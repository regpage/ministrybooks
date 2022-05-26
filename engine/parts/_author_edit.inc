<?php
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  // 
  if(!empty($errors))
    print form_print_errors($errors);

  // 
  print form_begin('edit_form', '', 'post', 'multipart');

  // 
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[85]));

  // 
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[75],
                                               "{field}" => form_create_input("author", $css = 'SiteFInputM', $size ='')));

  //
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[27],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

//
  //print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[84],
  //                                             "{field}" => form_create_input("about_author", $css = 'SiteFInputM', $size ='')));

// 
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[84],
                                                  "{field}" => form_create_textarea('about_author', $rows = '5', $css = 'SiteFTextareaM'))); 
 
   //
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'button')));

  // 
  print form_create_hidden('blague', session_id());
  print form_create_hidden('id_author', $id_author);
  print form_create_hidden('id_part_prec', $id_spo);
  print form_create_hidden('old_pos', $old_pos);
  // 
  print form_end();


?>