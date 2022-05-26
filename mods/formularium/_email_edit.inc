<?php
  //////////////////////////////////////////////////////////////////////////////
  // Форма, где указываются параметры адреса отправки сообщений формы
  // Подключается в модуля forms_email_add.inc и forms_email_edit.inc
  //////////////////////////////////////////////////////////////////////////////

  //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //e-mail адрес
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[1],
                                                  "{field}" => form_create_input("email", $css = 'SiteFInputM', $size ='')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                             "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague',    session_id());
  print form_create_hidden('id_form',   $id_form);
  print form_create_hidden('id_email',  $id_email);

  //конец формы
  print form_end();


?>