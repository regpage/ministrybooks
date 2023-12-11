<?php
  //////////////////////////////////////////////////////////////////////////////
  // ����������� ����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ �������� ��������� ����
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_menu = intval($_GET['id_menu']);
  if(empty($id_menu))
    $id_menu = intval($_POST['id_menu']);


  //////////////////////////////////////////////////////////////////////////////
  // ������� ������� �������� ����� �����
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}menu
               WHERE id_menu = {$id_menu}";
    $results = db_select($query);
    if(is_array($results))
    {
      $title = stripslashes($results[0]['title']);
      $disposition = stripslashes($results[0]['disposition']);
      $separator = stripslashes($results[0]['separator']);
      $pos = $results[0]['pos'];
      $old_pos = $pos;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //���������� ������ �����
    $old_pos = intval($_POST['old_pos']);

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

    //��������� �������
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}menu
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}menu
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
      //��������� ��������� ����
      $query = "UPDATE {$gl_db_prefix}menu
                   SET title = '{$title}',
                 	     disposition  = '{$disposition}',
	                      `separator`  = '{$separator}',
	                      pos   = {$pos}
                WHERE id_menu = {$id_menu} ";
      db_update($query);
      //������������ ������� � ������ ����
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=menu_list'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_menu[19]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}menu/_menu_edit.inc");

  //��������� � ������ ����
  print "<p><a class='Mustgreen' href='?adm=menu_list'>{$l_menu[22]}</a></p>";
?>