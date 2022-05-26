<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // ћодуль учитывает скачивание файла $id_item
  //////////////////////////////////////////////////////////////////////////////


  //получаем GET параметры
  $id_item = intval($_GET['id_item']);

  //выбираем id категории
  $id_cat = db_select_one("SELECT id_cat FROM {$gl_db_prefix}filearch2_items WHERE id_item = {$id_item}");

  //путь к файлу
		$path      = "content/_filearch2/".sprintf("%03d", $id_cat)."/";

		//выбираем параметры файла
  $query   = "SELECT * FROM {$gl_db_prefix}filearch2_items WHERE id_item = {$id_item}";
  $results = db_select($query);
  $file    = stripslashes($results[0]['file']);


  //получаем адрес файла
  $path    = $path.$file;

  //получаем ip
  $ip = correct_input($_SERVER['REMOTE_ADDR']);
  if(empty($ip))
    $ip = 'no';

   //подсчитываем число скачиваний
	  $filearch2_downloaded = unserialize($_SESSION['filearch2_downloaded']);
	  if(!@in_array($id_item, $filearch2_downloaded))
	  {
	    $query = "INSERT INTO {$gl_db_prefix}filearch2_stat
	                      SET id_stat = NULL,
	                          id_item = {$id_item},
	                          date    = NOW(),
	                          id_cat  = {$id_cat},
	                          ip      = '{$ip}'";

	   db_update($query);
    $filearch2_downloaded[] = $id_item;
    $_SESSION['filearch2_downloaded']= serialize($filearch2_downloaded);
   }

   //переходим на адрес url
   header("Location: {$gl_site}{$path}", 1);
   exit;


?>