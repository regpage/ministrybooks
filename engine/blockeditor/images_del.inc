<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ����������� �����.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_block = intval($_GET['id_block']);
  $id_img = intval($_GET['id_img']);
  $state    = intval($_GET['state']);

  //������� ���������� ���������� ��������
  $query = "SELECT pos
              FROM {$gl_db_prefix}{$ed_tbl_pref}_images
             WHERE id_img  = {$id_img}";
  $results = db_select($query);
  $pos = $results[0]['pos'];
  unset($results);


  //////////////////////////////////////////////////////////////////////////////
  //���������� ���� ������������� ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_blockeditor[70]}</h1><br><br><br><br><br><br><div align='Center'><a href='{$ed_url}&ed_opt=blocks_images_del&pg={$ed_pg}&id_block={$id_block}&state=1&id_img={$id_img}'>{$l_gen[20]}</a> <a target='_parent' href='{$ed_url}&ed_opt=blocks_images_list&pg={$ed_pg}&id_block={$id_block}'>{$l_gen[21]}</a></div><br><br>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //�������� �����������
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {

    //������� ����������� �� ���������� ��������
    $query = "SELECT img_min, img_max
                FROM {$gl_db_prefix}{$ed_tbl_pref}_images
               WHERE id_img = {$id_img}";
    $results = db_select($query);
    if(is_array($results))
    {
      //������������ �����
      $path = "{$ed_path_to_img}{$results[0]['img_min']}";
      if(file_exists($path) && !is_dir($path))
	        unlink($path);
      //����������� �����
      $path = "{$ed_path_to_img}{$results[0]['img_max']}";
      if(file_exists($path) && !is_dir($path))
	       unlink($path);
    }

    //������� �����������
    $query = "DELETE FROM {$gl_db_prefix}{$ed_tbl_pref}_images
               WHERE id_img = {$id_img}";
    db_delete($query);

    //��������� ������� ��������� ���������
    $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_images
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_block = {$id_block}";
    db_update($query);

    //�������� html-��� ���� ��������
    $page = ed_process_data($ed_tbl_pref, $ed_pg);

    //������������� ��������
    save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $page, 'w');

    //��������� � ������ ����������� �����
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$ed_url}&ed_opt=blocks_images_list&pg={$ed_pg}&id_block={$id_block}'></HEAD></HTML>";
    exit;
  }



?>