<style>
#preloader {
    position: fixed;
    left: 0;
    top: 0;
    z-index: 999;
    width: 100%;
    height: 100%;
    overflow: visible;
    background: #E7EDF1 url('img/ajax-loader2.gif') no-repeat center center;
  opacity: 0.8;  Полупрозрачный фон 
}
</style>
<script>
jQuery(document).ready(function ($) {
    $(window).load(function () {
        setTimeout(function(){
            $('#preloader').fadeOut('slow', function () {
            });
        },0);

    });  
});
</script>
<?php
	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+              Название: | MINISTRYBOOKS.RU Search               +
	+ -------------------------------------------------------------- + 
	+                Версия: | 1.0                                   +
	+             Тип:       | скрипт поиска по сайту                +
	+            Требования: | PHP5                                  +
	+             Платформа: | любая                                 +
	+                  Язык: | русский                               +
	+                 Автор: | Korolev Evgeniy (http://www.kbk.ru)   +
	+   Copyright 2016-2017: | © KBK.RU - All Rights Reserved.        +
	+ -------------------------------------------------------------- + 
	+              Обновлен: | 16 ноября 2016                        +
	+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + */ 

############################################################################
 include 'safemysql.class.php';
 // ставим скрипт "на счетчик" (чтобы знать, как долго он выполнялся
 $ttt=microtime();
 $ttt=((double)strstr($ttt, ' ')+(double)substr($ttt,0,strpos($ttt,' ')));

  print '<ul class="breadcrumbs">
        <li><a href="index.cfm">Главная</a></li>
        <li class="current"><a href="/?mod=search_books">Поиск по книгам</a></li>
      </ul>';
  print "<h2>Поиск по книгам</h2>";

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                     Инициализация переменных                   +
	+ --------------------------------------------------------------*/

  $srcStr = $_GET['srcStr'];   //  Инициализация переменной для GET для нового поиска 

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                   Открываем сессию                             +
	+ --------------------------------------------------------------*/
 
  session_start();  

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                удаление сессии по GET запросу                  +
	+ --------------------------------------------------------------*/

  if(strlen($_GET['srcStr'])>0 || isset($srcStr) || !empty($srcStr)) {    
    unset($_SESSION['template']);
    unset($_SESSION['temp']);
    unset($_SESSION['search_by_author']);
    unset($_SESSION['search_by_logic']);
    unset($_SESSION['search_by_stype']);
    session_destroy();
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=search_books'></HEAD></HTML>";
   return;
  }

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                                                                +
	+                ВЫБОР КРИТЕРИЕВ ПОИСКА В ФОРМЕ                  +
	+                ------------------------------                  +
	+                                                                +
	+               Выпадющий список: | Логига поиска: И, ИЛИ        +
	+ --------------------------------------------------------------*/
 
 /* $logic = $_POST['logic'];    
  if($logic != 'OR')
  $logic = 'AND';

  $search_by = $_POST['search_by'];
  if($search_by != '2') { $search_by = '1'; } else {$search_by = 'All';}

  $stype = $_POST['stype'];
  if($stype != 'F')
      $stype = 'S'; */

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+         Выпадющий список: | Логига поиска: И, ИЛИ              +
	+ --------------------------------------------------------------*/
         
    $logic_opt .= "<option value='AND' ";
  if($logic == 'AND')
    $logic_opt .= " selected" ;
    $logic_opt .= ">{$l_search[9]}</option>";
    $logic_opt .= "<option value='OR' ";
  if($logic == 'OR')
    $logic_opt .= " selected";
    $logic_opt .= ">{$l_search[10]}</option";

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Все публикации                 +
	+ --------------------------------------------------------------*/

    $id_search_by .= "<option value='All'";
  if($search_by == 'Все публикации')
    $id_search_by .= " selected" ;
    $id_search_by .= ">Все публикации</option>";


	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Список по автору               +
	+ --------------------------------------------------------------*/


    $id_search_by .= "<optgroup label='По автору:'><option value='WL'";
  if($search_by == 'Уитнесс Ли')
    $id_search_by .= " selected" ;
    $id_search_by .= ">Уитнесс Ли</option>";

    $id_search_by .= "<option value='WN'";
  if($search_by == 'Вочман Ни')
    $id_search_by .= " selected" ;
    $id_search_by .= ">Вочман Ни</option></optgroup>";
 
	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Список категорий               +
	+ --------------------------------------------------------------*/

  $query_CAT = "SELECT *
             FROM {$gl_db_prefix}parts
             ORDER BY title ASC";
  $results_CAT = db_select($query_CAT);

  if(is_array($results_CAT)) {      
      $cnt_CAT = count($results_CAT);
   
      $id_search_by .= "<optgroup label='По категории:'>";

      for($i = 0; $i < $cnt_CAT; $i++) {
            $id_part = $results_CAT[$i]['id_part'];
            $title_ct = stripslashes($results_CAT[$i]['title']);

            $query_z = "SELECT *
                FROM {$gl_db_prefix}parts_items
               	WHERE id_part = {$id_part}
               	ORDER BY title ASC";
              $results_z = db_select($query_z);
              $cnt_z = count($results_z);
              if($cnt_z > 0) { $title_CAT = $results_CAT[$i]['title'];  
               $id_search_by .= "<option value={$id_part}";
                  if($search_by == $title_CAT)
                       $id_search_by .= " selected" ;
                       $id_search_by .= ">" . $title_ct . " (" . $cnt_z . ") " . "</option>";
         }}
                       $id_search_by .= "></optgroup>";   
     }

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Список все книги               +
	+ --------------------------------------------------------------*/

   $query_all_books = "SELECT *
             FROM {$gl_db_prefix}parts_items
             ORDER BY title ASC, pos";
   $results_all_books = db_select($query_all_books);

   if(is_array($results_all_books)) {      
      $cnt_all_books = count($results_all_books);
   
      $id_search_by .= "<optgroup label='По книге:'>";

      for($q = 0; $q < $cnt_all_books; $q++) {
              $title_all_books = $results_all_books[$q]['title'];
              $id_item_all_books  = $results_all_books[$q]['id_item'];
              $id_item_all_books  = "G" . $id_item_all_books ;
 
              $id_search_by .= "<option value={$id_item_all_books}";
              if($search_by == $title_all_books)
              $id_search_by .= " selected" ;
              $id_search_by .= ">" . $title_all_books . "</option>";
           }
              $id_search_by .= "></optgroup>";   
     }

$noise_words = array('а', 'без', 'более', 'бы', 'был', 'была', 'были', 'было', 'быть', 'в', 'вам', 'вас', 'весь', 'во', 'вот', 'все', 'всего', 'всех', 'вы', 'где', 'да', 'даже', 'для', 'до', 'его', 'ее', 'если', 'есть', 'ещё', 'же', 'за', 'здесь', 'и', 'из', 'из-за', 'или', 'им', 'их', 'к', 'как', 'как-то', 'ко', 'когда', 'кто', 'ли', 'либо', 'мне', 'может', 'мы', 'на', 'надо', 'наш', 'не', 'него', 'неё', 'нет', 'ни', 'них', 'но', 'ну', 'о', 'об', 'однако', 'он', 'она', 'они', 'оно', 'от', 'очень', 'по', 'под', 'при', 'с', 'со', 'так', 'также', 'такой', 'там', 'те', 'тем', 'то', 'того', 'тоже', 'той', 'только', 'том', 'ты', 'у', 'уже', 'хотя', 'чего', 'чей', 'чем', 'что', 'чтобы', 'чьё', 'чья', 'эта', 'эти', 'это', 'я'); 

 if(!empty($_POST['search']) AND isset($_POST["template"]) AND !empty($_POST["template"]) AND !in_array(mb_strtolower($_POST["template"], 'utf-8'), $noise_words)) { echo '<div id="preloader"></div>'; }

      /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +                     Форма поиска по книгам                      +
      +----------------------------------------------------------------*/   

   echo '<div class="row">
            <div class="small-4 small-centered columns">';
   echo "<div id='resultalert' style='color:red; width:380px; text-align: center;margin-bottom:10px;'></div>";
   echo "</div>
            </div>";
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  if(!empty($errors))
  print form_print_errors($errors);
  print form_begin('edit_form', '', 'POST', 'multipart');
  print work_template($form_lineobl_tpl, array("{caption}" => $l_search[2],
        "{field}" => form_create_input("template", $css = 'SiteFInputM', $size ='')));
  print work_template($form_lineobl_tpl, array("{caption}" => "Включая все формы",
        "{field}" => form_create_radio("stype", "", "F")));
  print work_template($form_lineobl_tpl, array("{caption}" => "Точное совпадение",
        "{field}" => form_create_radio("stype", "yes", "S"))); 
  print work_template($form_lineobl_tpl, array("{caption}" => $l_search[3],
        "{field}" => form_create_select('logic', $logic_opt, $css = 'SiteFInputM')));  
  print work_template($form_lineobl_tpl, array("{caption}" => "Категория поиска",
        "{field}" => form_create_select('search_by', $id_search_by, $css = 'SiteFInputM')));   
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
        "{field}" => form_create_submit('search', $value='Найти', $css = 'button small radius expand')));
