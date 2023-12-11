<?php

  //////////////////////////////////////////////////////////////////////////////
  //форма, где указыываются параметры соответствия
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выбираем шаблоны сайта в виде опций select'a
  $tpl_options = form_get_options_from_db("sitetpl", "id_tpl", "title", $id_tpl);
  $tpl_options = "<option value='0'>{$l_url_and_sitetpl[3]}</option>".$tpl_options;

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //шаблон сайта
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_url_and_sitetpl[1],
                                                  "{field}" => form_create_select("id_tpl", $tpl_options, "SiteFInputM")));

  //заголовок модуля
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_url_and_sitetpl[2],
                                                  "{field}" => form_create_input("url", $css = 'SiteFInputM', $size ='')));

  //позиция
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_url_and_sitetpl[4],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_item', $id_item);

  //конец формы
  print form_end();

?>