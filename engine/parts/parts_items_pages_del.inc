<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль удаляет страницу $id_item из раздел $id_part
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

	 $id_item      = intval($_GET['id_item']);
	 $id_part_prec = intval($_GET['id_part_prec']);
	 $state        = intval($_GET['state']);

  //выборка параметров страницы
  $query = "SELECT pos
              FROM {$gl_db_prefix}parts_items
             WHERE id_item  = {$id_item}";
  $results = db_select($query);
  $pos = $results[0]['pos'];


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно подтверждения удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_parts[62]}</h1><br><br><br><br><br><div align='center'><br><br><a href='?adm=parts_items_pages_del&id_item={$id_item}&state=1&id_part_prec={$id_part_prec}'>{$l_adm_gen[5]}</a> <a href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_adm_gen[6]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //уладяем страницу из бд и файловой системы
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    $query = "DELETE FROM {$gl_db_prefix}parts_items
               WHERE id_item = {$id_item}";
    db_delete($query);

    $path = "content/{$id_item}";
    if(file_exists($path) && is_dir($path))
      remove_dir($path);

    $query = "DELETE FROM {$gl_db_prefix}pages_blocks
               WHERE id_pg = {$id_item}";
    db_delete($query);

    $query = "DELETE FROM {$gl_db_prefix}pages_images
               WHERE id_pg = {$id_item}";
    db_delete($query);

     //калибруем позицию остальных элементов
    $query = "UPDATE {$gl_db_prefix}parts_items
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_part = {$id_part_prec}";
    db_update($query);

    //переходим в список страниц и разделов
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
    exit;
  }



?>