<?php
//шапка таблицы
print "<ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главая</a></li>
      <li><a href='?mod=witness_lee_books'>Книги Уитнесса Ли</a></li>
      <li class='current'><a href='?mod=life_study'>Вершина божественного откровения</a></li>
      </ul>";
print "<h2>Книги Уитнесса Ли</h2>";
print "<dl class='sub-nav'>
      <dt></dt>
      <dd><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd class='active'><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd>
    </dl><hr>";
print "<h3>Вершина божественного откровения</h3>";
print "<p>Начиная с Международной китайскоязычной конференции в начале 1994 года, служение брата Уитнесса Ли было сосредоточено на том, что он сам называл вершиной божественного откровения: на том, что <em>Бог стал человеком, чтобы человек стал Богом по жизни и природе, но не в Божестве</em>. Представленные здесь книги Уитнесса Ли включают сообщения, раскрывающие эту важнейшую истину.</p>";
//Cначала выбераем автора, его ID
     $author="Уитнесс Ли";
     $query = "SELECT id_author
                FROM {$gl_db_prefix}parts_author
                WHERE author = '{$author}'";
      $id_author = db_select_one($query);
    // Затем выбераем поиск всех жизнеизучений
    //выводим страницы подкатегории
    $query = "SELECT *
                FROM {$gl_db_prefix}parts_items
               WHERE date >= '1994-01-01' AND date <= '1997-08-01' ORDER BY title";
    $results = db_select($query);
    if(is_array($results))
    {
print "<ol class='decimal'>";
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
        $params   = $results[$i]['params'];
        $params   = unserialize(stripslashes($params));

          //заголовок
          print "<li><a class ='contentpagetitle' href='?mb={$id_item}'>{$title}</a></li>";
      }
print "</ol>";
print "<hr><dl class='sub-nav'>
      <dt></dt>
      <dd><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd class='active'><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd>
    </dl>";
print "<div class='to-top'><a href='#top' class='scroll'>в начало</a></div>";

    }
?>
