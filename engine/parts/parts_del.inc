<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� � ����������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ������ id_part
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
	 //////////////////////////////////////////////////////////////////////////////

	 $id_part      = intval($_GET['id_part']);
	 $id_part_prec = intval($_GET['id_part_prec']);
	 $state        = intval($_GET['state']);

  //�������� ��������� �������
  $query = "SELECT pos
              FROM {$gl_db_prefix}parts
             WHERE id_part  = {$id_part}";
  $results = db_select($query);
  $pos = $results[0]['pos'];


  //////////////////////////////////////////////////////////////////////////////
  //�������
  //////////////////////////////////////////////////////////////////////////////

  //������� ������ id_part �� ����� ������������ � ����������
  //������� �������� ��������
	 function del_part($id_part)
	 {
	   global $gl_db_prefix;

	   //������� �������� �� �������� ������� � ���� ������
	   $query = "SELECT id_item
	               FROM {$gl_db_prefix}parts_items
	              WHERE id_part = {$id_part}";
	   $results = db_select($query);
	   if(is_array($results))
	   {
	     $cnt = count($results);
	     for($i = 0; $i < $cnt; $i++)
	     {
	       $id_item = $results[$i]['id_item'];
	       $path = "content/{$id_item}";
		      if(file_exists($path) && is_dir($path))
		        remove_dir($path);

	       $query = "DELETE FROM {$gl_db_prefix}pages_blocks
	               WHERE id_pg = {$id_item}";
	    	  db_delete($query);

		      $query = "DELETE FROM {$gl_db_prefix}pages_images
		                 WHERE id_pg = {$id_item}";
		      db_delete($query);
	     }
	   }

	   $query = "DELETE FROM {$gl_db_prefix}parts_items
	               WHERE id_part = {$id_part}";
	   db_delete($query);

	   //������� ��� ������
	   $query = "DELETE FROM {$gl_db_prefix}parts
	               WHERE id_part = {$id_part}";
	   db_delete($query);

	   $query = "SELECT id_part
	               FROM {$gl_db_prefix}parts
	              WHERE id_part_prec = {$id_part}";
	   $results = db_select($query);
	   if(is_array($results))
	   {
	     $cnt = count($results);
	     for($i = 0; $i < $cnt; $i++)
	     {
	       $child_id_part = $results[$i]['id_part'];
	       del_part($child_id_part);
	     }
	   }
	 }


  //////////////////////////////////////////////////////////////////////////////
  //���������� ���� ������������� ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_parts[35]}</h1><br><br><br><br><br><div align='center'><br><br><a href='?adm=parts_del&id_part={$id_part}&state=1&id_part_prec={$id_part_prec}'>{$l_adm_gen[5]}</a> <a href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_adm_gen[6]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  // ������� ������
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    //������� ������
    del_part($id_part);

    //��������� ������� ��������� ��������
    $query = "UPDATE {$gl_db_prefix}parts
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_part_prec = {$id_part_prec}";
    db_update($query);

    //��������� � ������ ��������
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
    exit;
  }



?>