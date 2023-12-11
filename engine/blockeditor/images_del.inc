<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль удаляет изображение блока.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_block = intval($_GET['id_block']);
  $id_img = intval($_GET['id_img']);
  $state    = intval($_GET['state']);

  //выборка параметров удаляемого элемента
  $query = "SELECT pos
              FROM {$gl_db_prefix}{$ed_tbl_pref}_images
             WHERE id_img  = {$id_img}";
  $results = db_select($query);
  $pos = $results[0]['pos'];
  unset($results);


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно подтверждения удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_blockeditor[70]}</h1><br><br><br><br><br><br><div align='Center'><a href='{$ed_url}&ed_opt=blocks_images_del&pg={$ed_pg}&id_block={$id_block}&state=1&id_img={$id_img}'>{$l_gen[20]}</a> <a target='_parent' href='{$ed_url}&ed_opt=blocks_images_list&pg={$ed_pg}&id_block={$id_block}'>{$l_gen[21]}</a></div><br><br>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //удаление изображения
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {

    //удаляем изображение из директории страницы
    $query = "SELECT img_min, img_max
                FROM {$gl_db_prefix}{$ed_tbl_pref}_images
               WHERE id_img = {$id_img}";
    $results = db_select($query);
    if(is_array($results))
    {
      //уменьшеннная копия
      $path = "{$ed_path_to_img}{$results[0]['img_min']}";
      if(file_exists($path) && !is_dir($path))
	        unlink($path);
      //увеличенная копия
      $path = "{$ed_path_to_img}{$results[0]['img_max']}";
      if(file_exists($path) && !is_dir($path))
	       unlink($path);
    }

    //удаляем изображение
    $query = "DELETE FROM {$gl_db_prefix}{$ed_tbl_pref}_images
               WHERE id_img = {$id_img}";
    db_delete($query);

    //калибруем позицию остальных элементов
    $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_images
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_block = {$id_block}";
    db_update($query);

    //получаем html-код всей страницы
    $page = ed_process_data($ed_tbl_pref, $ed_pg);

    //пересохраняем страницу
    save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $page, 'w');

    //переходим в список изображений блока
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$ed_url}&ed_opt=blocks_images_list&pg={$ed_pg}&id_block={$id_block}'></HEAD></HTML>";
    exit;
  }



?>