//  print form_create_hidden('blague', session_id());
//  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_tpl', $id_tpl);
  print form_end();
  print '<p>Область поиска <strong><a href="#" data-reveal-id="myModalScope">Что это?</a></strong><br>';  
  if(isset($_SESSION['template'])){ print '<a class="button radius" href="/?mod=search_books&srcStr='. $templateid .'">Очистить поиск</a></p>'; } 

     /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +          Подключает класс извлечения корня слова                +
      +----------------------------------------------------------------*/
  $vendorDir = __DIR__ . '';
    if (file_exists($file = $vendorDir . '/FIL/1.inc')) {
       require_once $file;     
     } 
      /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +                                                                 +
      +          ОТПРАВКА ДАННЫХ В ФОРМУ ПОИСКА, POST                   +
      +                                                                 +
      +----------------------------------------------------------------*/

if(!empty($_POST['search']) || isset($_GET['part'])) {
  //   if (count($out) < 1 || !is_array($out))

      /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +          Подключает класс извлечения корня слова                +
      +----------------------------------------------------------------*/

  $vendorDir = __DIR__ . '';
    if (file_exists($file = $vendorDir . '/NXP/Stemmer.php')) {
       require_once $file;     
     } 
      /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +     Инициализируем Переменные выбора критерия поиска            +
      +----------------------------------------------------------------*/ 
      
  $logic = $_POST['logic'];
  if($logic != 'OR') $logic = 'AND';  // Выбор Логики поиска: И, ИЛИ
  
  $search_by = $_POST['search_by'];   // Выбор критерия поиска по категории

  $stype = $_POST['stype'];
  if($stype != 'F') $stype = 'S';      // Выбор критерия поиска по автору

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                   Помещаем переменные в сессию                 +
	+ --------------------------------------------------------------*/

  if (isset($_POST["template"])) {
    $template = strip_tags($_POST['template']); 
    $_SESSION['template']=$_POST['template'];
    $_SESSION['temp']=$_POST['template'];
    $_SESSION['search_by_author']=$_POST['search_by'];
    $_SESSION['search_by_logic']=$_POST['logic'];
    $_SESSION['search_by_stype']=$_POST['stype']; 
   }

    $template = strip_tags($_SESSION['template']);  
    $templateid = strip_tags($_SESSION['temp']);
    $search_books_by_author = strip_tags($_SESSION['search_by_author']);
    $search_books_by_logic = strip_tags($_SESSION['search_by_logic']);
    $search_books_by_stype = strip_tags($_SESSION['search_by_stype']); 
  
      /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +                          Точное совпадение                      +
      +----------------------------------------------------------------*/

 if($search_books_by_stype == 'S') {
    $tpl = trim($templateid);
 /*   $tpl = mysqli_real_escape_string(DBBYMYSQLI::$link,$tpl);
    $tpl = htmlspecialchars($tpl);  // преобразование в HTML сущности
    $tpl = stripcslashes($tpl);   // Удаляет экранирование символов
    $tpl = stripslashes($tpl);   // Удаляет экранирование символов
    $tpllower = mb_strtolower($tpl, 'utf-8');
    $tplucfirst = mb_ucfirst($tpllower);
    $tplupper = mb_strtoupper($tpl, 'utf-8');
    if (str_word_count > 1) { $tplconvert_case = mb_convert_case($tpllower, MB_CASE_TITLE, "UTF-8");}
    $stemmed = array();
    $stemmed[] = $tplucfirst;       // Первая буква заглавная 
    if (str_word_count > 1) { $stemmed[] = $tplconvert_case; } 
    $stemmed[] = $tplupper;         // Все буквы большие
    $stemmed[] = $tpllower;         // Все буквы маленькие
    if (!in_array($tpl, $stemmed)) {  $stemmed[] = $tpl; }  // Проверяем есть ли исходная фраза в массиве, и если нет добавляем в массив
    $wrd_cnt = count($stemmed);    */
   }       
      /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +                          Включая все словоформы                 +
      +----------------------------------------------------------------*/
  else {
      $tpl = preg_replace("/[^\w\x7F-\xFF\s]/", " ", $templateid);  
      $tpl = str_replace('?', '_', $tpl);
      $tpl = str_replace('*', '%', $tpl);
      $tpl = trim(preg_replace("/\s(\S{1,2})\s/", " ", $tpl));   
      $tpl = ereg_replace(" +", " ", $tpl);                        
      $words = explode(" ", $tpl);                               
      $stemmer = new \NXP\Stemmer();
      $stemmed = array();
        foreach ($words as $word) {
           if (!in_array(mb_strtolower($word, 'utf-8'), $noise_words)) { 
             $word = $stemmer->getWordBase($word);                               // Слова в исходном состоянии
             $stemmed[] = $stemmer->getWordBase(mb_ucfirst($word));              //  Первая заглавная буква
             $stemmed[] = $stemmer->getWordBase(mb_strtoupper($word, 'utf-8'));  //  Слова из заглавных букв
             $stemmed[] = $stemmer->getWordBase(mb_strtolower($word, 'utf-8'));  //  Слова из маленькие буквы 
             }
          }
             $wrd_cnt = count($stemmed);
  }
        $result = implode(', ', $stemmed);
        $_SESSION['words_sessia'] = serialize($stemmed);    //  не удалять сессию
        $_SESSION['words_stemmed'] = $result;               //  не удалять сессию                                           
 
  if(empty($tpl)) {
      echo "<script> 
               document.getElementById('resultalert').innerHTML = '<strong>Введите, пожалуйста, ключевые слова.</strong>';
                  setTimeout(function() { document.getElementById('resultalert').style.display = 'none'; }, 8000); </script>";
      return;
  } else {
    if (mb_strlen(trim($tpl), 'utf-8') < 3) {           
         echo "<script>document.getElementById('resultalert').innerHTML = '<strong>Слишком короткий поисковый запрос, меньше 3 символов.</strong>'; 
                      setTimeout(function() { document.getElementById('resultalert').style.display = 'none';}, 8000);</script>";  

             unset($_SESSION['template']);
             return;          
    } else if (mb_strlen(trim($tpl), 'utf-8') > 128) {
         echo "<script>document.getElementById('resultalert').innerHTML = '<strong>Слишком длинный поисковый запрос, больше 128 символов.</strong>';
                    setTimeout(function() { document.getElementById('resultalert').style.display = 'none';}, 8000);</script>";  
             unset($_SESSION['template']);
             return;
    } else if (in_array(mb_strtolower($tpl, 'utf-8'), $noise_words)) {
          echo "<script>document.getElementById('resultalert').innerHTML = '<strong>Слово относится к Стоп-словам</strong>';
                   setTimeout(function() { document.getElementById('resultalert').style.display = 'none';}, 8000);</script>";  
             unset($_SESSION['template']);
             return;
    }
  }

  if($search_books_by_author[0]<>'G') {
    $query_CAT = "SELECT *
             FROM {$gl_db_prefix}parts
             ORDER BY title ASC";

   $results_CAT = db_select($query_CAT);

      if(is_array($results_CAT)) {
       $cnt_CAT = count($results_CAT); 
        for($i = 0; $i < $cnt_CAT; $i++) {   
            $id_part = $results_CAT[$i]['id_part']; 
            $cat_title = $results_CAT[$i]['title']; 
            if($id_part = $search_books_by_author) {$cat_books = $id_part;}
        }
      }
      $search_criterion_books = "WHERE id_part = " . $id_part;
    }
  else if($search_books_by_author[0]=='G') {
  $search_books_by_author = substr($search_books_by_author, 1);
  $query_all_books = "SELECT *
             FROM {$gl_db_prefix}parts_items
             ORDER BY title ASC, pos";

  $results_all_books = db_select($query_all_books);

  if(is_array($results_all_books)) {      
      $cnt_all_books = count($results_all_books);
    
     for($q = 0; $q < $cnt_all_books; $q++) {
           $id_item_all_books  = $results_all_books[$q]['id_item'];
           $title_all_books = $results_all_books[$q]['title'];
           if($id_item_all_books = $search_books_by_author) {$cat_books = $id_item_all_books;}
         }
      }

    $search_criterion_books = "WHERE id_item =" . $id_item_all_books;
 }

   switch ($search_books_by_author) {
      case 'All':
        $search_criterion = ""; $books_by_author = "Все публикации"; break;
      case 'WN':
        $search_criterion = "WHERE id_author = 1";  $books_by_author = "Вочман Ни";  break;      
      case 'WL':
        $search_criterion = "WHERE id_author = 2";  $books_by_author = "Уитнесс Ли"; break;
      case $cat_books:
        $search_criterion =  $search_criterion_books;  $books_by_author = "По категории"; break;    
       } 
 
    $_SESSION['books_by_author'] = $books_by_author;

    $query_id_pg = "SELECT id_item 
                    FROM {$gl_db_prefix}parts_items "; 
    $query_id_pg .= $search_criterion;
  
    $results_id_pg = db_select($query_id_pg);
  
     if(is_array($results_id_pg))
       { 
           $ct = count($results_id_pg);
           $id_books= array();  //  массив выборка страниц по заданному критерию  
              for($i = 0; $i < $ct; $i++)
                {
                   $books = $results_id_pg[$i]['id_item'];        
                    $id_books[] = $books;      
                }
        }
   $id_pg_books = implode(", ", $id_books);

   //    echo $id_pg_books . '<hr>'; 

/*$name` IN BOOLEAN MODE
 $query = "SELECT id_pg, content
              FROM {$gl_db_prefix}pages_blocks
              WHERE gen_type = 'text' AND id_pg IN ({$id_pg_books}) AND ";
    $query .= " (";    
          for($t = 0; $t < $wrd_cnt; $t++)  
              {
		  if($t != 0)
		      $query .= ' '.$search_books_by_logic.' ';
		      $query .= "content LIKE '%{$stemmed[$t]}%'";
	        }
 		      $query .= " ) GROUP BY id_pg"; 
*/

 $query = "SELECT *
              FROM {$gl_db_prefix}pages_blocks
              WHERE  gen_type = 'text' AND id_pg IN ({$id_pg_books}) AND  
		MATCH(content) AGAINST('{$tpl}' IN BOOLEAN MODE)"; 

   $results = db_select($query);   

      $tpl = preg_replace("/[^\w\x7F-\xFF\s]/", " ", $tpl);  
      $tpl = str_replace('?', '_', $tpl);
      $tpl = str_replace('*', '%', $tpl);
      $tpl = preg_replace("/\s(\S{1,2})\s/", " ", $tpl);    
      $tpl = ereg_replace(" +", " ", $tpl);                        

   $arr = array();    // инициализация ассоциативного многомерного массива для заполнения данными
  
 if(is_array($results)) {  // 6
     $cnt = count($results);                                         //  количество книг, найденных по критерию поиска
      for($i = 0; $i < $cnt; $i++)                                   //  постраничный перебор каждой книги
        {    // 5
          $id_pg = $results[$i]['id_pg'];                            //  номера, найденных книг
          $content = $results[$i]['content'];
          //$content = stripslashes($results[$i]['content']);          //  stripslashes — Удаляет экранирование символов
          $content = strip_tags($content);                           //  strip_tags - Удаляет HTML и PHP-теги из строки  
  	   $content_by_pages = explode("[NEWPAGE]", $content);        //  разбивает контент на страницы
  	   $pages_cnt = count($content_by_pages);                     //  количество страниц в найденной книге
            //      echo $id_pg . ', ' ;                             //  печать найденных книг  new RegExp(word, 'g')                           
        $reps = array(); 
           if($pages_cnt > 0)
            {  // 4
               for($j = 0; $j < $pages_cnt; $j++) 
                 {   //3
                    $num_pages = $num_pages + 1;
                       $part = $j + 1;
                               $query = "SELECT title FROM {$gl_db_prefix}parts_items WHERE id_item = {$id_pg} ORDER BY title ASC"; 
                   	       $title = stripslashes(db_select_one($query));                     
                               $links_books = "<a href='?mod=s&mb={$id_pg}&part={$part}'>{$title}</a>";


         		//for($k = 0; $k < $wrd_cnt; $k++)  
          		//  {        //2                 	
                           $count_words = preg_match_all( '/'. $tpl .'/iu', $content_by_pages[$j], $matches ); 
                                           
                          if(preg_match('/'.$tpl.'/i', $content_by_pages[$j]))
                             {         //1                    
  	                       $pos = mb_strrpos($content_by_pages[$j], $tpl);        // позиция первого вхождения слова/фразы                        
                                          $content_by_pages[$j] = mb_substr($content_by_pages[$j], $pos, 100);
		                            $content_by_pages[$j] = $content_by_pages[$j];
		                            $content_by_pages[$j] = substr($content_by_pages[$j], 0, strrpos($content_by_pages[$j], ' '));
		                            $content_by_pages[$j] .= " ...";
                                  	    $replacement = "<mark>".$tpl."</mark>"; 
		                //$content_by_pages[$j] = eregi_replace($tpl, $replacement, $content_by_pages[$j]);
                    $content_by_pages[$j] = mb_eregi_replace($tpl, $replacement, $content_by_pages[$j]);                                        
  $arr[$i][$j] = array('subject' => $title, 'lnk' => $links_books, 'shot_content' => $content_by_pages[$j], 'prt' => $part, 'ps' => $pos, 'rep' => $count_words);   
                                            	                            
                             }       //1
 
                   //     }      //2  
                   }   //3
              } // 4
          }  // 5
   }  // 6
 
  foreach ($arr as $elements => $element) {$vcount = count($element) + $vcount;}
 
  if($vcount > 0) {
    $n = 0;
    $ar_sort = array();

      foreach ($arr as $key => $val) {  
             foreach ($val as $v1) {
                 $ar_sort[] = $v1[subject];    // заполняем массив для сортировки
                 $n = $n + 1;         
                 $mass[$n] = '<tr><td>' . $v1[lnk] . '</td><td>' . $v1[shot_content] . '</td><td>' . $v1[prt] . '</td><td>' . $v1[rep] . '</td></tr>'; 
                 $reps[] = $v1[rep];   // Собираем массив количество найденных фраз

               }
          } 

      $total_repet_words = array_sum($reps); 
      $_SESSION['total_repet_words_sessia'] = serialize($total_repet_words);         //  ПОМЕЩАЕМ МАССИВ подсчет слов  В СЕССИЮ                                                      
      array_multisort($ar_sort, SORT_ASC, $mass);     //  сортировка по алфавиту
      $_SESSION['books_sessia'] = serialize($mass);   //  ПОМЕЩАЕМ МАССИВ В СЕССИЮ ПОСЛЕ СОРТИРОВКИ 
  
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=search_tips_books'></HEAD></HTML>";  // Переходим к результатам поиска на другую страницу

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                          КОНЕЦ                                 +
	+ --------------------------------------------------------------*/
  } 
  else {
	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+	                                                         +
	+      Сообщение, если ничего не найдено по запросу              +
	+	                                                         +
	+ --------------------------------------------------------------*/

         echo "<script>
                  document.getElementById('resultalert').innerHTML = 'По запросу <strong> «{$template}» </strong> ничего не найдено!';
                             setTimeout(function() {
                              document.getElementById('resultalert').style.display = 'none';
                             }, 10000);
                                     </script>";

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                          ОЧИЩАЕМ СЕССИЮ                        +
	+ --------------------------------------------------------------*/
   
                unset($_SESSION['template']);
                unset($_SESSION['temp']);
                unset($_SESSION['search_by_author']);
                unset($_SESSION['search_by_logic']);
                unset($_SESSION['search_by_stype']);
                                 session_destroy();
                                           return;  
 }
      /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +                                                                 +
      +                 КОНЕЦ | ОТПРАВКА ДАННЫХ В ФОРМУ                 +
      +                                                                 +
      +----------------------------------------------------------------*/
} 

