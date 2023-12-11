<?php
  //////////////////////////////////////////////////////////////////////////////
  // Форма, где указываются параметры поля формы
  // Подключается в модуля regform_fields_fields_add.inc и regform_fields_fields_edit.inc
  //////////////////////////////////////////////////////////////////////////////

  //загружаем шаблоны в переменные
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $tbl_section_tpl  = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('catitem_edit_form', '', 'post', 'multipart');

  //заголовок опции поля
  print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[10]));

  //имя поля
  if($type != 'groupe_title')
  {
		  if($gl_adm != 'regform_fields_edit')
		  {
		  	 print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[11],
			                                                   "{field}" => form_create_input("field_name", $css = 'SiteFInputM', $size ='')));
    }
  }
  //название поля
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[12],
                                                  "{field}" => form_create_input("caption", $css = 'SiteFInputM', $size ='')));
  if($type != 'groupe_title')
  {
  	 //обязательное
	   print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[13],
	                                                   "{field}" => form_create_checkbox("oblig", $oblig)));

	   //показывать в списке пользователей
	   print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[55],
	                                                   "{field}" => form_create_checkbox("in_users_list", $in_users_list)));
  }

  //позиция
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[14],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //свойства textarea
  if($type == 'text')
  {
    //заголовок Свойства text
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[15]));

    //значение по умолчанию
    print work_template($form_line_tpl,    array("{caption}" => $l_regform_fields[16],
                                                   "{field}" => form_create_textarea('default_value', $rows = '6', $css = 'SiteFTextareaM')));
  }

  //свойства textarea
  if($type == 'textarea')
  {
    //заголовок Свойства textarea
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[17]));

    //значение по умолчанию
    print work_template($form_line_tpl,    array("{caption}" => $l_regform_fields[18],
                                                   "{field}" => form_create_textarea('default_value', $rows = '6', $css = 'SiteFTextareaM')));

    //количество строк
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[19],
                                                    "{field}" => form_create_input("num_rows", $css = 'SiteFInputM', $size ='')));
  }

  //свойства checkbox
  if($type == 'checkbox')
  {
    //начальные значения полей
    if(empty($yes_rep)) $yes_rep = $l_regform_fields[20];
    if(empty($no_rep))  $no_rep = $l_regform_fields[21];

    //заголовок Свойства checkbox
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[22]));

    //положительный ответ
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[23],
                                                    "{field}" => form_create_input("yes_rep", $css = 'SiteFInputM', $size ='')));

    //отрицательный ответ
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[24],
                                                    "{field}" => form_create_input("no_rep", $css = 'SiteFInputM', $size ='')));

    //отмечен/не отмечен
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[25],
                                                    "{field}" => form_create_checkbox("checked", $checked)));

  }

  //свойства radio
  if($type == 'radio')
  {
    //заголовок Свойства radio
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[26]));

    //Опции
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[27],
                                                    "{field}" => form_create_input("options", $css = 'SiteFInputM', $size ='')));
  }

  if($type == 'select')
  {
    //заголовок Свойства select
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[28]));

    //опции
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[29],
                                                    "{field}" => form_create_input("options", $css = 'SiteFInputM', $size ='')));

    //высота списка
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[30],
                                                    "{field}" => form_create_input("height", $css = 'SiteFInputM', $size ='')));

    //множественный выбор
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[31],
                                                    "{field}" => form_create_checkbox("multiple", $multiple)));
  }

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                             "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague',    session_id());
  print form_create_hidden('id_form',   $id_form);
  print form_create_hidden('id_field',  $id_field);
  print form_create_hidden('old_pos',   $old_pos);
  print form_create_hidden('old_field_name',   $old_field_name);
  print form_create_hidden('page',      $page);
  print form_create_hidden('type',      $type);


  //конец формы
  print form_end();


?>