<?php
  include("{$gl_path_to_root}config/site_settings.inc");
  $path = "{$gl_path_to_engine_root}langfiles/";
  $dir = opendir($path);
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && !is_dir("{$path}{$file}"))
    {
      if(strpos($file, 'adm_') !== false)
        { include("{$path}{$file}"); }
    }
  }
  closedir($dir);
  include("{$gl_path_to_engine}common/actions.inc");
  if($gl_group != 'admin')
  {
    header("Location: https://ministrybooks.ru");
    exit;
  }
?>
<html>
	<head>
<title><?php echo $l_adm_gen[21]?><?php echo $pg_title ?></title>
<link rel="stylesheet" href="<? echo $gl_admin_url ?>css/admin/main.css" rel="stylesheet" rev="stylesheet" type="text/css" media="screen" charset="utf-8" />
<link rel="stylesheet" href="<? echo $gl_admin_url ?>css/admin/format.css" rel="stylesheet" rev="stylesheet" type="text/css" media="screen" charset="utf-8" />
<!-- link calendar files  -->
<!--
<script language="JavaScript" src="<? //echo $gl_admin_url ?>tigra_calendar/calendar_us.js"></script>
<link rel="stylesheet" href="<? //echo $gl_admin_url ?>tigra_calendar/calendar.css">

 -->
<script language="JavaScript" src="<? echo $gl_admin_url ?>1-simple-calendar/tcal.js"></script>
<link rel="stylesheet" href="<? echo $gl_admin_url ?>1-simple-calendar/tcal.css">

 <link href="<? echo $gl_admin_url ?>dist/css/datepicker.min.css" rel="stylesheet" type="text/css">
<script src="<? echo $gl_admin_url ?>dist/js/jquery.min.js"></script>
<script src="<? echo $gl_admin_url ?>dist/js/datepicker.min.js"></script>
<script src="<? echo $gl_admin_url ?>dist/js/i18n/datepicker.js"></script>
<script src="<? echo $gl_admin_url ?>dist/js/datepicker.en.js"></script>


<head><body marginwidth=0 marginheight=0 leftmargin=0 rightmargin=0 topmargin=0 bottommargin=0 bgcolor='#ffffff' alink='#F26D00' link='#0857A6' vlink='#0857A6'>
<!--  //print "<div id='header'><strong>{$l_admmain[28]}</strong></div>";   -->
<?php
    $editor_path = "{$gl_path_to_engine_root}mods/editarea/ortus_connector.inc";
    if(file_exists($editor_path))
    include($editor_path);
    unset($editor_path);
?>
<?php
    print "<div id='layer1'><div id='menu'> ";
       include("{$gl_path_to_engine}admin/leftcol.inc");
    print "</div></div><div id='layer2'>";
