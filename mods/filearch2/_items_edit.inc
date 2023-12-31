<?php
  //////////////////////////////////////////////////////////////////////////////
  // CMS Ortus
  // File archive M2
  // by Anton Fedorchenko (antf@inbox.ru, antf@pochta.ru)
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //�����, ��� ����������� ��������� �����
  //������������ � ������� filearch2_items_add.inc � filearch2_items_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //������� �������
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $tbl_section_tpl  = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");

  //��������� ����� ��� ������ �����
  $dr = opendir($path);
  while($dir_file = readdir($dr))
  {    if($dir_file != '.' && $dir_file !='..')
    {      $files[] = $dir_file;
    }
  }
  closedir($dr);

  $options = "<option value=''>{$l_filearch2[39]}</option>";
  $cnt = count($files);
  for($i = 0; $i < $cnt; $i++)
  {    $options .= "<option value='{$files[$i]}'";
    if($files[$i] == $file)
      $options .= " selected";
    $options .= ">{$files[$i]}</option>";
  }


  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '', 'post', 'multipart');

  //��������
  print work_template($form_line_tpl, array("{caption}" => $l_filearch2[34],
                                               "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='') ));


  //����, �������
  print work_template($form_line_tpl,    array("{caption}" => $l_filearch2[35],
                                                  "{field}" => form_create_select("file_sel", $options, "SiteFInputM")));

  //����, ���������
  print work_template($form_line_tpl,    array("{caption}" => $l_filearch2[36],
                                                  "{field}" => form_create_file("file", $css = 'SiteFInputM', $size ='64')));


  //�������
  print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[37],
                                               "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='') ));

  //�������� ���������
  print work_template($form_line_tpl,    array("{caption}" => $l_filearch2[38],
	                                                  "{field}" => form_create_bbcodeeditor("{$gl_path_to_engine_root}ext_prm/bbcodeeditor/", 'small', 'descr', $descr, "SiteFTextareaM", "10", "{$gl_admin_url}ext_prm/bbcodeeditor/")));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('old_pos',  $old_pos);
  print form_create_hidden('old_file',  $old_file);
  print form_create_hidden('id_cat', $id_cat);
  print form_create_hidden('id_item', $id_item);
  print form_create_hidden('part', $part);

  //����� �����
  print form_end();
?>