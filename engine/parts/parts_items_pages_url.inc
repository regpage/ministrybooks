<?php
  //////////////////////////////////////////////////////////////////////////////
  // —истема управлени€ разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ћодуль выдает список url страницы id_item
  //////////////////////////////////////////////////////////////////////////////


  //инициализаци€ переменных
  $id_part_prec = intval($_GET['id_part_prec']);
  $id_item      = intval($_GET['id_item']);

  //выбираем заголовок страницы
  $query = "SELECT title
              FROM {$gl_db_prefix}parts_items
             WHERE id_item = {$id_item}";
  $title = stripslashes(db_select_one($query));

  print "<h1>{$l_parts[66]} :: {$title}</h1>";
  print "<p>";
    print "<b>{$l_parts[67]}</b><br>";
    print "<br>";
    print "<a href='?mb={$id_item}' target='_blank'>?mb={$id_item}</a><br>";
    print "<br>";

    print "<b>{$l_parts[68]}</b><br>";
    print "<br>";
    print "<a href='{$gl_site}?mb={$id_item}' target='_blank'>{$gl_site}?mb={$id_item}</a><br>";
    print "<br>";
    print "{$l_parts[69]}<br><br>";
    print "&lt;?php include(\"content/{$id_item}/{$id_item}.inc\"); ?&gt;";

    print "<br><br>";
    print "<b>{$l_parts[70]}:</b><br>";
    print "<br>";
    print "<a href='?mod=print_page&mb={$id_item}' target='_blank'>?mod=print_page&mb={$id_item}</a><br>";
    print "<br><br>";
  print "</p>";

  //ссылка назад
  print "<p><a class='Mustgreen' href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_adm_gen[11]}</a></p>";


?>