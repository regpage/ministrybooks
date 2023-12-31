<?php
  //////////////////////////////////////////////////////////////////////////////
  // �����, ��� ����������� ��������� ���� �����
  // ������������ � ������ regform_fields_fields_add.inc � regform_fields_fields_edit.inc
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
  print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[10]));

  //��� ����
  if($type != 'groupe_title')
  {
		  if($gl_adm != 'regform_fields_edit')
		  {
		  	 print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[11],
			                                                   "{field}" => form_create_input("field_name", $css = 'SiteFInputM', $size ='')));
    }
  }
  //�������� ����
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[12],
                                                  "{field}" => form_create_input("caption", $css = 'SiteFInputM', $size ='')));
  if($type != 'groupe_title')
  {
  	 //������������
	   print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[13],
	                                                   "{field}" => form_create_checkbox("oblig", $oblig)));

	   //���������� � ������ �������������
	   print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[55],
	                                                   "{field}" => form_create_checkbox("in_users_list", $in_users_list)));
  }

  //�������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[14],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //�������� textarea
  if($type == 'text')
  {
    //��������� �������� text
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[15]));

    //�������� �� ���������
    print work_template($form_line_tpl,    array("{caption}" => $l_regform_fields[16],
                                                   "{field}" => form_create_textarea('default_value', $rows = '6', $css = 'SiteFTextareaM')));
  }

  //�������� textarea
  if($type == 'textarea')
  {
    //��������� �������� textarea
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[17]));

    //�������� �� ���������
    print work_template($form_line_tpl,    array("{caption}" => $l_regform_fields[18],
                                                   "{field}" => form_create_textarea('default_value', $rows = '6', $css = 'SiteFTextareaM')));

    //���������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[19],
                                                    "{field}" => form_create_input("num_rows", $css = 'SiteFInputM', $size ='')));
  }

  //�������� checkbox
  if($type == 'checkbox')
  {
    //��������� �������� �����
    if(empty($yes_rep)) $yes_rep = $l_regform_fields[20];
    if(empty($no_rep))  $no_rep = $l_regform_fields[21];

    //��������� �������� checkbox
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[22]));

    //������������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[23],
                                                    "{field}" => form_create_input("yes_rep", $css = 'SiteFInputM', $size ='')));

    //������������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[24],
                                                    "{field}" => form_create_input("no_rep", $css = 'SiteFInputM', $size ='')));

    //�������/�� �������
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[25],
                                                    "{field}" => form_create_checkbox("checked", $checked)));

  }

  //�������� radio
  if($type == 'radio')
  {
    //��������� �������� radio
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[26]));

    //�����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[27],
                                                    "{field}" => form_create_input("options", $css = 'SiteFInputM', $size ='')));
  }

  if($type == 'select')
  {
    //��������� �������� select
    print work_template($tbl_section_tpl,    array("{caption}" => $l_regform_fields[28]));

    //�����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[29],
                                                    "{field}" => form_create_input("options", $css = 'SiteFInputM', $size ='')));

    //������ ������
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[30],
                                                    "{field}" => form_create_input("height", $css = 'SiteFInputM', $size ='')));

    //������������� �����
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_regform_fields[31],
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