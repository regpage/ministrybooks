<?php
 
  if(!empty($_GET['id_part']))
  {
    $id_part = intval($_GET['id_part']);
    $_SESSION['be_id_part'] = $id_part;
    $id_item = intval($_GET['id_item']);
    $_SESSION['be_id_item'] = $id_item;
  }
  else
  {
    $id_part = intval($_SESSION['be_id_part']);
    $id_item = intval($_SESSION['be_id_item']);
  }

  //////////////////////////////////////////////////////////////////////////////
  //   
  //////////////////////////////////////////////////////////////////////////////

  $query = "SELECT title
              FROM {$gl_db_prefix}parts
             WHERE id_part = {$id_part}";
  $ed_part_title = stripslashes(db_select_one($query));

  $ed_back_href = "<strong>/</strong> <a href='?adm=parts_items_pages_text&ed_opt=blocks_list&pg={$id_item}&id_part={$id_part}&id_item={$id_item}
'>Редактировать книгу</a> <strong>/</strong> <a href='?adm=parts_list&id_part_prec={$id_part}'>Вернуться в категорию <strong>{$ed_part_title}</strong></a> <strong>/</strong> <a href='?adm=parts_items_pages_edit&id_part_prec={$id_part}&id_item={$id_item}'> Параметры книги</a> <strong>/</strong>";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

  $query = "SELECT title
              FROM {$gl_db_prefix}parts_items
             WHERE id_item = {$id_item}";
  $ed_pg_title = stripslashes(db_select_one($query));
  //$ed_h1_prefix = "{$l_pages[5]} :: {$ed_part_title} :: {$l_parts[65]} :: {$ed_pg_title}";
  $ed_h1_prefix = "{$ed_part_title} :: {$ed_pg_title}";


  //////////////////////////////////////////////////////////// 
  ////////////////////////////////////////////////////////////

  //   (  )
  $ed_url = "?adm=parts_items_pages_text";
  //  {prefix}_blocks  {prefix}_images
  $ed_tbl_pref = 'pages';
  //  
  $ed_opt = preg_replace("/[^a-z0-9_]/", '', $_GET['ed_opt']);
  //id_item  
  $ed_pg  = preg_replace("/[^a-z0-9_]/", '', $_GET['pg']);
  if(empty($ed_pg))
  $ed_pg  = preg_replace("/[^a-z0-9_]/", '', $_POST['pg']);


  /////////////////////////////////////////////////////////// 
  ///////////////////////////////////////////////////////////

  //   
  $ed_path_to_editor = "{$gl_path_to_engine}blockeditor/";
  //  ,      ,   
  $ed_path_to_file   = "{$gl_path_to_root}content/{$ed_pg}/";
  //  ,    
  $ed_path_to_img   = "{$gl_path_to_root}content/{$ed_pg}/";
  //url  
  $ed_path_to_img_for_url = "content/{$ed_pg}/";
  //  
  $ed_page_preview_href = "?mb={$ed_pg}";

  ////////////////////////////////////////////////////////// 
  //////////////////////////////////////////////////////////
 
  include("{$ed_path_to_editor}func.inc");

  print "<p style='padding-top:20px;'>{$ed_back_href}</p>";
  //         ed_opt
  include("{$ed_path_to_editor}blocks_chupters.inc");
  // 
  print "<p style='padding-bottom:100px;'>{$ed_back_href}</p>";

?>