<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль удаляет блок.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_block = intval($_GET['id_block']);
  $state = intval($_GET['state']);

  //выбираем параметры блока
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
  //диалоговое окно подтверждения удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<div align='center'><h1>{$l_blockeditor[51]}</h1><br><br><a href='{$ed_url}&ed_opt=blocks_del&pg={$ed_pg}&id_block={$id_block}&state=1'>{$l_gen[20]}</a> <a target='_parent' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}&id_block={$id_block}'>{$l_gen[21]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //удяляем блок
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    //удаляем файл, связанный с файловым блоком
    if($block_type == 'file')
    {
      $path = $ed_path_to_file.$params['file'];
       if(file_exists($path))
        unlink($path);
    }

    //удаляем изображения блока images из файловой системы
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
	         //удаляем уменьшенную копию
	         $path = "{$ed_path_to_img}{$results[$i]['img_min']}";
	         if(file_exists($path) && !is_dir($path))
	            unlink($path);
	         //удаляем увеличенную копию
	         $path = "{$ed_path_to_img}{$results[$i]['img_max']}";
	         if(file_exists($path) && !is_dir($path))
	            unlink($path);
	       }
	     }

	     //удаляем изображения из базы
	     $query = "DELETE FROM {$gl_db_prefix}{$ed_tbl_pref}_images
	                WHERE id_block = {$id_block}";
	     db_delete($query);
    }

    //удаляем блок
    $query = "DELETE FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
               WHERE id_block = {$id_block}";
    db_delete($query);

    //калибруем позицию остальных элементов
    $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_pg = {$ed_pg}";
    db_update($query);

    //получаем html-код всей страницы
    $page = ed_process_data($ed_tbl_pref, $ed_pg);

    //пересохраняем страницу
    save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $page, 'w');

    //переходим в список блоков
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'></HEAD></HTML>";
    exit;
  }



?>