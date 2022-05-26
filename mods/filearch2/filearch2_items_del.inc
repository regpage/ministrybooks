<?php
  //////////////////////////////////////////////////////////////////////////////
  // CMS Ortus
  // File archive M2
  // by Anton Fedorchenko (antf@inbox.ru, antf@pochta.ru)
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Модуль удаляет файл $id_item
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

 	$id_item      = intval($_GET['id_item']);
	 $id_cat       = intval($_GET['id_cat']);
	 $state        = intval($_GET['state']);

  //выбираем путь к файлу
  $path          = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";

  //выбираем параметры файла
  $query   = "SELECT * FROM {$gl_db_prefix}filearch2_items WHERE id_item = {$id_item}";
  $results = db_select($query);
  $file = stripslashes($results[0]['file']);
  $pos     = $results[0]['pos'];


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно подтверждения удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h4>{$l_filearch2[53]}</h4><div align='center'><a href='index.cfm?mod=filearch2_items_del&amp;id_item={$id_item}&amp;state=1&amp;id_cat={$id_cat}'>{$l_gen[20]}</a> <a href='index.cfm?mod=filearch2_items_list&amp;id_cat={$id_cat}'>{$l_gen[21]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //удаление файла
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {

	   $path = "{$path}{$file}";
	   if(file_exists($path) && !is_dir($path))
	     unlink($path);

	   //удаляем элемент из базы данных
	   $query = "DELETE FROM {$gl_db_prefix}filearch2_items
	              WHERE id_item = {$id_item}";
	   db_delete($query);

	   $query = "DELETE FROM {$gl_db_prefix}filearch2_stat
	              WHERE id_item = {$id_item}";
	   db_delete($query);

    //калибруем позицию остальных файлов
    $query = "UPDATE {$gl_db_prefix}filearch2_items
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_cat = {$id_cat}";
    db_update($query);

    //переходим в список файлов id_cat
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=filearch2_items_list&amp;id_cat={$id_cat}'></HEAD></HTML>";
    exit;
  }
?>