<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

	 $id_author      = intval($_GET['id_author']);
	 $id_part_prec = intval($_GET['id_part_prec']);
	 $state        = intval($_GET['state']);

  //������� ���������� ��������
  $query = "SELECT pos
              FROM {$gl_db_prefix}parts_author
             WHERE id_author  = {$id_author}";
  $results = db_select($query);
  $pos = $results[0]['pos'];


  //////////////////////////////////////////////////////////////////////////////
  //���������� ���� ������������� ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_parts[62]}</h1><br><br><br><br><br><div align='center'><br><br><a href='?adm=author_del&id_author={$id_author}&state=1'>{$l_adm_gen[5]}</a> <a href='?adm=author_list'>{$l_adm_gen[6]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //������� �������� �� �� � �������� �������
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    $query = "DELETE FROM {$gl_db_prefix}parts_author
               WHERE id_author = {$id_author}";
    db_delete($query);

        //��������� ������� ��������� ���������
    $query = "UPDATE {$gl_db_prefix}parts_author
                 SET pos = pos - 1
               WHERE pos > {$pos}";
    db_update($query);

    //��������� � ������ ������� � ��������
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=author_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
    exit;
  }

