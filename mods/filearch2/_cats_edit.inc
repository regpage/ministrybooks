<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // �����, ��� ����������� ��������� ���������
  // ������������ � ������� filearch2_cats_add.inc � filearch2_cats_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //��������� �������
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('item_edit_form', '', 'post', 'multipart');

  //���� ���������
  print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[10],
                                               "{field}"   => form_create_input("title", $css = 'SiteFInputM', $size ='') ));

  /*if($gl_mod != 'filearch2_cats_edit')
  {
    //����������
    print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[11],
	                                                "{field}"   => form_create_input("folder", $css = 'SiteFInputM', $size ='') ));

    //������� checkbox
    print work_template($form_line_tpl, array("{caption}"    => $l_filearch2[12],
	                                                "{field}"   => form_create_checkbox("mkdir", $mkdir) ));
  }*/

  //�������
  print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[13],
                                               "{field}"   => form_create_input("pos", $css = 'SiteFInputM', $size ='') ));

  //�������� ���������
  print work_template($form_line_tpl,    array("{caption}" => $l_filearch2[14],
	"{field}" => form_create_bbcodeeditor("{$gl_path_to_engine_root}ext_prm/bbcodeeditor/", 'small', 'descr', $descr, "SiteFTextareaM", "10", "{$gl_admin_url}ext_prm/bbcodeeditor/")));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_cat',  $id_cat);

  //����� �����
  print form_end();


?>