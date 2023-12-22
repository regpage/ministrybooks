<?php
  /* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
  +                        CSS стили                               +
  + --------------------------------------------------------------*/
  
include("engine/search/css/style.php");
  
  /* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
  +                      JS document.ready                         +
  + --------------------------------------------------------------*/

include("engine/search/js/js_up.php");

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

// ставим скрипт "на счетчик" (чтобы знать, как долго он выполнялся)
$ttt=microtime();
$ttt=((double)strstr($ttt, ' ')+(double)substr($ttt,0,strpos($ttt,' ')));

// хлебные крошки (навигация)
print '<ul class="breadcrumbs">
      <li><a href="index.cfm">Главная</a></li>
      <li class="current"><a href="/?mod=search_on_site">Поиск по книгам</a></li>
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

if (strlen($_GET['srcStr'])>0 || isset($srcStr) || !empty($srcStr)) {
  unset($_SESSION['template']);
  unset($_SESSION['temp']);
  unset($_SESSION['search_by_author']);
  unset($_SESSION['search_by_logic']);
  unset($_SESSION['search_by_stype']);
  session_destroy();
  echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=search_on_site'></HEAD></HTML>";
  return;  
}

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
  +                        Выпадющие списки                        +
  + --------------------------------------------------------------*/
  
include("engine/search/html/options_html.php");
  
  /* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
  +                        шумовые слова                           +
  + --------------------------------------------------------------*/

include("engine/search/data/noise_words.php");

// На случай пустого запроса и шумовых слов
if (!empty($_POST['search']) AND isset($_POST["template"]) AND !empty($_POST["template"]) AND !in_array(mb_strtolower($_POST["template"], 'utf-8'), $noise_words)) {
  echo '<div id="preloader"></div>';
}

  /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
  +                     Форма поиска по книгам                      +
  +----------------------------------------------------------------*/

include("engine/search/html/form.php");

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

