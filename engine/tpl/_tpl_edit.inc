<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления шаблонами сайта
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Форма, где указываются параметры шаблона сайта
  //Подключается в модулях tpl_add.inc, tpl_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //название шаблона
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[10],
                                                  "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='')));

  //Имя файла (без расширения)
  if($gl_adm == 'tpl_add')
	 {
	    print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[11],
	                                                    "{field}" => form_create_input("file", $css = 'SiteFInputM', $size ='')));
	 }

  //позиция
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[12],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //основной шаблон
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[13],
                                                  "{field}" => form_create_checkbox("maintpl", $maintpl)));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'button')));

  //скрытые поля
  print form_create_hidden('blague', session_id());
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_tpl', $id_tpl);

  //конец формы
  print form_end();


?>