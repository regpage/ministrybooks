<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ����������� � ����.
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_block = intval($_GET['id_block']);
  if(empty($id_block))
    $id_block = intval($_POST['id_block']);


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //���������� ������
    $title      = correct_input($_POST['title']);
    $text       = correct_input($_POST['text']);
    $pos        = intval($_POST['pos']);

    if(empty($pos) || $pos < 1)
      $errors[] = $l_blockeditor[68] ;
    if(empty($title))
      //$errors[] = "���������, ����������, ���� <b>��������</b>.";
      $title = $pos;

    //�������� ������. ����� �����������
    if(empty($errors))
    {
	     //$dir = "img/command/";
      if(!empty($_FILES['img_min']['name']))
      {
        $arr = form_image_copy($ed_path_to_img, 'img_min', $old_img_name = '');
        if(!empty($arr['error']))
          $errors[] = $arr['error'];
        else
          $img_min = $arr['new_img_name'];
      } else $errors[] = $l_blockeditor[69] ;

    }

    //�������� ����������� ����� �����������
    if(empty($errors))
    {
	     //$dir = "img/command/";
      if(!empty($_FILES['img_max']['name']))
      {
        $arr = form_image_copy($ed_path_to_img, 'img_max', $old_img_name = '', 512000);
        if(!empty($arr['error']))
          $errors[] = $arr['error'];
        else
          $img_max = $arr['new_img_name'];
      } else $img_max = '';

    }

    //������� ����������� � ������ ������
    if(!empty($errors))
    {
      if(!empty($img_min))
        if(is_file("{$ed_path_to_img}{$img_min}"))
          unlink("{$ed_path_to_img}{$img_min}");
      if(!empty($img_max))
        if(is_file("{$ed_path_to_img}{$img_max}"))
          unlink("{$ed_path_to_img}{$img_max}");
    }

    if(empty($errors))
    {
      //��������� ������� ��������� ����������� � �����
      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_images
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                      AND id_block = {$id_block}";
      db_update($query);

      //��������� ����������� � ����
      $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_images
                    SET id_img = NULL,
                        title      = '{$title}',
                        text      = '{$text}',
                        img_min    = '{$img_min}',
                        img_max    = '{$img_max}',
                        pos        = {$pos},
                        id_pg      = {$ed_pg},
                        id_block   = {$id_block}";

      db_insert($query);

      //�������� html-��� ���� ��������
      $page = ed_process_data($ed_tbl_pref, $ed_pg);

      //������������� ��������
      save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $page, 'w');

      //��������� � ������ ����������� �����
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$ed_url}&ed_opt=blocks_images_list&pg={$ed_pg}&id_block={$id_block}'></HEAD></HTML>";
      exit;

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_blockeditor[66]}</h1>";

  //�������� �������������� ������� �����������
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}{$ed_tbl_pref}_images
               WHERE id_block = {$id_block}";
              // print $query;
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //���������� �����
  include("{$ed_path_to_editor}_images_edit.inc");

  //������ "�����"
  print "<p><a class='Mustgreen' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'>{$l_blockeditor[71]}</a></p>";

?>