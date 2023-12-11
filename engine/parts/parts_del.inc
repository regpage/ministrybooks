<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль удаляет раздел id_part
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
	 //////////////////////////////////////////////////////////////////////////////

	 $id_part      = intval($_GET['id_part']);
	 $id_part_prec = intval($_GET['id_part_prec']);
	 $state        = intval($_GET['state']);

  //выбираем параметры раздела
  $query = "SELECT pos
              FROM {$gl_db_prefix}parts
             WHERE id_part  = {$id_part}";
  $results = db_select($query);
  $pos = $results[0]['pos'];


  //////////////////////////////////////////////////////////////////////////////
  //Функции
  //////////////////////////////////////////////////////////////////////////////

  //удаляет раздел id_part со всеми подразделами и страницами
  //функция содержит рекурсию
	 function del_part($id_part)
	 {
	   global $gl_db_prefix;

	   //удаляем страницы из файловой системы и базы данных
	   $query = "SELECT id_item
	               FROM {$gl_db_prefix}parts_items
	              WHERE id_part = {$id_part}";
	   $results = db_select($query);
	   if(is_array($results))
	   {
	     $cnt = count($results);
	     for($i = 0; $i < $cnt; $i++)
	     {
	       $id_item = $results[$i]['id_item'];
	       $path = "content/{$id_item}";
		      if(file_exists($path) && is_dir($path))
		        remove_dir($path);

	       $query = "DELETE FROM {$gl_db_prefix}pages_blocks
	               WHERE id_pg = {$id_item}";
	    	  db_delete($query);

		      $query = "DELETE FROM {$gl_db_prefix}pages_images
		                 WHERE id_pg = {$id_item}";
		      db_delete($query);
	     }
	   }

	   $query = "DELETE FROM {$gl_db_prefix}parts_items
	               WHERE id_part = {$id_part}";
	   db_delete($query);

	   //удаляем сам раздел
	   $query = "DELETE FROM {$gl_db_prefix}parts
	               WHERE id_part = {$id_part}";
	   db_delete($query);

	   $query = "SELECT id_part
	               FROM {$gl_db_prefix}parts
	              WHERE id_part_prec = {$id_part}";
	   $results = db_select($query);
	   if(is_array($results))
	   {
	     $cnt = count($results);
	     for($i = 0; $i < $cnt; $i++)
	     {
	       $child_id_part = $results[$i]['id_part'];
	       del_part($child_id_part);
	     }
	   }
	 }


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно подтверждения удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_parts[35]}</h1><br><br><br><br><br><div align='center'><br><br><a href='?adm=parts_del&id_part={$id_part}&state=1&id_part_prec={$id_part_prec}'>{$l_adm_gen[5]}</a> <a href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_adm_gen[6]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  // удаляем раздел
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    //удаляем раздел
    del_part($id_part);

    //калибруем позицию остальных разделов
    $query = "UPDATE {$gl_db_prefix}parts
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_part_prec = {$id_part_prec}";
    db_update($query);

    //переходим в список раздедов
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
    exit;
  }



?>