if (!empty($_POST['search']) || isset($_GET['part'])) {
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
      // точное соответствие
      include("engine/search/core/exact_match.php");
      $wrd_cnt = count($stemmed);
  } else {

    /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
    +                          Включая все словоформы                 +
    +----------------------------------------------------------------*/

      include("engine/search/core/exact_match.php");
      $wrd_cnt = count($stemmed);
  }

    /*++++++++++++++++++++++++++++++++++
    + работаем с полученным массивом   +
    +-----------------------------------*/

  $result = implode(', ', $stemmed);
  $_SESSION['words_sessia'] = serialize($stemmed);    //  !не удалять сессию
  $_SESSION['words_stemmed'] = $result;               //  !не удалять сессию
    
    /*+++++++++++++++++++++++++++++++++++
    +     Сообщения об ошибках html   +
    +-----------------------------------*/     

  include("engine/search/html/error_msgs.php");

    /*+++++++++++++++++++++++++++++++++++
    +         Запросы MySQL             +
    +-----------------------------------*/

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
  } else if($search_books_by_author[0]=='G') {
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
              if($id_item_all_books = $search_books_by_author) {
                  $cat_books = $id_item_all_books;
              }
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

     if(is_array($results_id_pg)) {
          $ct = count($results_id_pg);
          $id_books= array();  //  массив выборка страниц по заданному критерию
          for($i = 0; $i < $ct; $i++) {
              $books = $results_id_pg[$i]['id_item'];
                  $id_books[] = $books;
          }
    }
    $id_pg_books = implode(", ", $id_books);
   
   //    echo $id_pg_books . '<hr>';
// ПОИСК MySQL *********************************
  // Разбить весь объём опрашиваемых книг на несколько запросов например 5-10.
  // Так же можно сделать кэш и брать книги и кэша, периодически подгружая их в кэш.
  // так же можно некотрые объёмные запросы хранить в кэше
   // ПРЕДВАРИТЕЛЬНО ТЕСТИРОВАТЬ В ТЕЧЕНИИ ДНЯ ОФИЦИАЛЬНЫЙ САЙТ
  $query = "SELECT id_pg, content
              FROM {$gl_db_prefix}pages_blocks
              WHERE id_pg IN ({$id_pg_books}) AND "; //gen_type = 'text' AND Временно удалено, не используется.
  $query .= " (";
      if ($search_books_by_stype == 'S') { // Точное совпадение с запятыми, ковычками и пр. знаками. Точка и знак вопроса пока не работают
        for($t = 0; $t < $wrd_cnt; $t++) {
            if($t != 0) {
              $query .= ' OR '; //$search_books_by_logic
          }
          //$query .= " `content` LIKE '%{$stemmed[$t]}%' ";
          $query .= "MATCH (content) AGAINST ('{$stemmed[$t]}') ";
        }
      } else { // Включая все словоформы
        for($t = 0; $t < $wrd_cnt; $t++) {
            if($t != 0)
              $query .= ' '.$search_books_by_logic.' ';
            $query .= "MATCH (content) AGAINST ('{$stemmed[$t]}') "; //  OR content REGEXP '[[:<:]]{$stemmed[$t]}[[:>:]]'    content LIKE '%{$stemmed[$t]}%'    MATCH (content) AGAINST ('{$stemmed[$t]}')
        }
      }

 		      $query .= " ) GROUP BY id_pg"; // COLLATE utf8_general_ci

   $results = db_select($query);
   $arr = array();  // инициализация ассоциативного многомерного массива для заполнения данными

 if(is_array($results))
    {  // 6      


      //  ЗАКОНЧИЛ ЗДЕСЬ ДАННЫЕ ПОЛУЧЕНЫ НО НЕ ВЫВЕДЕНЫ



     $cnt = count($results);                                         //  количество книг, найденных по критерию поиска
      for($i = 0; $i < $cnt; $i++)                                   //  постраничный перебор каждой книги
        {   // 5
          $id_pg = $results[$i]['id_pg'];                           //  номера, найденных книг
          $content = $results[$i]['content'];
          $content = stripslashes($results[$i]['content']);         //  stripslashes — Удаляет экранирование символов
          $content = strip_tags($content);                          //  strip_tags - Удаляет HTML и PHP-теги из строки
  	   $content_by_pages = explode("[NEWPAGE]", $content);       //  разбивает контент на страницы
  	   $pages_cnt = count($content_by_pages);                    //  количество страниц в найденной книге       
       // echo $id_pg . ', ' ;                            //  печать найденных книг  new RegExp(word, 'g')
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

// $count_words_arr = array();
         		for($k = 0; $k < $wrd_cnt; $k++)
          		  {        //2                         
                         $count_words = preg_match_all( '/'. $stemmed[$k] .'/iu', $content_by_pages[$j], $matches );                         
//  $count_words_arr[$k] = $count_words;
//  mb_ereg_match
//  if(preg_match('/'. $stemmed[$k] .'/i', $content_by_pages[$j]))
//  $stemmed[$k] = mb_convert_encoding($stemmed[$k], "UTF-8");
//  preg_match('/^.{' . $stemmed[$k] . '}(.*)/us', $s, $tmp);
//  /^[а-яё]+$/i; /^[а-яА-Я]+\s*[a-zA-Z]+$/
// ^foo -- строка начинается с “foo” $convertedText = (mb_convert_encoding($stemmed[$k], 'utf-8', mb_detect_encoding($stemmed[$k])));                                                   
                          if (strpos($content_by_pages[$j], $stemmed[$k]) !== false) { //1  // preg_match('/'.$stemmed[$k].$tmp_ecran.'/i', $content_by_pages[$j])                          
                              // позиция ПОСЛЕДНЕГО вхождения слова/фразы (что если слово окажется последним в тексте?)
  	                          $pos = mb_strrpos($content_by_pages[$j], $stemmed[$k]);
                              // Получаем фрагмент текста длинной 100 символов
                              $content_by_pages[$j] = mb_substr($content_by_pages[$j], $pos, 100);

		                          //$content_by_pages[$j] = $content_by_pages[$j];

                              // убираем часть строки до первого пробела с конца.
		                          $content_by_pages[$j] = substr($content_by_pages[$j], 0, strrpos($content_by_pages[$j], ' '));
                              // добавляем троеточее в конец фразы
		                          $content_by_pages[$j] .= " ...";
  // исключения для . и ? в патернах регулярных выражений
  $sim = false;
  $mark_stemmed = $stemmed[$k];  
  if (substr(trim($stemmed[$k]),-1) === '.') {
    $temp_str_ekran_search = explode('.', $stemmed[$k]);
    $mark_stemmed = $stemmed[$k];
    $content_by_pages[$j] = mb_eregi_replace($temp_str_ekran_search[0]."\.", $replacement, $content_by_pages[$j]);
    $sim = true;
  } elseif (substr(trim($stemmed[$k]),-1) === '?') {
    $temp_str_ekran_search = explode('?', $stemmed[$k]);
    $content_by_pages[$j] = mb_eregi_replace($temp_str_ekran_search[0]."\?", $replacement, $content_by_pages[$j]);    
    $mark_stemmed = $stemmed[$k];
    $sim = true;
  }
                              // отмечаем икомое слово
                              $replacement = "<mark>".$mark_stemmed."</mark>";
                              
		                          //$content_by_pages[$j] = eregi_replace($stemmed[$k], $replacement, $content_by_pages[$j]);
                              // заменяем искомое слово словом с выделением
                              if ($sim === false) {
                                $content_by_pages[$j] = mb_eregi_replace($stemmed[$k], $replacement, $content_by_pages[$j]);
                              } else {
                                $sim = false;
                              }
                              

                              // $array_sum_array_sum = array_sum($count_words_arr);
                              $arr[$i][$j] = array('subject' => $title, 'lnk' => $links_books, 'shot_content' => $content_by_pages[$j], 'prt' => $part, 'ps' => $pos, 'rep' => $count_words);

                             }       //1
                        }      //2
                   }      //3
              }      // 4
          }    // 5
   }      // 6
// exit();
 foreach ($arr as $elements => $element) {$vcount = count($element) + $vcount;}

 if($vcount > 0)
  {
    $n = 0;
    $ar_sort = array();

      foreach ($arr as $key => $val)
         {
             foreach ($val as $v1)
               {
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

      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=search_tips'></HEAD></HTML>";  // Переходим к результатам поиска на другую страницу

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+                          КОНЕЦ                                 +
	+ --------------------------------------------------------------*/
  }
  else
  {
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

// закоментированное описание поиска в html
include("engine/search/html/html_bottom.php");