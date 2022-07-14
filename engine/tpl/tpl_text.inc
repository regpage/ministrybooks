<?php
  //////////////////////////////////////////////////////////////////////////////
  function process_main_tpl($tpl)
  {
    global $gl_path_to_root, $gl_path_to_engine;
    $tpl = preg_replace("/\[CONTENT\]/i", "<?php include(\"{\$gl_path_to_engine}public/content.inc\"); ?>", $tpl);
    $tpl = preg_replace("/\[TITLE\]/i", "<?php print \$site_title; ?>", $tpl);
    $tpl = preg_replace("/\[AUTH_FORM\]/i", '<?php include("{\$gl_path_to_engine}auth/auth_form.inc"); ?>', $tpl);
    $tpl = preg_replace("/\[KEYWORDS\]/i", "<?php setmeta(\$gl_page, \$site_keywords, \$site_descr) ?>", $tpl);
    $tpl = preg_replace("/\[MENU=([0-9]+)\]/i", "<?php create_menu($1); ?>", $tpl);
    $tpl = preg_replace("/\[CODEFR=([^\]]+)\]/i", "<?php include(\"{\$gl_path_to_root}codesfragms/$1\"); ?>", $tpl);
    return($tpl);
  }


  //////////////////////////////////////////////////////////////////////////////
  // 
  //////////////////////////////////////////////////////////////////////////////

  $id_tpl = intval($_GET['id_tpl']);
  if(empty($id_tpl))
    $id_tpl = intval($_POST['id_tpl']);

  //  
  $query = "SELECT title, file
              FROM {$gl_db_prefix}sitetpl
             WHERE id_tpl = {$id_tpl}";
  $results = db_select($query);
  $tpl_title = stripslashes($results[0]['title']);
  $file      = $results[0]['file'];


  //////////////////////////////////////////////////////////////////////////////
  // 
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $tpl = $_POST['tpl'];
    if(false)
      $tpl = stripslashes($tpl);

    $fp = fopen ("{$gl_path_to_templates}site/{$file}.tpl", "w");
    fwrite ($fp, $tpl);
    fclose ($fp);


    $fp = fopen ("{$gl_path_to_templates}site/{$file}.inc", "w");
    fwrite ($fp, process_main_tpl($tpl));
    fclose ($fp);
  }


  //////////////////////////////////////////////////////////////////////////////
  //
  //////////////////////////////////////////////////////////////////////////////

  //    
  $tpl = file_get_contents("{$gl_path_to_templates}site/{$file}.tpl");


  //
  print "<h1>{$tpl_title} :: {$l_tpl[21]}</h1>";

  // 
  $form_line_tpl = "<tr><td>{field}</td></tr>";

  // 
  if(!empty($errors))
    print form_print_errors($errors);

  // 
  print "<form action='' method='post'>";
    print "<table  cellspacing='0' cellpadding='0' border='0'>";
      print "<tr><td>";
        // 
        print "<textarea style='margin-left:10px' id='tpl' name='tpl' rows='33' class='SiteFTextareaL'>{$tpl}</textarea>";
      print "</td></tr>";
      print "<tr><td>";
        //
        print "<input class='SiteFButton' type='submit' name='save' value='{$l_adm_gen[2]}'><input type='button' value='{$l_adm_gen[4]}' class='SiteFButton' onClick=\"location.href='?adm=tpl_list'\">";
      print "</td></tr>";
    print "</table>";


  // 
  print form_create_hidden('blague', session_id());
  print form_create_hidden('id_tpl', $id_tpl);

  print "</form>";


  //////////////////////////////////////////////////////////////////////////////
  //SELECT'    
  //////////////////////////////////////////////////////////////////////////////

  //    
  $dir = opendir("codesfragms");
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..')
      $opt_fragms .= "<option value='[CODEFR={$file}]'>{$file}</option>";
  }
  closedir($dir);

  //   
  $query = "SELECT id_menu, title
              FROM {$gl_db_prefix}menu
            ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $m_title = stripslashes($results[$i]['title']);
      $id_menu = $results[$i]['id_menu'];
      $opt_menu .= "<option value='[MENU={$id_menu}]'>{$m_title}</option>";
    }
  }

  //    
  $opt_other = "";
  //: ,   
  $opt_other .= "<option value='[CONTENT]'>{$l_tpl[22]}</option>";
  //: -,    
  $opt_other .= "<option value='[KEYWORDS]'>{$l_tpl[23]}</option>";
  // 
  $opt_other .= "<option value='[AUTH_FORM]'>{$l_tpl[31]}</option>";

  // 
  $form_line_tpl = get_tpl_from_file("{$gl_path_to_templates}forms/line1.htm");
  print form_begin('codes_form', '', 'post', 'multipart');

  //:      ,    :
  print work_template($form_line_tpl,    array("{caption}" => $l_tpl[24],
                                                  "{field}" => form_create_input("code", $css = 'SiteFInputM', $size ='')));

  //  
  print work_template($form_line_tpl,    array("{caption}" => "{$l_tpl[25]}",
                                               "{field}" => form_create_select('menu_code', $opt_menu, $css = 'SiteFInputM', '', "document.codes_form.code.value=document.codes_form.menu_code.value")));

  //  
  print work_template($form_line_tpl,    array("{caption}" => "{$l_tpl[26]}",
                                               "{field}" => form_create_select('fr_code', $opt_fragms, $css = 'SiteFInputM', '', "document.codes_form.code.value=document.codes_form.fr_code.value")));

  // 
  print work_template($form_line_tpl,    array("{caption}" => "{$l_tpl[27]}",
                                               "{field}" => form_create_select('other_code', $opt_other, $css = 'SiteFInputM', '', "document.codes_form.code.value=document.codes_form.other_code.value")));

  // 
  print form_end();
?>