// считаем, как долго работал скрипт mb_strtolower($tag, 'utf-8')
   $ddd=microtime();  $_SESSION['ddd'] = $ddd;
   $ddd=((double)strstr($ddd, ' ')+(double)substr($ddd,0,strpos($ddd,' ')));
   $_SESSION['dd'] = number_format(($ddd-$ttt),3);
// echo ("<br>Время индексации: ".(number_format(($ddd-$ttt),3)). " секунд<br><br>");
?>
 <!--     <h3>Основной поиск</h3>
      <dl>
      <dt>Для того, чтобы осуществить поиск нужно просто ввести искомые слово или фразу.</dt>
      <dd>В работу алгоритма поисковой машины заложено отбрасывание, т.е. исключение из индексирования, определённых слов, которые часто называют <a href="#" data-reveal-id="myModalNoise">«шумовыми словами»</a> (их часто называют "стоп-слова"). Такими словами могут быть предлоги, суффиксы, причастия, междометия и частицы:</dd>	
<dd>а, без, более, бы, был, была, были, было, быть, в, вам, вас, весь, во, вот, все, всего, всех, вы, где, да, даже, для, до, его, ее, если, есть, ещё, же, за, здесь, и, из, из-за, или, им, их, к, как, как-то, ко, когда, кто, ли, либо, мне, может, мы, на, надо, наш, не, него, неё, нет, ни, них, но, ну, о, об, однако, он, она, они, оно, от, очень, по, под, при, с, со, так, также, такой, там, те, тем, то, того, тоже, той, только, том, ты, у, уже, хотя, чего, чей, чем, что, чтобы, чьё, чья, эта, эти, это, я</dd>      
<h3>Расширенный поиск</h3>
        <dd>Вы можете ограничить несколько слов или фраз с помощью И, ИЛИ</dd> 
