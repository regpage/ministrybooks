<?php

  //////////////////////////////////////////////////////////////////////////////
  // ������ ��������� ����� ������������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //���������� ������ �����
    $url          = correct_input($_POST['url']);
    $id_tpl       = intval($_POST['id_tpl']);
    $pos          = intval($_POST['pos']);

    if(empty($url))
      $errors[] = $l_url_and_sitetpl[8];
    if($pos < 1)
      $errors[] =  $l_url_and_sitetpl[7];

    //��������� ����
    if(empty($errors))
    {
      //��������� �������
      $query = "UPDATE {$gl_db_prefix}url_and_sitetpl
                   SET pos = pos + 1
                 WHERE pos >= {$pos}";
      db_update($query);

      $query = "INSERT INTO {$gl_db_prefix}url_and_sitetpl SET
                   id_item   = NULL,
                   id_tpl   = {$id_tpl},
                   url      = '{$url}',
                   pos      = {$pos}";
      db_insert($query);

      //������������ ������� � ������ ������������
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=url_and_sitetpl_list'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //�������� �������������� ������� ���������
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}url_and_sitetpl";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }


  //���������
  print "<h1>{$l_url_and_sitetpl[5]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine_root}mods/url_and_sitetpl/_form.inc");

  //������ �����
  print "<p><a class='Mustgreen' href='index.cfm?mod=url_and_sitetpl_list'>{$l_url_and_sitetpl[1000]}</a></p>";
?>