<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� �����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //�����, ��� ����������� ��������� ������� �����
  //������������ � ������� tpl_add.inc, tpl_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '', 'post', 'multipart');

  //�������� �������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[10],
                                                  "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='')));

  //��� ����� (��� ����������)
  if($gl_adm == 'tpl_add')
	 {
	    print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[11],
	                                                    "{field}" => form_create_input("file", $css = 'SiteFInputM', $size ='')));
	 }

  //�������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[12],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //�������� ������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_tpl[13],
                                                  "{field}" => form_create_checkbox("maintpl", $maintpl)));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'button')));

  //������� ����
  print form_create_hidden('blague', session_id());
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_tpl', $id_tpl);

  //����� �����
  print form_end();


?>