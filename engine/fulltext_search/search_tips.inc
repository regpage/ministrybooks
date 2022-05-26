<?php
/*************************************************************
*   https://github.com/NeonXP/Stemmer
*   PURPOSE: ПОИСК ПО КНИГАМ
*   scalar values
*************************************************************** */
print '<ul class="breadcrumbs">
        <li><a href="index.cfm">Главная</a></li>
        <li class="current"><a href="/?mod=search_books">Результаты поиска</a></li>
      </ul>';

 // print "<h2>Результаты поиска</h2>";
$part = 1;             // кол-во выводимых страниц
$part = isset($_GET['part']) ? (int) $_GET['part'] : 1;        // получим номер запрошенной страницы
$perPage = 30;  
   $start = ($part - 1) * $perPage; 
   session_start();
   $mass = unserialize($_SESSION['books_sessia']);     // Массив 
   $frase = strip_tags($_SESSION['template']);
   $words_sessia = $_SESSION['words_stemmed'];
   $total_repet_words = unserialize($_SESSION['total_repet_words_sessia']);
   $search_books_by_author = $_SESSION['search_by_author'];
   $search_books_by_logic = $_SESSION['search_by_logic'];
   $search_books_by_stype = $_SESSION['search_by_stype']; 
   $books_by = $_SESSION['books_by_author'];

$dd = $_SESSION['dd'];


if(isset($part)){if($part <= 1){$start=0;} else $start= $start + 1;}
           
print '<a class="button radius" href="/?mod=search_books&srcStr='. $templateid .'">Перейти к новому поиску</a>';
$out = array_slice($mass, $start, $perPage);
  //  print_r($mass);
$pages = (int) ceil(count($mass) / $perPage);
   if(is_array($out))
    {
     if($part > $pages or $part < 1)   { 
    //  echo '<p><a href="javascript:history.back()"> Вернуться назад </a></p>';            
        echo "<p style='color:red; width:380px; text-align: right;'><strong>Нет такой страницы</strong></p>";
        //echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=search_books'></HEAD></HTML>";
        return;           
       }  
if($search_books_by_stype =='F') { $books_by_stype = "<b>Включая все словоформы</b>";} else {$books_by_stype = "<b>Точное совпадение</b>";}
if($search_books_by_logic =='AND') { $by_logic = "<b>И</b>";} else {$by_logic = "<b>ИЛИ</b>";}
  $navig_top = navigation_books($pages, "?mod=search_tips_books", $part);
  $navig_bottom = create_navigation($pages, "?mod=search_tips_books", $part);
  echo "<div class='section-nav'>";
         echo $navig_top; 
echo "</div>";
echo "<div style='margin: 4px 0 0 0; font-size: 12px; display: inline-block;'>";
echo "Записей: " . count($mass) . ", #<strong>" . $start . "</strong> | Стр. <strong>" . $part . "</strong> из <strong>" . $pages . "</strong> | Поисковая фраза: <strong>" . $frase . "</strong> | Тип поиска: " . $books_by_stype . " | " . $by_logic . " | <strong>" . $books_by . "</strong><br>Всего упоминаний слова: <strong>" . $total_repet_words . "</strong>. ";
 echo " Словоформы поиска: <strong>" . $words_sessia . "</strong>. <br><br>Время, затраченное на поиск: ". $dd . " секунд";
; 
echo "</div>";
      echo '<table>
            <thead>
              <tr>                            
                <th>Название публикации</th>
                <th>Текст</th>
                <th>Стр.</th>
		  <th style="width: 2%;">кол.</th>               
              </tr>
            </thead>
            <tbody>';
  echo "<ol start={$start}>";  
     foreach ($out as $kay => $vl) {  echo $vl;  }
        echo "</ol>"; 
        echo '</tbody></table>';
         echo $navig_bottom; 
}
else 
{
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=search_books'></HEAD></HTML>";
   return;  
}
?>
<div id="notice">
      <p class="note"><strong>Примечание:</strong> Мы надеемся, что многие получат пользу от этих материалов. Однако во избежание недоразумений мы просим не копировать, не загружать и не переиздавать данные материалы ни электронными, ни какими-либо другими средствами. Авторские права на все материалы принадлежат «Коллектору библейской книги» и Living Stream Ministry. Мы надеемся, что все наши посетители отнесутся к этой просьбе с уважением.</p> <!-- &#x25c4; -->

</div>

