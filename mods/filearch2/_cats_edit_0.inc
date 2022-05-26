<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // ‘орма, где указываютс€ параметры категории
  // ѕодключаетс€ в модул€х filearch2_cats_add.inc и filearch2_cats_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('item_edit_form', '', 'post', 'multipart');

  //поле заголовок
  print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[10],
                                               "{field}"   => form_create_input("title", $css = 'SiteFInputM', $size ='') ));

  /*if($gl_mod != 'filearch2_cats_edit')
  {
    //директори€
    print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[11],
	                                                "{field}"   => form_create_input("folder", $css = 'SiteFInputM', $size ='') ));

    //создать checkbox
    print work_template($form_line_tpl, array("{caption}"    => $l_filearch2[12],
	                                                "{field}"   => form_create_checkbox("mkdir", $mkdir) ));
  }*/

  //позици€
  print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[13],
                                               "{field}"   => form_create_input("pos", $css = 'SiteFInputM', $size ='') ));

  //описание категории
  print work_template($form_line_tpl,    array("{caption}" => $l_filearch2[14],
	                                                  "{field}" => form_create_bbcodeeditor("{$gl_path_to_engine_root}ext_prm/bbcodeeditor/", 'small', 'descr', $descr, "SiteFTextareaM", "10", "{$gl_admin_url}ext_prm/bbcodeeditor/")));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые пол€
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_cat',  $id_cat);

  //конец формы
  print form_end();


?>