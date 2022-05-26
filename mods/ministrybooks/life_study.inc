<?php
//шапка таблицы
print "<ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главая</a></li>
      <li><a href='?mod=witness_lee_books'>Книги Уитнесса Ли</a></li>
      <li class='current'><a href='?mod=life_study'>Жизнеизучение Библии</a></li>
    </ul>";
print "<h2>Книги Уитнесса Ли</h2>";
print "<dl class='sub-nav'>
      <dt></dt>
      <dd><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd class='active'><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd>
    </dl><hr>";
print "<div class='large-10 push-2 columns'>";
print "<h3>Жизнеизучение Библии</h3>";
    //Cначала выбераем автора, его ID
     $author="Уитнесс Ли";
     $old_testement="Ветхий Завет";
     $new_testement="Новый Завет";
     $query = "SELECT id_author
                FROM {$gl_db_prefix}parts_author
                WHERE author = '{$author}'";
      $id_author = db_select_one($query);
// Затем выбераем поиск всех жизнеизучений
      $type="Жизнеизучение";
      $nottype="Заключительные сообщения по Новому Завету";
//выводим страницы подкатегории
   $query = "SELECT id_part
                FROM {$gl_db_prefix}parts
               WHERE title='{$old_testement}'";
    $id_part = db_select_one($query);

    $query = "SELECT *
                FROM {$gl_db_prefix}parts_items
               WHERE title like '%{$type}%'AND id_author like '{$id_author}' AND title not like '%{$nottype}%' AND id_part='{$id_part}'ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
print "<h4 class='subheader'>{$old_testement}</h4>";
print "<ol class='decimal'>";  
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
        $params   = $results[$i]['params'];
        $params   = unserialize(stripslashes($params));        
         
//заголовок
          print "<li><a class ='contentpagetitle' href='?mb={$id_item}'>{$title}</a></li>"; 

      }
print "</ol>";
    }
//Новый Завет
     $author="Уитнесс Ли";
     $old_testement="Ветхий Завет";
     $new_testement="Новый Завет";
     $query = "SELECT id_author
                FROM {$gl_db_prefix}parts_author
                WHERE author = '{$author}'";
      $id_author = db_select_one($query);
// Затем выбераем поиск всех жизнеизучений
      $type="Жизнеизучение";
      $nottype="Заключительные сообщения по Новому Завету";
//выводим страницы подкатегории
    $query = "SELECT id_part
                FROM {$gl_db_prefix}parts
               WHERE title='{$new_testement}'";
    $id_part_new = db_select_one($query);

    $query = "SELECT *
                FROM {$gl_db_prefix}parts_items
               WHERE title like '%{$type}%'AND id_author like '{$id_author}' AND title not like '%{$nottype}%' AND id_part='{$id_part_new}'ORDER BY pos";
    $results = db_select($query);

    if(is_array($results))
   {
//шапка таблицы
print "<h4 class='subheader'>{$new_testement}</h4>";
print "<ol class='decimal'>";  
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
        $params   = $results[$i]['params'];
        $params   = unserialize(stripslashes($params));         
 //заголовок
          print "<li><a class ='contentpagetitle' href='?mb={$id_item}'>{$title}</a></li>";
      }
print "</ol>";
print "</div>";
print "<div class='large-2 pull-10 columns'>
          <div class='covers'>
            <img src='http://kbk.ru/wa-data/public/shop/products/41/12/1241/images/751/751.400.jpg' alt='The Life-Study of the Bible (cover img)' class='coverimg'>
            <p>Печатные копии <a href='http://kbk.ru/category/prints/life-study/'>доступны на сайте Коллектора библейской книги</a></p>
          </div>
        </div>";
print "<hr><dl class='sub-nav'>
      <dt></dt>
      <dd><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd class='active'><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd>
    </dl>";
print "<div class='to-top'><a href='#top' class='scroll'>в начало</a></div>";
    }
?>

