<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // ������ ������� ��������� $id_cat
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // ������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_cat   = intval($_GET['id_cat']);
  $state    = intval($_GET['state']);
 
  //������� ������ �����������
  $query = "SELECT pos
            FROM {$gl_db_prefix}filearch2_cats
  	         WHERE id_cat  = {$id_cat}";
	 $results = db_select($query);
	 $pos = $results[0]['pos'];

  //����� � �������������
	 $folder = sprintf("%03d", $id_cat);
	 $path   = "{$gl_path_to_root}content/_filearch2/{$folder}/";


  //////////////////////////////////////////////////////////////////////////////
	 //����� ����������� ���� ������������� ��������
	 //////////////////////////////////////////////////////////////////////////////

	 if(empty($state))
	 {
print "<h3>{$l_filearch2[22]}</h3><br /><br /><br /><br /><br /><div align='center'><br /><br /><a class='chap' href='index.cfm?mod=filearch2_cats_del&amp;id_cat={$id_cat}&amp;state=1'>{$l_gen[20]}</a> <a class='chap' href='index.cfm?mod=filearch2_cats_list'>{$l_gen[21]}</a></div>";
$tmp = "<br /><br /><p>{$l_filearch2[23]}</p>";
print str_replace("{dir}", $path, $tmp);
	 }


  //////////////////////////////////////////////////////////////////////////////
  //�������� ���������
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    $query = "DELETE FROM {$gl_db_prefix}filearch2_items
                 WHERE id_cat = {$id_cat}";
    db_delete($query);

    $query = "DELETE FROM {$gl_db_prefix}filearch2_cats
                 WHERE id_cat = {$id_cat}";
    db_delete($query);

    $query = "DELETE FROM {$gl_db_prefix}filearch2_stat
                 WHERE id_cat = {$id_cat}";
    db_delete($query);

    //��������� ������� ��������� ���������
    $query = "UPDATE {$gl_db_prefix}filearch2_cats
                 SET pos = pos - 1
                WHERE pos > {$pos}";
    db_update($query);

    //������� � ������ ���������
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL='index.cfm?mod=filearch2_cats_list'></HEAD></HTML>";
    exit;
  }



?>