<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� � ����������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ����� ������ � �������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
      $id_part_prec = intval($_POST['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = 0;


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //�������������, ���������� ���������� �����
    $title = correct_input($_POST['title']);
    $pos   = intval($_POST['pos']);
    $id_tpl = intval($_POST['id_tpl']);

    if(empty($title))
      $errors[] = $l_parts[33];
    if($pos < 1)
      $errors[] = $l_parts[34];

    //��������� ���� ������
    if(empty($errors))
    {
      //��������� �������
      $query = "UPDATE {$gl_db_prefix}parts
                   SET pos = pos + 1
                 WHERE id_part_prec = {$id_part_prec}
                   AND pos >= {$pos}";
      db_update($query);

      //��������� ����� ������
      $query = "INSERT INTO {$gl_db_prefix}parts
                   SET id_part = NULL,
                       title = '{$title}',
                       pos   = {$pos},
                       id_tpl = {$id_tpl},
                       id_part_prec = {$id_part_prec}";
      db_insert($query);

      //������������ ������� � ������ ��������.
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // �����
  //////////////////////////////////////////////////////////////////////////////

  //�������� �������������� ������� �������
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}parts
               WHERE id_part_prec = {$id_part_prec}";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }


  //���������
  print "<h1>{$l_parts[31]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}parts/_parts_edit.inc");

  //������ "�����"
  print "<p><a class='Mustgreen' href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a></p>";

?>