<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� � ����������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //����� ���������/��������� ���������� ��������
  //������������ � ������ parts_add.inc, parts_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //�������� �������� ������ �����
  /*if(empty($id_tpl))
  {
    $query = "SELECT id_tpl
                FROM sitetpl
               WHERE maintpl = 'yes'";
    $id_tpl = db_select_one($query);
  }*/

  //����� ��� select'� ������ �������
  if($gl_mod != 'parts_add')
    $options = form_get_options_from_db("sitetpl", "id_tpl", "title", $id_tpl);
  else
    $options = form_get_options_from_db("sitetpl", "id_tpl", "title", 0);
  $options = "<option value='0'>{$l_parts[74]}</option>".$options ;


  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '', 'post', 'multipart');

  //��������� �������
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[25]));

  //��������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[26],
                                               "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='')));

  //�������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[27],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //������, ���������
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[28]));

  //������
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[29],
                                                  "{field}" => form_create_select("id_tpl", $options, "SiteFInputM")));

  //��������� � �����������
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[30],
                                                  "{field}" => form_create_checkbox("tpl_on_subparts", $tpl_on_subparts)));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague', session_id());
  print form_create_hidden('id_part_prec', $id_spo);
  print form_create_hidden('id_part', $id_cat);
  print form_create_hidden('old_pos', $old_pos);

  //����� �����
  print form_end();


?>