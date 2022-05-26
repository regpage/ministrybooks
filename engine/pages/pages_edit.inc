<?php
?>
<?php
  $ed_pg  = preg_replace("/[^a-z0-9_]/", '', $_GET['pg']);
  if(empty($ed_pg))
    $ed_pg  = preg_replace("/[^a-z0-9_]/", '', $_POST['pg']);
  /*if(empty($ed_pg))
  {
    $pg_name = preg_replace("/[^a-z0-9_\.]/i", "", $_GET['pg_name']);
    $query = "SELECT id_page FROM pages_list WHERE page = '{$pg_name}'";
    $ed_pg = db_select_one($query);

  }*/

  $ed_url = "?mod=pages_edit";
  $ed_tbl_pref = 'pages';
  $ed_opt = preg_replace("/[^a-z0-9_]/", '', $_GET['ed_opt']);

  $ed_path_to_editor = "{$gl_path_to_engine}blockeditor/";
  $ed_path_to_file   = "{$gl_path_to_root}content/pages/{$ed_pg}/";
  $ed_path_to_img   = "{$gl_path_to_root}content/pages/{$ed_pg}/";

  include("{$ed_path_to_editor}func.inc");

  if($gl_group != 'admin')
    return;

  include("{$ed_path_to_editor}blocks_pages.inc");

?>