<?php
  //////////////////////////////////////////////////////////////////////////////
  // ����������� ����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ����� � ���� $id_menu
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_item_prec = intval($_GET['id_item_prec']);
  if(empty($id_item_prec))
    $id_item_prec = intval($_POST['id_item_prec']);

  $id_menu = intval($_GET['id_menu']);
  if(empty($id_menu))
    $id_menu = intval($_POST['id_menu']);


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //���������� ������ �����
    $caption = correct_input($_POST['caption']);
    $url     = correct_input($_POST['url']);
    $pos     = intval($_POST['pos']);

    if(empty($caption))
      $errors[] = $l_menu[55];
    if(empty($url))
      $errors[] = $l_menu[56];
    if($pos < 1)
      $errors[] = $l_menu[57];

    if(empty($errors))
    {
      //��������� �������
      $query = "UPDATE {$gl_db_prefix}menu_items
                   SET pos = pos + 1
                 WHERE id_item_prec = {$id_item_prec}
                   AND id_menu = {$id_menu}
                   AND pos >= {$pos}";
      db_update($query);

      //��������� �����
      $query = "INSERT INTO {$gl_db_prefix}menu_items SET
                   id_item = NULL,
                   caption = '{$caption}',
                   url = '{$url}',
                   pos   = {$pos},
                   id_menu = {$id_menu},
                   id_item_prec = {$id_item_prec}";
      db_insert($query);

      //������������ ������� � ������ �������
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=menu_items_list&id_menu={$id_menu}&id_item_prec={$id_item_prec}'></HEAD></HTML>";
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
               FROM {$gl_db_prefix}menu_items
              WHERE id_item_prec = {$id_item_prec}
                AND id_menu = {$id_menu}";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //���������
  print "<h1>{$l_menu[53]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}menu/_items_edit.inc");

  //��������� � ������ ����
  print "<p><a class='Mustgreen' href='?adm=menu_list'>{$l_menu[22]}</a></p>";
?>