<dt>Поиск по всем словоформам</dt>
	<dd>Это метод поиска разделяет фразу на отдельные слова и генерирует все спряжения и склонения для каждого слова в поисковой фразе. Поиск слова, обитать, находит фразы обитать, обитающий, обители, обитель, обители, и обителей и т.д.</dd>
       
      </dl> 

<div id="myModalNoise" class="reveal-modal">
 	<h2>Шумовые слова и Стоп-слова</h2>
 	<p>В работу алгоритма поисковой машины заложено отбрасывание, т.е. исключение из индексирования, определённых слов, которые часто называют "шумовыми словами" (их часто называют "стоп-слова"). Такими словами могут быть предлоги, суффиксы, причастия, междометия и частицы:</p>
	<p>а, без, более, бы, был, была, были, было, быть, в, вам, вас, весь, во, вот, все, всего, всех, вы, где, да, даже, для, до, его, ее, если, есть, ещё, же, за, здесь, и, из, из-за, или, им, их, к, как, как-то, ко, когда, кто, ли, либо, мне, может, мы, на, надо, наш, не, него, неё, нет, ни, них, но, ну, о, об, однако, он, она, они, оно, от, очень, по, под, при, с, со, так, также, такой, там, те, тем, то, того, тоже, той, только, том, ты, у, уже, хотя, чего, чей, чем, что, чтобы, чьё, чья, эта, эти, это, я</p>
 	<a class="close-reveal-modal">&#215;</a>
