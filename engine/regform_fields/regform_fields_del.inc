<?php

  //////////////////////////////////////////////////////////////////////////////
  // ������� ���� $id_field ����� $id_form
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_field = intval($_GET['id_field']);
  $state    = intval($_GET['state']);


  //////////////////////////////////////////////////////////////////////////////
  //���������� ���� ������������� ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_regform_fields[52]}</h1><br><br><br><br><div align='center'><a href='?adm=regform_fields_del&id_field={$id_field}&state=1'>{$l_gen[20]}</a> <a href='?adm=regform_fields_list&id_field={$id_field}'>{$l_gen[21]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //������� ����
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    //�������� ��������� ���������� ����
    $query   = "SELECT *
                FROM {$gl_db_prefix}regform_fields
               WHERE id_field = {$id_field}";
    $results = db_select($query);
    $pos     = $results[0]['pos'];
    $page    = $results[0]['page'];
    $type    = $results[0]['type'];
    $field_name     = $results[0]['field_name'];

    //������� ����
    $query = "DELETE FROM {$gl_db_prefix}regform_fields
               WHERE id_field = {$id_field}";
    db_delete($query);

    //��������� �������
    $query = "UPDATE {$gl_db_prefix}regform_fields
                 SET pos = pos - 1
               WHERE pos > {$pos}";
    db_update($query);

    //������� ���� �� ������� users
		  if($type != 'groupe_title')
		  {
		    $query = "ALTER TABLE {$gl_db_prefix}users
		              DROP {$field_name}";
		    db_update($query);
    }

    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=regform_fields_list'></HEAD></HTML>";
    exit;

  }





?>