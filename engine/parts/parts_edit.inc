<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� � ����������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ���������� ������� id_part
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_part = intval($_GET['id_part']);
  if(empty($id_part))
      $id_part = intval($_POST['id_part']);

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
      $id_part_prec = intval($_POST['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = 0;


  //////////////////////////////////////////////////////////////////////////////
  // ������� ������� �������� ����� �����
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}parts
               WHERE id_part = {$id_part}";
    $results = db_select($query);
    $title = stripslashes($results[0]['title']);
    $pos = $results[0]['pos'];
    //$in_site_map = $results[0]['in_site_map'];
    $id_tpl = $results[0]['id_tpl'];
    $old_pos = $pos;
  }


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //�������������, ���������� ���������� �����
    $title = correct_input($_POST['title']);
    $pos   = intval($_POST['pos']);
    $old_pos = intval($_POST['old_pos']);
    $id_tpl = intval($_POST['id_tpl']);

    $tpl_on_subparts = correct_input($_POST['tpl_on_subparts']);
    if($tpl_on_subparts != 'yes')
      $tpl_on_subparts = 'no';

    if(empty($title))
      $errors[] = $l_parts[33];    
    if($pos < 1)
      $errors[] = $l_parts[34];

    //��������� ������ � �����������
    if($tpl_on_subparts == 'yes')
    {

      //��������� ������ $id_tpl � ������������ ������� $id_part_prec
      function set_tpl_on_subparts($id_part_prec, $id_tpl)
      {
        global $gl_db_prefix;

        $query = "SELECT id_part
                    FROM {$gl_db_prefix}parts
                   WHERE id_part_prec = {$id_part_prec}";

        $results = db_select($query);
        if(is_array($results))
        {
          $cnt = count($results);
          for($i = 0; $i < $cnt; $i++)
          {
            $id_part = $results[$i]['id_part'];

            $query = "UPDATE {$gl_db_prefix}parts
                         SET id_tpl = {$id_tpl}
                        WHERE id_part = {$id_part}";
            db_update($query);
            set_tpl_on_subparts($id_part, $id_tpl);
          }
        }
      }

      set_tpl_on_subparts($id_part, $id_tpl);
    }

    //��������� �������
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}parts
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}
                         AND id_part_prec = {$id_part_prec}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}parts
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}
                         AND id_part_prec = {$id_part_prec}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    if(empty($errors))
    {
      //��������� ����
      $query = "UPDATE {$gl_db_prefix}parts
                   SET title = '{$title}',
                        pos   = {$pos},
                       id_tpl = {$id_tpl}
                WHERE id_part = {$id_part}";
      db_update($query);

      //������������ ������� � ������ ��������.
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  // �����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_parts[32]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}parts/_parts_edit.inc");

  //������ �����
  print "<p><a class='Mustgreen' href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a></p>";

?>