<?php
  //////////////////////////////////////////////////////////////////////////////
  // Конструктор меню
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Функции построения меню
  //////////////////////////////////////////////////////////////////////////////

  //формирует и выводит меню $id_menu
  function create_menu($id_menu)
  {
    global $gl_path_to_templates, $gl_subdir, $site_begin_id_item, $gl_page, $gl_mod, $l_gen, $l_menu, $gl_db_prefix;

    $query = "SELECT disposition, `separator`
                FROM {$gl_db_prefix}menu
               WHERE id_menu = {$id_menu}";
    $results = db_select($query);
    $disposition = $results[0]['disposition'];
    $separator   = stripslashes($results[0]['separator']);
    $separator   = str_replace(" ", '&nbsp;', $separator);
    if(empty($separator))
      $separator = '&nbsp;|&nbsp;';

    if($disposition == 'horizontal')
    {
      create_hor_menu($id_menu, $separator) ;
    }
    else
    {
      $tpl_main = file_get_contents("{$gl_path_to_templates}menu/v_main.htm");
      $items = create_vert_menu($id_menu, 0, $set_vt, 0) ;
      print work_template($tpl_main,    array("{items}" => $items));
    }

  }

  //формирует и выводит горизонтальное меню $id_menu
  //пункты разделяются разделителем $separator
  //вызывается в теле функции create_menu()
  function create_hor_menu($id_menu, $separator)
  {
    global $gl_path_to_templates, $gl_subdir, $site_begin_id_item, $gl_page, $gl_mod, $gl_group, $l_gen, $l_menu, $gl_db_prefix;

    $tpl_main = file_get_contents("{$gl_path_to_templates}menu/h_main.htm");
    $tpl_item = file_get_contents("{$gl_path_to_templates}menu/h_item.htm");

      $query = "SELECT caption, url
                  FROM {$gl_db_prefix}menu_items
                 WHERE id_menu = {$id_menu}
                 AND id_item_prec = 0
                 ORDER BY pos";
      $results = db_select($query);
      if(is_array($results))
      {
        $cnt = count($results);
        for($i = 0; $i < $cnt; $i++)
        {
          $url = stripslashes($results[$i]['url']);
          $caption = stripslashes($results[$i]['caption']);

          $reg_pg = "/mb=([0-9]+)/i";
          $reg_mod = "/mod=([a-z0-9_]+)/i";
          //print $url;
          if(preg_match("/\[[0-9a-z_]+\]/i", $url))
          {
            if($url == '[ENTEREXIT]')
            {
              if($gl_group != 'unregistered')
                $caption =  "<a href='?act=auth_exit'>{$l_menu[1]}</a>";
              else
              {
                if($gl_mod != 'auth')
                  $caption =  "<a href='?mod=auth'>{$l_menu[2]}</a>";
                else
                  $caption = $l_menu[2];
              }
            }
            if($url == '[USERS_ADD]')
            {

              if($gl_group == 'unregistered')
                $caption = "<a href='?mod=users_add'>{$l_menu[3]}</a>";
              else
                $caption = '';
            }
          }
          else
          {
                   if(preg_match($reg_pg, $url, $matches))
                   {

                     if($gl_page != $matches[1])
                       $caption =  "<a href='{$url}'>{$caption}</a>";
                   }
                   elseif(preg_match($reg_mod, $url, $matches))
                   {

                     if($gl_mod != $matches[1])
                       $caption =  "<a href='{$url}'>{$caption}</a>";

                   }
                   else
                     $caption =  "<a href='{$url}'>{$caption}</a>";
          }
          if($i != $cnt - 1)
            $caption .= $separator;
          if(!empty($caption))
            $items .= work_template($tpl_item,    array("{caption}" => $caption));
        }

        print work_template($tpl_main,    array("{items}" => $items));
      }
  }

  //рекурсивная функция, формирует и возвращает пункты и подпункты вертикального меню $id_menu
  //вызывается в теле функции create_menu()
  //$id_item_prec - id родительского пункта
  //$set_vt - id родительских пунктов, разделенных точкой с запятой (для определения вложенности)
  //level - вложенность, число, прибавляется к имени css-класса
  function create_vert_menu($id_menu, $id_item_prec, $set_vt, $level)
  {
    global $gl_path_to_templates, $gl_subdir, $site_begin_id_item, $gl_page, $gl_mod, $gl_group, $l_gen, $l_menu, $gl_db_prefix;


    $tpl_item = file_get_contents("{$gl_path_to_templates}menu/v_item.htm");

    $vt = preg_replace("/[^;0-9]/", "", $_GET['vt']);
    //$set_vt = $vt;
    $vt = explode(";", $vt);
    if(is_array($vt))
    {
      $cnt_vt = count($vt);
      for($i = 0; $i < cnt_vt; $i++)
        $vt[$i] = intval($vt[$i]);
    }


      $query = "SELECT id_item, caption, url
                  FROM {$gl_db_prefix}menu_items
                 WHERE id_menu = {$id_menu}
                 AND id_item_prec = {$id_item_prec}
                 ORDER BY pos";
      $results = db_select($query);
      if(is_array($results))
      {
        $cnt = count($results);
        for($i = 0; $i < $cnt; $i++)
        {
          $url = stripslashes($results[$i]['url']);
          $id_item = $results[$i]['id_item'];
          $caption = stripslashes($results[$i]['caption']);

          if(preg_match("/\[[0-9a-z_]+\]/i", $url))
          {
            if($url == '[ENTEREXIT]')
            {
              if($gl_group != 'unregistered')
                $caption =  "<a href='?act=auth_exit'>{$l_menu[1]}</a>";
              else
              {
                if($gl_mod != 'auth')
                  $caption =  "<a href='?mod=auth'>{$l_menu[2]}</a>";
                else
                  $caption = $l_menu[2];
              }
            }
            if($url == '[USERS_ADD]')
            {
              if($gl_group == 'unregistered')
                $caption = "<a href='?mod=users_add'>{$l_menu[3]}</a>";
              else
                $caption = '';
            }
          }
          else
          {

                   $reg_pg = "/mb=([0-9]+)/i";
                   $reg_mod = "/mod=([a-z0-9_]+)/i";
                   if(preg_match($reg_pg, $url, $matches))
                   {

                     if($gl_page != $matches[1])
                     {
                       $caption =  "<a href='{$url}&vt={$set_vt}{$id_item};'>{$caption}</a>";
                       $css_name = "VertMenuItem".($level+1);
                     }
                     else $css_name = "VertMenuItemSel".($level+1);

                   }
                   elseif(preg_match($reg_mod, $url, $matches))
                   {

                     if($gl_mod != $matches[1])
                     {
                       $caption =  "<a href='{$url}&vt={$set_vt}{$id_item};'>{$caption}</a>";
                       $css_name = "VertMenuItem".($level+1);
                     }
                     else $css_name = "VertMenuItemSel".($level+1);
                   }
                   else
                     { $caption =  "<a href='{$url}'>{$caption}</a>"; $css_name = "VertMenuItem".($level+1); }
          }

          if(!empty($caption))
                   $items .= work_template($tpl_item,    array("{caption}" => $caption,
                                                               "{css_cl}" => $css_name));
          $css_name = '';
          if(in_array($id_item, $vt))
          {
            $items .= create_vert_menu($id_menu, $id_item, $set_vt."{$id_item};", $level + 1);
          }
        }


      }
      return $items;
  }

?>
