<?php    
//шапка таблицы
print "<ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главая</a></li>
      <li><a href='?mod=witness_lee_books'>Книги Уитнесса Ли</a></li>
      <li class='current'><a href='?mod=life_study'>Заключительные сообщения по Новому Завету</a></li>
    </ul>";
print "<h2>Книги Уитнесса Ли</h2>";
print "<dl class='sub-nav'>
      <dt></dt>
      <dd><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd class='active'><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd>
    </dl><hr>";
print "<div class='large-10 push-2 columns'>";
print "<h3>Заключительные сообщения по Новому Завету</h3>";
//Cначала выбераем автора, его ID
     $author="Уитнесс Ли";
     $query = "SELECT id_author
                FROM {$gl_db_prefix}parts_author
                WHERE author = '{$author}'";
      $id_author = db_select_one($query);
    // Затем выбераем поиск всех жизнеизучений
      $type="Заключительные сообщения";
    //выводим страницы подкатегории
    $query = "SELECT *
                FROM {$gl_db_prefix}parts_items
               WHERE title like '%{$type}%'AND id_author like '{$id_author}' ORDER BY title ASC, pos";
    $results = db_select($query);
    if(is_array($results))
    {

print "<ol class='bullet'>";
      //print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";  
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $id_item  = $results[$i]['id_item'];
        $id_parts  = $results[$i]['id_part'];
        $type     = $results[$i]['i_type'];
        $pos      = $results[$i]['pos'];
        $title    = stripslashes($results[$i]['title']);
        $id_author    = stripslashes($results[$i]['id_author']);        
        $mod_name = $results[$i]['mod_name'];
        //$params   = $results[$i]['params'];
	 $params = unserialize(stripslashes($results[$i]['params']));
	 $descr = $params['descr'];
        //$params   = unserialize(stripslashes($params)); 
          
         //print "<tr>";
         //позиция
         //print "<td class='SiteTblLeft'>{$pos}</td>";
         //заголовок
         print "<li><a class ='contentpagetitle' href='?mb={$id_item}'>{$title}</a><br>{$descr}</li>"; 
         //print "</tr>";
      }
print "</div>";
print "<div class='large-2 pull-10 columns'>
          <div class='covers'>
            <img src='http://kbk.ru/wa-data/public/shop/products/21/02/221/images/526/526.970.jpg' alt='The Life-Study of the Bible (cover img)' class='coverimg'>
            <p>Печатные копии <a href='http://kbk.ru/category/prints/life-study/'>доступны на сайте Коллектора библейской книги</a></p>
          </div>
        </div>";
print "<hr><dl class='sub-nav'>
      <dt></dt>
      <dd><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd class='active'><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd>
    </dl>";
print "<div class='to-top'><a href='#top' class='scroll'>в начало</a></div>";

    }
?>

