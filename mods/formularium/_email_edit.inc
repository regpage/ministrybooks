<?php
  //////////////////////////////////////////////////////////////////////////////
  // �����, ��� ����������� ��������� ������ �������� ��������� �����
  // ������������ � ������ forms_email_add.inc � forms_email_edit.inc
  //////////////////////////////////////////////////////////////////////////////

  //��������� �������
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '', 'post', 'multipart');

  //e-mail �����
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[1],
                                                  "{field}" => form_create_input("email", $css = 'SiteFInputM', $size ='')));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                             "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague',    session_id());
  print form_create_hidden('id_form',   $id_form);
  print form_create_hidden('id_email',  $id_email);

  //����� �����
  print form_end();


?>