</div>

<div id="myModalScope" class="reveal-modal" style="display: none; opacity: 1; visibility: hidden; top: -180px;">
 	<h2>Область поиска</h2>
 	<h3>Поиск по всем словоформам</h3>
	<p>Это метод поиска разделяет фразу на отдельные слова и генерирует все спряжения и склонения для каждого слова в поисковой фразе. Поиск слова, обитать, находит фразы обитать, обитающий, обители, обитель, обители, и обителей и т.д.</p>
	<h3>Поиск по точному соответсвию</h3>
	<p>Эта опция выполняет поиск точных совпадений указанных слов или фраз, используемых в строке поиска.</p> 
	<h3>Примечание</h3>
	<p>Общие слова, такие как "и", "есть", "но", пропускаются при поиске. Список всех шумовых слов выглядит следующим образом:</p>
	<p>а, без, более, бы, был, была, были, было, быть, в, вам, вас, весь, во, вот, все, всего, всех, вы, где, да, даже, для, до, его, ее, если, есть, ещё, же, за, здесь, и, из, из-за, или, им, их, к, как, как-то, ко, когда, кто, ли, либо, мне, может, мы, на, надо, наш, не, него, неё, нет, ни, них, но, ну, о, об, однако, он, она, они, оно, от, очень, по, под, при, с, со, так, также, такой, там, те, тем, то, того, тоже, той, только, том, ты, у, уже, хотя, чего, чей, чем, что, чтобы, чьё, чья, эта, эти, это, я</p><a class="close-reveal-modal">×</a>
</div> -->