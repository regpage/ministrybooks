<?php
  //////////////////////////////////////////////////////////////////////////////
  // ����������� ����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //����� �������������� ���������� ����
  //������������ � ������� menu_add.inc, menu_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //����� ��� select'a ������������ �������
  $disp_opt = "<option value='vertical'";
  if($disposition == 'vertical')
    $disp_opt .= ' selected';
  $disp_opt .= ">{$l_menu[12]}</option>";
  $disp_opt .= "<option value='horizontal'";
  if($disposition == 'horizontal')
    $disp_opt .= ' selected';
  $disp_opt .= ">{$l_menu[13]}</option>";

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '', 'post', 'multipart');

  //��������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[14],
                                                  "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='')));

  //������������ �������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[15],
                                                  "{field}" => form_create_select("disposition", $disp_opt, $css = 'SiteFInputM')));

  //�����������
  print work_template($form_line_tpl,    array("{caption}" => $l_menu[16],
                                                  "{field}" => form_create_input("separator", $css = 'SiteFInputM', $size ='')));

  //�������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[17],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague', session_id());
  print form_create_hidden('old_pos', $old_pos);

  //����� �����
  print form_end();


?>