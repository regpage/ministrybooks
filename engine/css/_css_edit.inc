<?php
  //////////////////////////////////////////////////////////////////////////////
  // CSS Editor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //�����, ������������ � css_add.inc � css_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '', 'post', 'multipart');

  //��� �����
	 print work_template($form_lineobl_tpl,    array("{caption}" => $l_css[8],
	                                                 "{field}" => form_create_input("file", $css = 'SiteFInputM', $size ='')));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague', session_id());

  //����� �����
  print form_end();


?>