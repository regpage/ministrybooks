<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // ������ ��������� ����� ���������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����, ���������� ���������
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //���������� ������ �����
    $title          = correct_input($_POST['title']);
    $descr          = correct_input($_POST['descr']);
    $pos            = intval($_POST['pos']);

    if(empty($title))
      $errors[] = $l_filearch2[17];
    if($pos < 1)
      $errors[] =  $l_filearch2[18];

    //��������� ����
    if(empty($errors))
    {
      $query = "INSERT INTO {$gl_db_prefix}filearch2_cats SET
                   id_cat   = NULL,
                   if_arch_user   = {$gl_id_user},
                   title    = '{$title}',
                   descr    = '{$descr}',
                   pos      = {$pos}";
      db_insert($query);

      //������� ����������
      $id_cat = db_insert_id();
      $dirname = sprintf("%03d", $id_cat);

      if(!mkdir("{$gl_path_to_root}content/_filearch2/{$dirname}",0777))
      {      	 db_delete("DELETE FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}");
      	 $errors[] = str_replace("{dir}", "{$gl_path_to_root}content/_filearch2/{$dirname}", $l_filearch2[19]);
      }

      //��������� �������
      $query = "UPDATE {$gl_db_prefix}filearch2_cats
                   SET pos = pos + 1
                 WHERE pos >= {$pos}";
      db_update($query);

      //������������ ������� � ������ ���������
      //echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL='index.cfm?mod=filearch2_cats_list'></HEAD></HTML>";
          //������� � ������ ���������
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=filearch2_cats_list'></HEAD></HTML>";
    exit;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //�������� �������������� ������� ���������
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}filearch2_cats";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }


  //���������
  print "<img src='themes/file_archiv/images/add_categoriu2.gif' height = 100px><h1></h1>";

  //���������� �����
  include("{$gl_path_to_engine_root}mods/filearch2/_cats_edit.inc");

  //������ �����
  print "<p><a class='chap' href='index.cfm?mod=filearch2_cats_list'>{$l_filearch2[1000]}</a></p>";
  print "<br />";
  print "<br />";

?>