//print "<table border='1' cellpadding='10' cellspacing='0' ><tr><td>";
	   switch($gl_adm)
	   {
	     case 'main'       : include("{$gl_path_to_engine}admin/main_menu.inc"); break;

	     case 'author_list' : include("{$gl_path_to_engine}parts/author_list.inc"); break;
	     case 'author_add'  : include("{$gl_path_to_engine}parts/author_add.inc");  break;
	     case 'author_edit' : include("{$gl_path_to_engine}parts/author_edit.inc"); break;
	     case 'author_del'  : include("{$gl_path_to_engine}parts/author_del.inc"); break;

	     case 'parts_list' : include("{$gl_path_to_engine}parts/parts_list.inc");  break;
	     case 'parts_add'  : include("{$gl_path_to_engine}parts/parts_add.inc");   break;
	     case 'parts_edit' : include("{$gl_path_to_engine}parts/parts_edit.inc");  break;
	     case 'parts_del'  : include("{$gl_path_to_engine}parts/parts_del.inc");   break;
	     case 'parts_move'  : include("{$gl_path_to_engine}parts/parts_move.inc");   break;
	     case 'parts_perm'  : include("{$gl_path_to_engine}parts/parts_perm.inc");   break;
	     case 'parts_items_pages_add'  : include("{$gl_path_to_engine}parts/parts_items_pages_add.inc");   break;
	     case 'parts_items_pages_edit' : include("{$gl_path_to_engine}parts/parts_items_pages_edit.inc");   break;
	     case 'parts_items_pages_move' : include("{$gl_path_to_engine}parts/parts_items_pages_move.inc");   break;
	     case 'parts_items_pages_del'  : include("{$gl_path_to_engine}parts/parts_items_pages_del.inc");   break;
	     case 'parts_items_pages_text' : include("{$gl_path_to_engine}parts/parts_items_pages_text.inc");   break;
	     case 'parts_items_pages_chapter' : include("{$gl_path_to_engine}parts/parts_items_pages_chapter.inc");   break;
	     case 'parts_items_pages_url' : include("{$gl_path_to_engine}parts/parts_items_pages_url.inc");   break;
	     case 'parts_pages_search' :  include("{$gl_path_to_engine}parts/parts_pages_search.inc");   break;

	     case 'parts_items_mods_add'  : include("{$gl_path_to_engine}parts/parts_items_mods_add.inc");   break;
	     case 'parts_items_mods_edit' : include("{$gl_path_to_engine}parts/parts_items_mods_edit.inc");   break;
	     case 'parts_items_mods_del'  : include("{$gl_path_to_engine}parts/parts_items_mods_del.inc");   break;

	     case 'tpl_list' : include("{$gl_path_to_engine}tpl/tpl_list.inc");  break;
	     case 'tpl_add'  : include("{$gl_path_to_engine}tpl/tpl_add.inc");   break;
	     case 'tpl_edit' : include("{$gl_path_to_engine}tpl/tpl_edit.inc");  break;
	     case 'tpl_text' : include("{$gl_path_to_engine}tpl/tpl_text.inc");  break;
	     case 'tpl_del'  : include("{$gl_path_to_engine}tpl/tpl_del.inc");   break;

	     case 'settings'  : include("{$gl_path_to_engine}settings/settings.inc");   break;

	     case 'menu_list' : include("{$gl_path_to_engine}menu/menu_list.inc");  break;
	     case 'menu_add'  : include("{$gl_path_to_engine}menu/menu_add.inc");   break;
	     case 'menu_edit' : include("{$gl_path_to_engine}menu/menu_edit.inc");  break;
	     case 'menu_del'  : include("{$gl_path_to_engine}menu/menu_del.inc");   break;

	     case 'sites_list' : include("{$gl_path_to_engine}sites/sites_list.inc");  break;
	     case 'sites_add'  : include("{$gl_path_to_engine}sites/sites_add.inc");   break;
	     case 'sites_edit' : include("{$gl_path_to_engine}sites/sites_edit.inc");  break;
	     case 'sites_del'  : include("{$gl_path_to_engine}sites/sites_del.inc");   break;

	     case 'smiles_list' : include("{$gl_path_to_engine}smiles/list.inc");  break;
	     case 'smiles_add'  : include("{$gl_path_to_engine}smiles/add.inc");   break;
	     case 'smiles_edit' : include("{$gl_path_to_engine}smiles/edit.inc");  break;
	     case 'smiles_del'  : include("{$gl_path_to_engine}smiles/del.inc");   break;

	     case 'menu_items_list' : include("{$gl_path_to_engine}menu/menu_items_list.inc");  break;
	     case 'menu_items_add'  : include("{$gl_path_to_engine}menu/menu_items_add.inc");   break;
	     case 'menu_items_edit' : include("{$gl_path_to_engine}menu/menu_items_edit.inc");  break;
	     case 'menu_items_del'  : include("{$gl_path_to_engine}menu/menu_items_del.inc");   break;

	     case 'css_list' : include("{$gl_path_to_engine}css/css_list.inc");  break;
	     case 'css_add'  : include("{$gl_path_to_engine}css/css_add.inc");   break;
	     case 'css_edit' : include("{$gl_path_to_engine}css/css_edit.inc");  break;
	     case 'css_text' : include("{$gl_path_to_engine}css/css_text.inc");  break;
	     case 'css_del'  : include("{$gl_path_to_engine}css/css_del.inc");   break;

	     case 'mods_list' : include("{$gl_path_to_engine}mods/list.inc");  break;
	     case 'mods_url' : include("{$gl_path_to_engine}mods/url.inc");  break;

	     case 'codesfragms_list' : include("{$gl_path_to_engine}codesfragms/list.inc");  break;
	     case 'codesfragms_add'  : include("{$gl_path_to_engine}codesfragms/add.inc");   break;
	     case 'codesfragms_edit' : include("{$gl_path_to_engine}codesfragms/edit.inc");  break;
	     case 'codesfragms_text' : include("{$gl_path_to_engine}codesfragms/text.inc");  break;
	     case 'codesfragms_del'  : include("{$gl_path_to_engine}codesfragms/del.inc");   break;

	     case 'stpl_edit' : include("{$gl_path_to_engine}stpl/stpl_edit.inc");  break;

	     case 'users_list'     : include("{$gl_path_to_engine}users/users_list.inc");  break;
	     case 'users_chgroup'  : include("{$gl_path_to_engine}users/users_chgroup.inc");   break;
	     case 'users_chpsw'  : include("{$gl_path_to_engine}users/users_chpsw.inc");   break;
	     case 'users_edit'     : include("{$gl_path_to_engine}users/users_edit.inc");  break;
	     case 'users_del'      : include("{$gl_path_to_engine}users/users_del.inc");   break;
	     case 'users_add'      : include("{$gl_path_to_engine}users/users_add.inc");   break;

	     case 'users_del_all'      : include("{$gl_path_to_engine}users/users_del_all.inc");   break;

	     case 'url_list':         include("{$gl_path_to_engine}admin/url_list.inc");  break;

	     case 'distrib':         include("{$gl_path_to_engine}distrib/distrib.inc");  break;

	     case 'letters_edit':         include("{$gl_path_to_engine}letters/letters_edit.inc");  break;

	     case 'regform_fields_list'      : include("{$gl_path_to_engine}regform_fields/regform_fields_list.inc");   break;
	     case 'regform_fields_add'      : include("{$gl_path_to_engine}regform_fields/regform_fields_add.inc");   break;
	     case 'regform_fields_edit'      : include("{$gl_path_to_engine}regform_fields/regform_fields_edit.inc");   break;
	     case 'regform_fields_del'      : include("{$gl_path_to_engine}regform_fields/regform_fields_del.inc");   break;
}
//print "</td></tr></table>";
    print "</div>";
print "</body>
</html>";
?>
