<?php
  //////////////////////////////////////////////////////////////////////////////
  //Форма изменения параметров изображения блока,
  //подключается в модулях images_add.inc и images_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');


  //название
  print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[61],
                                                 "{field}" => form_create_input("title", 'SiteFInputM', $size ='') ));

  //уменьшенная копия изображения
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_blockeditor[62],
                                                  "{field}" => form_create_file("img_min", $css = 'SiteFInputM', $size ='64')));

  //увеличенная копия изображения:
  print work_template($form_line_tpl,    array("{caption}" => $l_blockeditor[63],
                                                  "{field}" => form_create_file("img_max", $css = 'SiteFInputM', $size ='64')));

  //позиция
  print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[64],
                                               "{field}" => form_create_input("pos", 'SiteFInputM', $size ='') ));

  //пояснительный текст
  print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[65],
                                                 "{field}"   => form_create_bbcodeeditor("{$gl_path_to_engine_root}ext_prm/bbcodeeditor/", 'small', 'text', $text, "SiteFTextareaM", "10", "{$gl_admin_url}ext_prm/bbcodeeditor/")));
  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());
  //print form_create_hidden('block_gen_type', $block_gen_type);
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_block', $id_block);
  print form_create_hidden('pg', $ed_pg);
  print form_create_hidden('id_img', $id_img);
  print form_create_hidden('old_img_min', $old_img_min);
  print form_create_hidden('old_img_max', $old_img_max);

  //конец формы
  print form_end();
?>