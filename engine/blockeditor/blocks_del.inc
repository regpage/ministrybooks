<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ����.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_block = intval($_GET['id_block']);
  $state = intval($_GET['state']);

  //�������� ��������� �����
  $query = "SELECT pos, params, type
              FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
             WHERE id_block  = {$id_block}";
  $results = db_select($query);
  $pos = $results[0]['pos'];
  $params = unserialize($results[0]['params']);
  $block_type = $results[0]['type'];
  $block_gen_type = $results[0]['gen_type'];
  unset($results);


  //////////////////////////////////////////////////////////////////////////////
  //���������� ���� ������������� ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<div align='center'><h1>{$l_blockeditor[51]}</h1><br><br><a href='{$ed_url}&ed_opt=blocks_del&pg={$ed_pg}&id_block={$id_block}&state=1'>{$l_gen[20]}</a> <a target='_parent' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}&id_block={$id_block}'>{$l_gen[21]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //������� ����
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    //������� ����, ��������� � �������� ������
    if($block_type == 'file')
    {
      $path = $ed_path_to_file.$params['file'];
       if(file_exists($path))
        unlink($path);
    }

    //������� ����������� ����� images �� �������� �������
    if($block_type == 'images')
    {
      $query = "SELECT img_min, img_max
                  FROM {$gl_db_prefix}{$ed_tbl_pref}_images
                 WHERE id_block = {$id_block}";
      $results = db_select($query);

    	 if(is_array($results))
	     {
	       $cnt = count($results);
	       for($i = 0; $i < $cnt; $i++)
	       {
	         //������� ����������� �����
	         $path = "{$ed_path_to_img}{$results[$i]['img_min']}";
	         if(file_exists($path) && !is_dir($path))
	            unlink($path);
	         //������� ����������� �����
	         $path = "{$ed_path_to_img}{$results[$i]['img_max']}";
	         if(file_exists($path) && !is_dir($path))
	            unlink($path);
	       }
	     }

	     //������� ����������� �� ����
	     $query = "DELETE FROM {$gl_db_prefix}{$ed_tbl_pref}_images
	                WHERE id_block = {$id_block}";
	     db_delete($query);
    }

    //������� ����
    $query = "DELETE FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
               WHERE id_block = {$id_block}";
    db_delete($query);

    //��������� ������� ��������� ���������
    $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_pg = {$ed_pg}";
    db_update($query);

    //�������� html-��� ���� ��������
    $page = ed_process_data($ed_tbl_pref, $ed_pg);

    //������������� ��������
    save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $page, 'w');

    //��������� � ������ ������
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'></HEAD></HTML>";
    exit;
  }



?>