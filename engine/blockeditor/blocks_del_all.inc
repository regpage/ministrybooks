<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // ������ ������� ��������� ������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $state    = intval($_GET['state']);
  if(empty($state))
    $state    = intval($_POST['state']);

  $to_del = $_POST['items'];

  if(is_array($to_del))
  {
  	 foreach($to_del as $key => $value)
  	 {
      $to_del[$key] = intval($value);
  	 }
  }


  //////////////////////////////////////////////////////////////////////////////
  //���������� ���� ������������� ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST['del_all']))
  {
    if(is_array($to_del))
    {
    	 print "<h1>{$l_blockeditor[78]}</h1>";
	     print "<form name='del_form' action='' method='post'>";
	     print "<br /><br /><br /><br /><br />";
	     print "<div align='center'><input type='submit' name='del_all' value='{$l_adm_gen[5]}'>&nbsp;<input type='button' name='back' value='{$l_adm_gen[6]}' onClick=\"location.href='?adm={$gl_adm}&amp;ed_opt=blocks_list&amp;pg={$ed_pg}'\"></div>";
      foreach($to_del as $key => $value)
      {
        print "<input type='hidden' name='items[]' value='$value'>";

      }
      print "</p>";
      print "<input type='hidden' name='adm' value='{$gl_adm}'>";
      print "<input type='hidden' name='pg' value='{$ed_pg}'>";
      print "<input type='hidden' name='ed_opt' value='{$ed_opt}'>";
      print "</form>";
    }
    //��������� � ���, ��� �� ���� ������������ �� ������
    else
    {
      print "<h1>{$l_blockeditor[79]}</h1>";
      print "<p>{$l_blockeditor[80]}<br /><a href='?adm={$gl_adm}&amp;ed_opt=blocks_list&amp;pg={$ed_pg}'>{$l_adm_gen[11]}</a></p>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //������� ��������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['del_all']))
  {
    foreach($to_del as $key => $id_block)
    {
      $results = db_select("SELECT pos, gen_type, params
                              FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
                             WHERE id_block = {$id_block}");

      $pos = $results[0]['pos'];
      $params = unserialize($results[0]['params']);
				  $block_type = $results[0]['type'];
				  $block_gen_type = $results[0]['gen_type'];

      //������� ����, ��������� � �������� ������
		    if($block_type == 'file')
		    {
		      $path = $ed_path_to_file.$params['file'];
		       if(file_exists($path))
		        unlink($path);
		    }

		    //������� ����������� ����� images �� �������� �������
		    if($block_gen_type == 'images')
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

    }

    //��������� � ������ ������
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm={$gl_adm}&amp;ed_opt=blocks_list&amp;pg={$ed_pg}'></HEAD></HTML>";
    exit;
  }




?>