<?php

  //////////////////////////////////////////////////////////////////////////////
  // �����, ��� ����������� ��������� ���� �����
  // ������������ � ������ forms_fields_add.inc � forms_fields_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //��������� ������� � ����������
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $tbl_section_tpl  = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('catitem_edit_form', '', 'post', 'multipart');

  //��������� ����� ����
  print work_template($tbl_section_tpl,    array("{caption}" => $l_forms[6]));

  //��� ����
  if($type != 'groupe_title')
  	 print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[7],
	                                                   "{field}" => form_create_input("field_name", $css = 'SiteFInputM', $size ='')));

  //�������� ����
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[8],
                                                  "{field}" => form_create_input("caption", $css = 'SiteFInputM', $size ='')));
  if($type != 'groupe_title')
  	 //������������
	   print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[9],
	                                                   "{field}" => form_create_checkbox("oblig", $oblig)));

  //�������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[10],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //�������� textarea
  if($type == 'text')
  {
    //��������� �������� text
    print work_template($tbl_section_tpl,    array("{caption}" => $l_forms[11]));

    //�������� �� ���������
    print work_template($form_line_tpl,    array("{caption}" => $l_forms[12],
                                                   "{field}" => form_create_textarea('default_value', $rows = '6', $css = 'SiteFTextareaL')));
  }

  //�������� textarea
  if($type == 'textarea')
  {
    //��������� �������� textarea
    print work_template($tbl_section_tpl,    array("{caption}" => $l_forms[13]));

    //�������� �� ���������
    print work_template($form_line_tpl,    array("{caption}" => $l_forms[14],
                                                   "{field}" => form_create_textarea('default_value', $rows = '6', $css = 'SiteFTextareaL')));

    //���������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[15],
                                                    "{field}" => form_create_input("num_rows", $css = 'SiteFInputM', $size ='')));
  }

  //�������� checkbox
  if($type == 'checkbox')
  {
    //��������� �������� �����
    if(empty($yes_rep)) $yes_rep = $l_forms[16];
    if(empty($no_rep))  $no_rep = $l_forms[17];

    //��������� �������� checkbox
    print work_template($tbl_section_tpl,    array("{caption}" => $l_forms[18]));

    //������������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[19],
                                                    "{field}" => form_create_input("yes_rep", $css = 'SiteFInputM', $size ='')));

    //������������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[20],
                                                    "{field}" => form_create_input("no_rep", $css = 'SiteFInputM', $size ='')));

    //�������/�� �������
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[21],
                                                    "{field}" => form_create_checkbox("checked", $checked)));

  }

  //�������� radio
  if($type == 'radio')
  {
    //��������� �������� radio
    print work_template($tbl_section_tpl,    array("{caption}" => $l_forms[22]));

    //�����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[23],
                                                    "{field}" => form_create_input("options", $css = 'SiteFInputM', $size ='')));
  }

  if($type == 'select')
  {
    //��������� �������� select
    print work_template($tbl_section_tpl,    array("{caption}" => $l_forms[24]));

    //�����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[25],
                                                    "{field}" => form_create_input("options", $css = 'SiteFInputM', $size ='')));

    //������ ������
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[26],
                                                    "{field}" => form_create_input("height", $css = 'SiteFInputM', $size ='')));

    //������������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[27],
                                                    "{field}" => form_create_checkbox("multiple", $multiple)));
  }

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                             "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague',    session_id());
  print form_create_hidden('id_form',   $id_form);
  print form_create_hidden('id_field',  $id_field);
  print form_create_hidden('old_pos',   $old_pos);
  print form_create_hidden('old_field_name',   $old_field_name);
  print form_create_hidden('page',      $page);
  print form_create_hidden('type',      $type);


  //����� �����
  print form_end();


?>