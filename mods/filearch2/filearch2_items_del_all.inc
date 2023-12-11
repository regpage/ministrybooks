<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Удаляет несколько файлов из категории $id_cat
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $state    = intval($_GET['state']);
  if(empty($state))
    $state    = intval($_POST['state']);

  $id_cat     = intval($_GET['id_cat']);
  if(empty($id_cat))
    $id_cat     = intval($_POST['id_cat']);

  $to_del = $_POST['items'];

  //выбираем параметры категории
  $query   = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}";
  $results = db_select($query);
  $path    = stripslashes($results[0]['folder']);
  $path    = $gl_path_to_root.$path;


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно подтверждения удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST['del_all']))
  {
    if(is_array($to_del))
    {
    	 print "<h3>{$l_filearch2[56]}</h3>";
	     print "<form name='del_form' action='' method='post'>";
	     print "<br /><br / ><br /><br /><br />";
	     print "<div align='center'><input type='submit' name='del_all' value='{$l_gen[20]}'>&nbsp;<input type='button' name='back' value='{$l_gen[21]}' onClick=\"location.href='?mod=filearch2_items_list&amp;state=1&amp;id_cat={$id_cat}&amp;part={$part}'\"></div>";
      foreach($to_del as $key => $id_item)
      {
        print "<input type='hidden' name='items[$key]' value='{$id_item}'>";
      }
      print "<input type='hidden' name='mod' value='filearch2_items_del_all'>";
      print "<input type='hidden' name='id_cat' value='{$id_cat}'>";
      print "</form>";
    }
    else
    {
      print "<h1>{$l_filearch2[57]}</h1>";
      print "<p>{$l_filearch2[58]}<br><a class='chap' href='?mod=filearch2_items_list&amp;id_cat={$id_cat}'>{$l_filearch2[59]}</a></p>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //удаляем файлы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['del_all']))
  {

    foreach($to_del as $id_item => $value)
    {
	     //выбираем параметры файла
				  $query   = "SELECT * FROM {$gl_db_prefix}filearch2_items WHERE id_item = {$id_item}";
				  $results = db_select($query);
				  $file = stripslashes($results[0]['file']);
				  $pos     = $results[0]['pos'];

      //удаляем файл
			   $file_path = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/{$file}";
			   if(file_exists($file_path) && !is_dir($file_path))
			     unlink($file_path);

			   //удаляем элемент из базы данных
			   $query = "DELETE FROM {$gl_db_prefix}filearch2_items
			              WHERE id_item = {$id_item}";
			   db_delete($query);

      $query = "DELETE FROM {$gl_db_prefix}filearch2_stat
			              WHERE id_item = {$id_item}";
			   db_delete($query);

		    //калибруем позицию остальных элементов
		    $query = "UPDATE {$gl_db_prefix}filearch2_items
		                 SET pos = pos - 1
		               WHERE pos > {$pos}
		                 AND id_cat = {$id_cat}";
		    db_update($query);
    }


    //переходим в список файлов id_cat
	   print "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL='?mod=filearch2_items_list&amp;id_cat={$id_cat}'></HEAD></HTML>";
	   exit;
  }

?>