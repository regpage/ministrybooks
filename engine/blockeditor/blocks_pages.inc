<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ѕодключение модул€ Antf Blockeditor в зависимости от значени€ переменной $ed_opt
  //////////////////////////////////////////////////////////////////////////////

  //$gl_ed_opt формируетс€ в blockeditor_sel_action.inc
  if(!empty($gl_ed_opt)) $ed_opt = $gl_ed_opt;

  if(!empty($_POST['ed_opt'])) $ed_opt = preg_replace("/[^a-z0-9_]/", '', $_POST['ed_opt']);

  switch($ed_opt)
  {
    case 'blocks_list': include("{$ed_path_to_editor}blocks_list.inc");  break;
    case 'blocks_add': include("{$ed_path_to_editor}blocks_add.inc");  break;
    case 'blocks_del': include("{$ed_path_to_editor}blocks_del.inc");  break;
    case 'blocks_edit': include("{$ed_path_to_editor}blocks_edit.inc");  break;
    case 'blocks_images_list': include("{$ed_path_to_editor}images_list.inc");  break;
    case 'blocks_images_add': include("{$ed_path_to_editor}images_add.inc");  break;
    case 'blocks_images_del': include("{$ed_path_to_editor}images_del.inc");  break;
    case 'blocks_images_edit': include("{$ed_path_to_editor}images_edit.inc");  break;
    case 'blocks_move_all': include("{$gl_path_to_engine}blockeditor/blocks_move_all.inc");  break;
    case 'blocks_del_all': include("{$gl_path_to_engine}blockeditor/blocks_del_all.inc");  break;
  }



?>