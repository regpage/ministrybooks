<?php

/***********************************************
*   PURPOSE: Search engine for ministry books
*   (c) Korolev Evgtniy
*   http://ministrybooks.ru
*   Date: 10.11.2016
*   Version.1.0
************************************************ */

//if (count($out) < 1 || !is_array($out) || )
  $vendorDir = __DIR__ . '';
    if (file_exists($file = $vendorDir . '/NXP/Stemmer.php')) {
       require_once $file;     // Подключает класс извлечения корня слова RussianStemmer
     }  
  include 'safemysql.class.php';
  // ставим скрипт "на счетчик" (чтобы знать, как долго он выполнялся
  $ttt=microtime();
  $ttt=((double)strstr($ttt, ' ')+(double)substr($ttt,0,strpos($ttt,' ')));

  $logic = $_POST['logic'];
  if($logic != 'OR') 
  $logic = 'AND';
  
  $search_by = $_POST['search_by'];
 //  if($search_by != '2') { $search_by = '1'; }

  $stype = $_POST['stype'];
  if($stype != 'F') $stype = 'S';
 
  print '<ul class="breadcrumbs">
        <li><a href="index.cfm">Главная</a></li>
        <li><a href="/?mod=search_on_site">Поиск по книгам</a></li>
        <li class="current"><a href="/?mod=search_on_site">Результаты поиска</a></li>
      </ul>';
  print "<h2>Поиск по книгам</h2>";

 /*   $logic_opt .= "<option value='AND' ";
  if($logic == 'AND')
    $logic_opt .= " selected" ;
    $logic_opt .= ">{$l_search[9]}</option>";
    $logic_opt .= "<option value='OR' ";
  if($logic == 'OR')
    $logic_opt .= " selected";
    $logic_opt .= ">{$l_search[10]}</option"; */
  
    session_start();  
    if (isset($_POST["template"])) 
  {    
    //$template = $_POST['template']; 
    $_SESSION['temp']=$_POST['template'];
    $_SESSION['search_by_author']=$_POST['search_by'];
    $_SESSION['search_by_logic']=$_POST['logic'];
    $_SESSION['search_by_stype']=$_POST['stype'];
  }
    $templateid = strip_tags($_SESSION['temp']);
    $search_books_by_author = strip_tags($_SESSION['search_by_author']);
    $search_books_by_logic = strip_tags($_SESSION['search_by_logic']);
    $search_books_by_stype = strip_tags($_SESSION['search_by_stype']);

 if(empty($templateid))
    {
      print $l_search[5]; 
      echo "<a href='/?mod=search_on_site'>Новый поиск по книгам</a><br><br><br><br><br>";                
      return;
    }
 if($search_books_by_stype == 'S') {
    $tpl = trim($templateid); 
    $tpl = mysqli_real_escape_string(DBBYMYSQLI::$link,$tpl);
    $tpl = htmlspecialchars($tpl);
    $stemmed = array();
    $stemmed[0] = $tpl; 
    $wrd_cnt = 1;    
 }
  else {
    $tpl = preg_replace("/[^\w\x7F-\xFF\s]/", " ", $templateid);
    $tpl = str_replace('?', '_', $tpl);
    $tpl = str_replace('*', '%', $tpl);
    $tpl = trim(preg_replace("/\s(\S{1,2})\s/", " ", $tpl));     // ограничение по количеству вводимых символов
    //$tpl = ereg_replace(" +", " ", $tpl);                        // сжатие 2-х пробелов   
    $tpl = preg_replace(" +", " ", $tpl);                        // сжатие 2-х пробелов   
    $words = explode(" ", $tpl);
    
    $stemmer = new \NXP\Stemmer();
    $stemmed = array();
    foreach ($words as $word) {
      $stemmed[] = $stemmer->getWordBase($word);
       } 
        $wrd_cnt = count($stemmed);
       }
        $result = implode(' ', $stemmed);
        //print_r($stemmed);
                                             
