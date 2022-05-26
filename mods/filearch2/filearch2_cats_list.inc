<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive
  // Модуль выводит список категорий
  //////////////////////////////////////////////////////////////////////////////
  //заголовок
  print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div>";
  //загружаем шаблон
  $cat_tpl      = file_get_contents("{$gl_path_to_templates}filearch2/cat.htm");
  //главное меню добавить | все файлы | настройки
		if($gl_group == 'admin' Or $gl_group == 'editors')
		{
		  print "&nbsp;&nbsp;&nbsp;<a href='?mod=filearch2_cats_add' onmouseover='document.add_categoriu.src=img7on.src' onmouseout='document.add_categoriu.src=img7.src'>
       <img src='themes/file_archiv/images/add_categoriu1.gif' height=40px alt='add_categoriu' name='add_categoriu' id='add_categoriu' />
      </a>";
 if($_SESSION["{$gl_site_name}_gl_id_user"]== 2){
		 print "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a span class='' href='index.cfm?mod=filearch2_items_stat&amp;id_cat=0'><img src='themes/file_archiv/images/all_stat_files.gif' height = 50px></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a span class='' href='index.cfm?mod=filearch2_settings'><img src='themes/file_archiv/images/settings_file.gif' height = 50px></a>";
  }
}
  //выбираем категории из бд
  $query = "SELECT *
              FROM {$gl_db_prefix}filearch2_cats WHERE if_arch_user = {$gl_id_user}
             ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    $cnt = count($results);
print "<table class='SiteTbl' width='612' border='0' cellpadding='0' cellspacing='0'>
<tr>
<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[84]}</td>
<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[38]}</td>
";
$opt = '';
if($gl_group == 'admin' Or $gl_group=='editors')
    {
        $opt = "<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[74]}</td>"; 
    }
print "{$opt}</tr>";
    for($i = 0; $i < $cnt; $i++)
    {
      $id_cat  = $results[$i]['id_cat'];
      $pos     = $results[$i]['pos'];
      $title   = stripslashes($results[$i]['title']);
print "<tr>";
      //форматирование описания
      $descr  = stripslashes($results[$i]['descr']);
      $descr  = convert_bb_tags($descr, 'forum');
      $descr  = nl2br($descr);
$descr  = "<td class='SiteTblCenter' valign='bottom'>{$descr}</td>";
      //кол-во файлов в категории
      $files_count = db_select_one("SELECT COUNT(id_item) FROM {$gl_db_prefix}filearch2_items WHERE id_cat = {$id_cat}");
      //ссылка на файлы категории
      $a_cat = "index.cfm?mod=filearch2_items_list&amp;id_cat={$id_cat}";
$title = "<td class='SiteTblLeft' valign='bottom'><b><a class='chap' href='{$a_cat}'>{$title}</a>&nbsp;({$files_count})</b></td>{$descr}";
      //опции
      $options = '';
      if($gl_group == 'admin' Or $gl_group=='editors')
		    {
		      //параметры
		      $options .= "<a class='chap' href='index.cfm?mod=filearch2_cats_edit&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/edit.gif'></a>&nbsp;&nbsp;|&nbsp;&nbsp;";
		      //удалить
		      $options .= "<a class='chap' href='index.cfm?mod=filearch2_cats_del&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/del_file.gif'></a>";
        $options   = "<td class='SiteTblCenter' valign='bottom'>{$options}</td>";
      }
      //print "<h2><a class='chap' href='{$a_cat}'>{$title}</a>&nbsp;($files_count)</h2>";
      //print "<p>{$descr}{$options}</p><br />";
      //обработка шаблона, вывод категории
      print work_template($cat_tpl,    array( "{title}"    => $title,
                                              "{options}"  => $options));
    }    //Сообщение о том, что ни одной категории не добавлено
print "</tr>";
print "</table><br>";
  } else print "<p>{$l_filearch2[9]}</p>";
  print "<br />";
  print "<br />";
?>