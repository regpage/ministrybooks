<?php
  //////////////////////////////////////////////////////////////////////////////
  //  арта сайта
  //////////////////////////////////////////////////////////////////////////////

  //выводит пункты меню в развернутом виде (с подпунктами) $id_menu в карту сайта
  //рекурсивна€ функци€
  //$id_item_prec - id_item родительского пункта меню
  //$indent - отступ дл€ вложенных пунктов
  function sm_print_items($id_menu, $id_item_prec, $indent)
  {
    global $gl_db_prefix;

    $query = "SELECT id_item, caption, url
                FROM {$gl_db_prefix}menu_items
               WHERE id_menu = {$id_menu}
               AND id_item_prec = {$id_item_prec}";
    $results = db_select($query);
    if(is_array($results))
    {
      if($indent != 0)
      {
        for($b = 0; $b < $indent; $b++)
          $nbsp .= '&nbsp;';
      }

      $cnt = count($results);
    	 for($i = 0; $i < $cnt; $i++)
	     {
        $i_caption = stripslashes($results[$i]['caption']);
        $url = stripslashes($results[$i]['url']);
        $id_item = $results[$i]['id_item'];


        print "<a href='{$url}'>{$nbsp}{$i_caption}</a><br>";
        sm_print_items($id_menu, $id_item, $indent + 3);
      }
    }
  }

  //заголовок
  print "<h1>{$l_sitemap[1]}</h1>";

  //выборка меню
  $query = "SELECT id_menu, title
              FROM {$gl_db_prefix}menu
            ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $m_title = stripslashes($results[$i]['title']);
      $id_menu = $results[$i]['id_menu'];
      print "<h2>{$m_title}</h2>";
      print "<p>";
        sm_print_items($id_menu, 0, 0);
      print "</p>";
    }
  } else print "<p>{$l_sitemap[2]}</p>";


?>