/* if(!empty($tpl))
    {
       if (strlen($tpl) < 3) {             
            echo '<p> Слишком короткий поисковый запрос.</p>';            
        }        
        else if (strlen($tpl) > 128) {
            echo '<p> Слишком длинный поисковый запрос.</p>';            
        }
     }    
*/
  $query_CAT = "SELECT *
             FROM {$gl_db_prefix}parts
             ORDER BY title ASC";
   $results_CAT = db_select($query_CAT);
   if(is_array($results_CAT))
  {      
     $cnt_CAT = count($results_CAT); 
     for($i = 0; $i < $cnt_CAT; $i++)
      {   
      $id_part = $results_CAT[$i]['id_part'];  
      if($id_part = $search_books_by_author) {$cat_books = $id_part;}
    }
  }
    switch ($search_books_by_author) {
      case 'All':
        $search_criterion = ""; break;
      case 'WN':
        $search_criterion = "WHERE id_author = 1";  break;      
      case 'WL':
        $search_criterion = "WHERE id_author = 2";  break;
      case $cat_books:
        $search_criterion = "WHERE id_part = {$id_part}";  break;    
       }         

    echo $search_books_by_author . " / " . $search_criterion . " / <br> ";
    //$search_criterion = "WHERE id_author = {$search_books_by_author}";
    
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

    echo $id_pg_books . '<hr>';
    $query = "SELECT id_pg, content
              FROM {$gl_db_prefix}pages_blocks
              WHERE gen_type = 'text' AND  id_pg IN ({$id_pg_books}) AND ";
    $query .= " (";    
          for($k = 0; $k < $wrd_cnt; $k++)  
              {
		   if($k != 0)
		      $query .= ' '.$search_books_by_logic.' ';
		      $query .= "content LIKE '%{$stemmed[$k]}%'";
	        }
 		      $query .= " ) GROUP BY id_pg"; 
    $results = db_select($query);
 
   /* print "<p><span class='gold'>{$l_search[8]}</span></p>";  */ 
   $arr = array();  // создаем массив для заполнения данными
   if(is_array($results))
    {
     $cnt = count($results);                                         // количество книг, найденных по критерию поиска
      print "{$l_search[6]}: [книг: <b>{$cnt}</b>], [кол. слов во фразе: <b>{$wrd_cnt}</b>], [фраза_1: <b>{$tpl}</b>, фраза_2: <b>{$result}</b>], [<b>{$ct}</b>]";   // количество найденных элементов
      for($i = 0; $i < $cnt; $i++)                                   // постраничный перебор каждой книги
        {   
           $id_pg = $results[$i]['id_pg'];                           //  номера, найденных книг
           // echo $id_pg . ', ' ;                                   //  печать найденных книг	
           $content = stripslashes($results[$i]['content']);         //  stripslashes — Удаляет экранирование символов
           $content = strip_tags($content);                          //  strip_tags — Удаляет HTML и PHP-теги из строки 
  	   $content_by_pages = explode("[NEWPAGE]", $content);        //  разбивает контент на страницы
  	   $pages_cnt = count( $content_by_pages);                    //  количество страниц в найденной книге
           if($pages_cnt > 0)
            {  	
             for($j = 0; $j < $pages_cnt; $j++) 
                 {  $num_pages = $num_pages + 1;
         		for($k = 0; $k < $wrd_cnt; $k++)  
          		  {  	
                         if(preg_match('/((?:^|>)[^<]*)('. $stemmed[$k] .')/si', $content_by_pages[$j])) 
                            { 
                               $part = $j + 1; 
                               $reps = substr_count($content_by_pages[$j], $stemmed[$k]);
  	                        $pos = strpos($content_by_pages[$j], $stemmed[$k]);  
  				                   		  
                               $query = "SELECT title FROM {$gl_db_prefix}parts_items WHERE id_item = {$id_pg} ORDER BY title ASC"; 
                   		   $title = stripslashes(db_select_one($query)); 
                                  if(strlen($content_by_pages[$j]) > 255)
                               	  { 
                               	    $content_by_pages[$j] = substr($content_by_pages[$j], $pos, 100);
		                 	    $content_by_pages[$j] = strip_tags($content_by_pages[$j]);
		                 	    $content_by_pages[$j] = rtrim($content_by_pages[$j], "!,.-");
		                 	    $content_by_pages[$j] = substr($content_by_pages[$j], 0, strrpos($content_by_pages[$j], ' '));
		                 	    $content_by_pages[$j] .= " ...";  
				   	  }      
		                 $replacement = "<mark>".$stemmed[$k]."</mark>"; 
		                 //$content_by_pages[$j] = eregi_replace($stemmed[$k], $replacement, $content_by_pages[$j]);
                     $content_by_pages[$j] = mb_eregi_replace($stemmed[$k], $replacement, $content_by_pages[$j]);
                               
   // echo "<li><a href='?mb={$id_pg}&part={$part}'>{$title}</a> : стр.[{$part}] : [{$pages_cnt}] : [Вхожд.: {$pos} ] : [Повт.: {$reps}]</li>";
   // $links_books = "<li><a href='?mb={$id_pg}&part={$part}'>{$title}</a></li>";
    $links_books = "<a href='?mb={$id_pg}&part={$part}'>{$title}</a>";
    $arr[$i][$j] = array('subject' => $title, 'lnk' => $links_books,'shot_content' => $content_by_pages[$j], 'prt' => $part, 'ps' => $pos, 'rep' => $reps);

                              //   echo "<p>{$content_by_pages[$j]}</p>";                
                          }    
		      }               
	          }   
              } 
          } 
echo "<hr>Поисковая фраза: <strong>" . $tpl . ".</strong> ";  
echo "<br>Логика поиска: <strong>" . $search_books_by_logic . "</strong><br>Вид поиска: "; if($search_books_by_stype =='F') { echo "<b>Включая все формы</b>";} else {echo "<b>Точное совпадение</b>";}
echo "<br>Kоличетсво элементов в 1 массиве многомерного массива: <b>" . count($arr) . "</b>";  
echo "<br>Рекурсивный подсчет всех элементов многомерного массива: <b>" . count($arr ,COUNT_RECURSIVE) . "</b>"; 
 foreach ($arr as $elements => $element) {$vcount = count($element) + $vcount;} 
   echo "<br>Количетсво элементов во вложенном массиве: <b>" . $vcount . "</b><hr>"; 

$part = isset($_GET['part']) ? (int) $_GET['part'] : 1;        // получим номер запрошенной страницы
$perPage = 50;                                                 // кол-во выводимых страниц
$pages = (int) ceil($vcount / $perPage);                       // рассчитаем кол-во страниц

if($vcount > 0) {
  $n = 0;
$ar_sort = array();
    foreach ($arr as $key => $val) {  
        foreach ($val as $v1) {
             $ar_sort[] = $v1[subject];  // заполняем массив для сортировки
             $n = $n + 1;         
           // echo $v1[lnk] . $v1[shot_content];  //print_r($val); 
 $mass[$n] = '<tr><td>' . $v1[lnk] . '</td><td>' . $v1[shot_content] . '</td><td>' . $v1[prt] . '</td><td>' . $v1[rep] . '</td></tr>'; 
            }
       } 
   }
   else
     if($part > $pages or $part < 1)          // проверим, что запрошенная страница существует
         // exit('Нет такой страницы');
         echo "Нет такой страницы";
       //  echo "<br><br>";
      $start = ($part - 1) * $perPage;               // посчитаем, с какого файла начинать вывод
                                                     // выберем файлы, которые должны быть отображены на этой странице
      array_multisort($ar_sort, SORT_ASC, $mass);    // сортировка по алфавиту
      $out = array_slice($mass, $start, $perPage); 
      echo "Кол. страниц: <b>" . $pages . "</b>"; echo "<br>Кол. элементов в массиве out: <b>" . count($out) . "</b>";

  if(isset($part)){if($part <= 1){$start=1;} else $start= $start + 1;}
    if(is_array($out))
    {
      echo '<table>
            <thead>
              <tr>                            
                <th>Название публикации</th>
                <th>Текст</th>
                <th>Стр.</th>
		  <th style="width: 2%;">вхожд.</th>               
              </tr>
            </thead>
            <tbody>';
  echo "<ol start={$start}>";  
     foreach ($out as $kay => $vl) {  echo $vl;  }
        echo "</ol>"; 
        echo '</tbody></table>'; 

  $navig = create_navigation($pages, "?mod=search_result", $part);
         echo $navig;
     }
} else {echo $text . "<br>Поиск не дал никаких результатов. <br><br><a href='/?mod=search_on_site'>Новый поиск по книгам</a>"; echo "<br><br><br><br>"; }

// считаем, как долго работал скрипт
$ddd=microtime();
$ddd=((double)strstr($ddd, ' ')+(double)substr($ddd,0,strpos($ddd,' ')));
echo ("<br>Время индексации: ".(number_format(($ddd-$ttt),3)). " секунд<br><br>");

?>