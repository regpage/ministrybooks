<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� �����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������ ��������� ������� id_tpl
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_tpl = intval($_GET['id_tpl']);
  if(empty($id_tpl))
    $id_tpl = intval($_POST['id_tpl']);


  //////////////////////////////////////////////////////////////////////////////
  //������� ������� ���������� �������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}sitetpl
               WHERE id_tpl = {$id_tpl}";
    $results = db_select($query);
    if(is_array($results))
    {
      $title = stripslashes($results[0]['title']);
      //$file  = stripslashes($results[0]['file']);
      $pos   = $results[0]['pos'];
      $old_pos = $pos;
      $maintpl   = $results[0]['maintpl'];
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //���������� ������ �����
    $title = correct_input($_POST['title']);
    $pos   = intval($_POST['pos']);
    $old_pos   = intval($_POST['old_pos']);

    if(empty($title))
      $errors[] = $l_tpl[16];
    if($pos < 1)
      $errors[] = $l_tpl[17];

    $maintpl = correct_input($_POST['maintpl']);
    if($maintpl != 'yes')
      $maintpl = 'no';

    //��������� �������
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}sitetpl
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}sitetpl
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    if(empty($errors))
    {
      //���� ������ ������� ��� ��������, ������� ���� ������ � ������� �������
      if($maintpl == 'yes')
      {

        $query = "UPDATE {$gl_db_prefix}sitetpl
                     SET maintpl = 'no'
                    WHERE id_tpl != {$id_tpl}";
        db_update($query);
      }

      //������ ��������� ������� � ����
      $query = "UPDATE {$gl_db_prefix}sitetpl SET
                   title = '{$title}',
                   maintpl = '{$maintpl}',
                   pos   = {$pos}
                 WHERE id_tpl = {$id_tpl}";
      db_insert($query);



      //������������ ������� � ������ �������� �����
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=tpl_list'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_tpl[15]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}tpl/_tpl_edit.inc");

  //��������� � ������ ��������
  print "<p><a class='Mustgreen' href='?adm=tpl_list'>{$l_tpl[20]}</a></p>";


?>