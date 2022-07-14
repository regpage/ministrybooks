<?php

  if(!empty($_POST['save']))
  {
    $text = $_POST['text'];

    //Р·Р°РЅРѕСЃРёРј РґР°РЅРЅС‹Рµ РІ Р±Р°Р·Сѓ
    $text_for_db = correct_input($text);
    $query = "SELECT id_block FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks WHERE id_pg = {$ed_pg} ORDER BY pos LIMIT 0, 1";
    $id_block = db_select_one($query);

    if(!$id_block)
    {
    	 $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_blocks SET
	                  id_block = NULL,
	                  type = 'p_just',
	                  gen_type = 'text',
	                  content = '{$text}',
	                  params = '',
	                  pos = 1,
	                  id_pg = {$ed_pg}";
      db_insert($query);
    }
    else
    {
      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks SET
	                  content = '{$text}'
	                WHERE id_block = {$id_block}";
      db_update($query);
    }

    //С„РѕСЂРјРёСЂСѓРµРј СЃС‚СЂР°РЅРёС†Сѓ РґР»СЏ СЃРѕС…СЂР°РЅРµРЅРёСЏ
    $text_for_save = $text;

    //РѕС‚РјРµРЅСЏРµРј РїРµСЂРµРєРѕРґРёСЂРѕРІР°РЅРёРµ php С‚РµРіРѕРІ
    $text_for_save = str_replace("&lt;?php", "<?php", $text_for_save);
    $text_for_save = str_replace("?&gt;", "?>", $text_for_save);
    
    if(false)
    $text_for_save = stripslashes($text_for_save);
    $text_for_save = explode("[NEWPAGE]", $text_for_save);
    $pages_cnt = count($text_for_save);

//СЃСЃС‹Р»РєР° РЅР° СЃС‚СЂР°РЅРёС†Сѓ
    $ed_page_preview_href = "?mb={$ed_pg}";
       
    $str  = "<?php\r\n";
    /*if((strpos($ed_back_href, 'parts_list') !== false) || (strpos($ed_back_href, 'mb') !== false))
    $navig_tpl = file_get_contents("{$gl_path_to_engine_root}mods/spaw2full/navig_pg.inc");
    else
      c*/
    $navig_tpl = file_get_contents("{$gl_path_to_engine_root}mods/spaw2full/navig.inc");
    $navig_tpl = str_replace("{ed_pg}", $ed_pg, $navig_tpl);
    //$navig_tpl = str_replace("{part}", $part, $navig_tpl);
    $navig_tpl = str_replace("{pages_cnt}", $pages_cnt, $navig_tpl);
    $navig_tpl = str_replace("{ed_page_preview_href}", $ed_page_preview_href, $navig_tpl);
    $str .= $navig_tpl;
    $str .= "\r\n";

    for($i = 0; $i < $pages_cnt; $i++)
    {
      $num = $i + 1;
      $str .= "if(\$part == {$num})\r\n";
      $str .= "{?>\r\n"; 
      $str .= $text_for_save[$i];
      $str .= "<?php }\r\n";    
    }    
   
    if($cnt > 1);
    $str .= "print \$navig;\r\n";
    $str .= "?>";   
      
    save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $str, 'w');
  }

  print "<h3>{$ed_h1_prefix}</h3>";
  $query = "SELECT content FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks WHERE id_pg = {$ed_pg} ORDER BY pos LIMIT 0, 1";
    $content = stripslashes(db_select_one($query));
  //РѕС€РёР±РєРё
  if(!empty($errors))
    print form_print_errors($errors);

  //С€Р°Р±Р»РѕРЅС‹
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //РЅР°С‡Р°Р»Рѕ С„РѕСЂРјС‹
  print "<form action='' method='post'>";
  include("{$gl_path_to_engine_root}mods/spaw2full/spaw.inc.php");
  $spaw1 = new SpawEditor("text", $content);
    $tmp_gl_subdir = $gl_subdir;
  if($tmp_gl_subdir[0] != '/')
    $tmp_gl_subdir = '/'.$tmp_gl_subdir;
  $inx = strlen($tmp_gl_subdir) - 1;
  if($tmp_gl_subdir[$inx] != '/')
    $tmp_gl_subdir = $tmp_gl_subdir.'/';

 $spaw1->setConfigItem (
  'PG_SPAWFM_DIRECTORIES',
  array(
    array(
        'dir' => $tmp_gl_subdir.$ed_path_to_img_for_url,
        //'fsdir' => '/'.$ed_path_to_img_for_url,
        'caption' => $ed_pg_title,
        'params' => array(
        'allowed_filetypes' => array('any'), 'default_dir' => true
      )
    ),

    array(
      'dir' => $tmp_gl_subdir."images",
         //'fsdir' => '/'.$ed_path_to_img_for_url,
         'caption' => "images",
         'params' => array(
         'allowed_filetypes' => array('images')
      )
    ),
  ),
  SPAW_CFG_TRANSFER_SECURE
);

  $spaw1->show();

  //РєРЅРѕРїРєРё
  
  print "<p>";
  print form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton');
  print "{$l_spaweditor[1]}</p>"; print "</form>";
  
if(!empty($gl_adm))
print "<p style='text-align: right;'> <strong>&raquo;</strong> <a href='?adm=parts_items_pages_chapter&ed_opt=blocks_list_chupters&pg={$ed_pg}'>{$l_parts[86]}</a> <strong>&raquo;</strong> <a href='?adm=parts_items_pages_edit&id_part_prec={$id_part}&id_item={$id_item}'> Параметры книги </a> <strong>&raquo;</strong> {$ed_back_href} ";

  $path = "{$ed_path_to_file}ch_{$ed_pg}.inc";

//    Если файл с системой навигации существует извлекаем массив данных
 
if(!file_exists($path)) print " <strong>&raquo;</strong> <a href='?adm=parts_items_pages_chapter&ed_opt=blocks_list_chupters_avtomat&pg={$ed_pg}'>{$l_parts[90]}</a> <strong>&raquo;</strong> <a href='?mb={$ed_pg}' target='_blank'> $l_spaweditor[2]</a> ";

print "<strong>&raquo;</strong></p>";
   
  if(!empty($gl_adm))
    exit;

?>