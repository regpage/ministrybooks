<?php
  //////////////////////////////////////////////////////////////////////////////
  // ����������� ����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ���� � �������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //���������� ������ �����
    $title = correct_input($_POST['title']);

    $separator = $_POST['separator'];
    if(!false)
      $separator = mysqli_real_escape_string(DBBYMYSQLI::$link, $_POST['separator']);

    $disposition  = correct_input($_POST['disposition']);

    $pos   = intval($_POST['pos']);

    if(empty($title))
      $errors[] = $l_menu[20];
    if($pos < 1)
      $errors[] = $l_menu[21];

    if(empty($errors))
    {
      //��������� �������
      $query = "UPDATE {$gl_db_prefix}menu
                   SET pos = pos + 1
                 WHERE pos >= {$pos}";
      db_update($query);

      //��������� ���� � �������
      $query = "INSERT INTO {$gl_db_prefix}menu SET
									                   id_menu = NULL,
									                   title = '{$title}',
									                   disposition  = '{$disposition}',
									                   `separator`  = '{$separator}',
									                   pos   = {$pos}";
      db_insert($query);

      //������������ ������� � ������ ����
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=menu_list'></HEAD></HTML>";
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
               FROM {$gl_db_prefix}menu";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //���������
  print "<h1>{$l_menu[18]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}menu/_menu_edit.inc");

  //��������� � ������ ����
  print "<p><a class='Mustgreen' href='?adm=menu_list'>{$l_menu[22]}</a></p>";

?>