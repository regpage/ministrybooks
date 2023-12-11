<?php
  //////////////////////////////////////////////////////////////////////////////
  // Конструктор меню
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Форма редакторивания параметров пункта меню
  //Подключается в модуляъ menu_items_add.inc, menu_items_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //формируем теги options для url страниц
  function get_pages_url($prefix, $id_part_prec, $url)
  {
    global $gl_db_prefix;

    $query = "SELECT id_part, title, id_part_prec
                FROM {$gl_db_prefix}parts
               WHERE id_part_prec = {$id_part_prec}
              ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $id_part = $results[$i]['id_part'];
        $id_part_prec = $results[$i]['id_part_prec'];
        $title        = stripslashes($results[$i]['title']);
        $options .= "<optgroup label='{$prefix}{$title}'>";
        $query = "SELECT id_item, title
                    FROM {$gl_db_prefix}parts_items
                   WHERE id_part = {$id_part}
                     AND i_type = 'page'
                   ORDER BY pos";
        $results_i = db_select($query);
        $cnt_i = count($results_i);
        for($b = 0; $b < $cnt_i; $b++)
        {
          $id_item = $results_i[$b]['id_item'];
          $i_title   = stripslashes($results_i[$b]['title']);
          $options .= "<option value='?mb={$id_item}'";
          if($url == "?mb={$id_item}")
            $options .= " selected";
          $options .= ">{$i_title}</option>";
        }
        $options .= "</optgroup>";

        $options .= get_pages_url($prefix .= "{$title} -&gt; ", $id_part, $url);
        if($id_part_prec == 0)
          $prefix = '';

      }
    }
    return($options);
  }
  $pages_url_opt = get_pages_url('', 0, $url);

  //формируем теги options для url модулей
  $mod_url_opt = '';
  $mod_url_opt .= "<optgroup label='{$l_menu[34]}'>";
  $mod_url_opt .= "<option value='?mod=users_list_pub'>{$l_menu[35]}</option>";
  $mod_url_opt .= "<option value='?mod=users_edit_pub'>{$l_menu[36]}</option>";
  $mod_url_opt .= "<option value='?mod=users_chpsw_pub'>{$l_menu[37]}</option>";
  $mod_url_opt .= "<option value='?mod=users_add'>{$l_menu[38]}</option>";
  $mod_url_opt .= "<option value='?mod=auth'>{$l_menu[39]}</option>";
  $mod_url_opt .= "<option value='[USERS_ADD]'>{$l_menu[40]}</option>";
  $mod_url_opt .= "<option value='[ENTEREXIT]'>{$l_menu[41]}</option>";
  $mod_url_opt .= "</optgroup>";
  $mod_url_opt .= "<optgroup label='{$l_menu[42]}'>";
  $mod_url_opt .= "<option value='?adm=main'>{$l_menu[43]}</option>";
  $mod_url_opt .= "<option value='?mod=sitemap'>{$l_menu[44]}</option>";
  $mod_url_opt .= "<option value='?mod=search'>{$l_menu[45]}</option>";
  $mod_url_opt .= "</optgroup>";

  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");


  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //параметры пункта, заголовок
  print work_template($tbl_section_tpl,    array("{caption}" => $l_menu[46]));

  //название
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[47],
                                                  "{field}" => form_create_input("caption", $css = 'SiteFInputM', $size ='')));

  //позиция
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[48],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //ссылка, заголовок
  print work_template($tbl_section_tpl,    array("{caption}" => $l_menu[49]));

  //url
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[50],
                                                  "{field}" => form_create_input("url", $css = 'SiteFInputM', $size ='')));

  //выбрать url страницы
  print work_template($form_line_tpl,    array("{caption}" => $l_menu[51],
                                               "{field}" => form_create_select('pg_url', $pages_url_opt, $css = 'SiteFInputM', '', "document.edit_form.url.value=document.edit_form.pg_url.value")));

  //выбрать url модуля
  print work_template($form_line_tpl,    array("{caption}" => $l_menu[52],
                                               "{field}" => form_create_select('mod_url', $mod_url_opt, $css = 'SiteFInputM', '', "document.edit_form.url.value=document.edit_form.mod_url.value")));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_item', $id_item);
  print form_create_hidden('id_item_prec', $id_item_prec);
  print form_create_hidden('id_menu', $id_menu);

  //конец формы
  print form_end();


?>