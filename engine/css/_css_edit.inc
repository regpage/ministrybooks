<?php
  //////////////////////////////////////////////////////////////////////////////
  // CSS Editor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Форма, подключается в css_add.inc и css_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //имя файла
	 print work_template($form_lineobl_tpl,    array("{caption}" => $l_css[8],
	                                                 "{field}" => form_create_input("file", $css = 'SiteFInputM', $size ='')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());

  //конец формы
  print form_end();


?>