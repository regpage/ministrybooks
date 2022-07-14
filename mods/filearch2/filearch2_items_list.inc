<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // ������� ������ ������ ��������� $id_cat, ���� $id_cat = 0,
  // ������� ���������� �� ���� ������.
  //////////////////////////////////////////////////////////////////////////////

  //������������� ����������
  $id_cat = intval($_GET['id_cat']);

  //��������� ������
  $file_tpl      = file_get_contents("{$gl_path_to_templates}filearch2/file.htm");

  //�������� ��������� ���������
  $query     = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}";
  $results   = db_select($query);
  $cat_title = stripslashes($results[0]['title']);
  $path      = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";
  $path_abs      = "https://ministrybooks.ru/content/_filearch2/".sprintf("%03d", $id_cat)."/";
  //���������

  print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div>";
  print "<p><a class='chap' href='?mod=filearch2_cats_list'><img src='themes/file_archiv/images/home.gif'>&nbsp;{$cat_title}</a> :: {$l_filearch2[24]}</p>";

  print "<form name='filearch2_form' action='' method='post'>";
  //������� ����,  �������� ���� | ������������ | �������� ��������
		if($gl_group == 'admin' Or $gl_group=='editors')
		{
		  print "<p>";
		  //�������� ����
		  print "<a class='' href='?mod=filearch2_items_add&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/add_file.gif' height = 50px></a>&nbsp;&nbsp;";
		  //����������
		  print "<a class='' href='?mod=filearch2_items_stat&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/stat_files.gif' height = 50px></a>&nbsp;&nbsp;";
 if($_SESSION["{$gl_site_name}_gl_id_user"]== 2){
		  //������������ ������
		  print "<a class='' href='?mod=filearch2_items_autoload&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/avtoload_file.gif' height = 50px></a>&nbsp;&nbsp;";

		  //�������� ��������
		  print "<a class='' href='?mod=filearch2_manager_list&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/maneger_files.gif' height = 50px></a>";
}
		  print "</p>";
  }
  else
  {  	 print "";
  }

  //�������� �����
		$query = "SELECT *, DATE_FORMAT(date, '%d %b %Y') as date_formatted
		            FROM {$gl_db_prefix}filearch2_items
		           WHERE id_cat = {$id_cat}
		             ORDER BY pos ASC";
  $results = db_select($query);

  if(is_array($results))
  {
    $cnt = count($results);
print "<table class='SiteTbl' width='612' border='0' cellpadding='0' cellspacing='0'>
<tr>
<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[34]}</td>
<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[38]}</td>
<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[31]}</td>
<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[36]}</td>
<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[83]}</td>";
$opt = '';
if($gl_group == 'admin' Or $gl_group=='editors')
    {
        $opt = "<td class='SiteTblTH' width='612' valign='bottom'>{$l_filearch2[74]}</td>";
    }

print "{$opt}</tr>";

    for($i = 0; $i < $cnt; $i++)
    {
      $id_item = $results[$i]['id_item'];

      $pos = $results[$i]['pos'];

      $title  = stripslashes($results[$i]['title']);

      $file    = stripslashes($results[$i]['file']);


  //�������� ����� �����
  $path_r    = $path.$file;
  $path_a    = $path_abs.$file;

print "<tr>";
$title  = "<td class='SiteTblLeft' valign='bottom'>{$title}</td>";

      $descr  = stripslashes($results[$i]['descr']);
      $descr  = convert_bb_tags($descr, 'forum');
      $descr  = nl2br($descr);
      $descr  = "<td class='SiteTblCenter'  valign='bottom'>{$descr}</td>";
      $date  = translate_data($results[$i]['date_formatted'], $gl_months);
      $date  = "<td class='SiteTblCenter'  valign='bottom'>{$date}</td>";

      //�����
      $options = '';
		    if($gl_group == 'admin' Or $gl_group=='editors')
		    {
		      $options  .= "&nbsp;<input id='items_{$i}' type='checkbox' value='yes' name='items[{$id_item}]' />&nbsp;";
		      //���������
		      $options  .= "<br><a class=''  alt='[{$l_filearch2[52]}]' title='{$l_filearch2[52]}' href='?mod=filearch2_items_edit&amp;id_item={$id_item}&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/edit.gif'></a>&nbsp;";
		      //�������
		      $options  .= "<a class=''  alt='[{$l_filearch2[55]}]' title='{$l_filearch2[55]}' href='?mod=filearch2_items_del&amp;id_item={$id_item}&amp;id_cat={$id_cat}'><img src='themes/file_archiv/images/del_file.gif'></a>";
        $options   = "{$options}";
        $options   = "<td class='SiteTblCenter'  valign='bottom'>{$options}</td>";

      }
      //������ �� ����
        $a_file = "http://ministrybooks.ru/index.cfm?act=filearch2_dwnld&amp;id_item={$id_item}";
	 $filesize = filesize_format(sprintf('%u', filesize($path_r)), '%01.1lf %s', 'mb');
	 $a_file="<td class='SiteTblCenter'  valign='bottom'><a class='' alt='[{$l_filearch2[41]}]' title='{$l_filearch2[41]}' href='{$a_file}' target='_blank'><img src='themes/file_archiv/images/save_as.gif'></a><br>{$filesize}</td>
      <td class='SiteTblCenter'  valign='bottom'>{$a_file}</td>";

     //������������ ������, ������� ���������� � �����
      print work_template($file_tpl,    array("{date}"     => $date,
                                              "{c_date}"   => $l_filearch2[31],
                                              "{title}"    => $title,
                                              "{a_file}"   => $a_file,
                                              "{path_file}"   => $path_file,
                                              "{descr}"    => $descr,
                                              "{c_download}" => $l_filearch2[41],
                                              "{options}"  => $options));
    }           //���������: ������ ���
print "</tr>";
print "</table>";
  } else print "<p>{$l_filearch2[32]}</p>";

  //������
  if($gl_group == 'admin' Or $gl_group=='editors')
  {
   	 print "<p>{$l_filearch2[54]}&nbsp;&nbsp;
		                 <input type='submit' class='' style='margin-bottom:0' name='delete_all' value='{$l_filearch2[55]}' />
		               </p>";

    //������� ����
    print "<input type='hidden' name='mod' value='filearch2_items_del_all'>";
    print "<input type='hidden' name='id_cat' value='{$id_cat}'>";
    print "<input type='hidden' name='part' value='{$part}'>";

    print "";
  }

  print "</form>";

  //������ "�����"
  print "<p><a class='chap' href='?mod=filearch2_cats_list'><img src='themes/file_archiv/images/home.gif'>&nbsp;{$l_filearch2[1002]}</a></p>";

function filesize_format($bytes, $format = '', $force = ''){
  $force = strtoupper($force);
  $defaultFormat = '%01d %s';
  if (strlen($format) == 0)
  $format = $defaultFormat;
  $bytes = max(0, (int) $bytes);
  $units = array('B', 'KB', 'MB', 'GB', 'TB', 'PB');
  $power = array_search($force, $units);
  if ($power === false)
  $power = $bytes > 0 ? floor(log($bytes, 1024)) : 0;
  return sprintf($format, $bytes / pow(1024, $power), $units[$power]);
}
?>
