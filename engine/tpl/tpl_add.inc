<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� �����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ����� ������ ����� � �������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //���������� ������ �����
    $title = correct_input($_POST['title']);
    $file  = correct_input($_POST['file']);
    $pos   = intval($_POST['pos']);

    if(empty($title))
      $errors[] = $l_tpl[16];
    if($pos < 1)
      $errors[] = $l_tpl[17];
    if(preg_match("/[^a-z0-9_]/i", $file) || strlen($file) == 0)
      $errors[] = $l_tpl[18];
    elseif(preg_match("/[0-9]/i", $file[0]))
      $errors[] = $l_tpl[19];
    $maintpl = correct_input($_POST['maintpl']);
    if($maintpl != 'yes')
      $maintpl = 'no';

    if(empty($errors))
    {
       //��������� �������
      $query = "UPDATE {$gl_db_prefix}sitetpl
                   SET pos = pos + 1
                 WHERE pos >= {$pos}";
      db_update($query);

      //��������� ��������� ������� � ��
      $query = "INSERT INTO {$gl_db_prefix}sitetpl SET
                   id_tpl = NULL,
                   title = '{$title}',
                   file  = '{$file}',
                   maintpl = '{$maintpl}',
                   pos   = {$pos}";
      db_insert($query);

      //��������� ������ ���� � ������� ��� ���������
      $fp = fopen ("{$gl_path_to_templates}site/{$file}.tpl", "w");
      fwrite ($fp, "");
      fclose ($fp);

      //��������� ������ ���� � �������, ������� ������������ (� ������������� ������)
      $fp = fopen ("{$gl_path_to_templates}site/{$file}.inc", "w");
      fwrite ($fp, "");
      fclose ($fp);

      //���� ������ ������� ��� ��������, ������� ���� ������ � ������� �������
      if($maintpl == 'yes')
      {
        $id_tpl = db_insert_id();
        $query = "UPDATE {$gl_db_prefix}sitetpl
                     SET maintpl = 'no'
                    WHERE id_tpl != {$id_tpl}";
        db_update($query);
      }

      //������������ ������� � ������ �������� �����
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=tpl_list'></HEAD></HTML>";
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //�������� �������������� ������� ��������
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}sitetpl";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //���������
  print "<h1>{$l_tpl[14]}</h1>";

  //�����
  include("{$gl_path_to_engine}tpl/_tpl_edit.inc");

  //��������� � ������ ��������
  print "<p><a class='Mustgreen' href='?adm=tpl_list'>{$l_tpl[20]}</a></p>";

?>