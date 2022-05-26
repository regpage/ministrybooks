<?php
  //////////////////////////////////////////////////////////////////////////////
  // CMS Ortus
  // File archive M2
  // by Anton Fedorchenko (antf@inbox.ru, antf@pochta.ru)
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Изменение параметров файла $id_item
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_cat = intval($_GET['id_cat']);
  if(empty($id_cat))
    $id_cat = intval($_POST['id_cat']);

  $id_item = intval($_GET['id_item']);
  if(empty($id_item))
    $id_item = intval($_POST['id_item']);

  //выбираем параметры категории
  $query = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}";
  $results = db_select($query);
  $cat_title = stripslashes($results[0]['title']);
  $path          = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";


  //////////////////////////////////////////////////////////////////////////////
  //выборка предыдущих значений формы
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query       = "SELECT * FROM {$gl_db_prefix}filearch2_items WHERE id_item = {$id_item}";
				$results     = db_select($query);
				$file     = stripslashes($results[0]['file']);
				$old_file = $file;
				$pos         = $results[0]['pos'];
				$old_pos     = $pos;
				$title       = stripslashes($results[0]['title']);
				$descr       = stripslashes($results[0]['descr']);
  }


  //////////////////////////////////////////////////////////////////////////////
  // обработчик формы, изменение параметров файла
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных формы
    $title          = correct_input($_POST['title']);

    $descr          = correct_input($_POST['descr']);

    $file_sel       = correct_input($_POST['file_sel']);

				$old_file = $_POST['old_file'];

    $pos            = intval($_POST['pos']);
    $old_pos        = intval($_POST['old_pos']);

    if($pos < 1)
      $errors[] =  $l_filearch2[40];

    if(empty($errors))
    {
		    //загружаем файл
		    if(!empty($_FILES['file']['name']))
		    {
		      $arr = form_file_copy($path, 'file', $old_file);
		      if(!empty($arr['error']))
		        $errors[] = $arr['error'];
		      else
		        $file = $arr['new_file_name'];
		    }
		    //выбираем файл
		    elseif(!empty($file_sel))
		    {
		      $file = $file_sel;
		    }

 	    if(empty($file))
		      $file = $old_file;
    }

     //калибруем позицию
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}filearch2_items
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}
                         AND id_cat = {$id_cat}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}filearch2_items
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}
                         AND id_cat = {$id_cat}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    //обновляем базу
    if(empty($errors))
    {
      if(empty($title))
        $title = $file;

      $query = "UPDATE {$gl_db_prefix}filearch2_items
                        SET title = '{$title}',
                            descr = '{$descr}',
                            file  = '{$file}',
                            pos   = {$pos}
                      WHERE id_item = {$id_item}";
      db_insert($query);

      //осуществляем переход в список файлов
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL='?mod=filearch2_items_list&amp;id_cat={$id_cat}'></HEAD></HTML>";
      return;
    }
    else
    {
    	 //удаляем изображения, если при их добавлении возникли ошибки
    	 /*if(file_exists("{$path}{$min_img}") && !is_dir("{$path}{$min_img}"))
    	   unlink("{$path}{$min_img}");
    	 if(file_exists("{$path}{$max_img}") && !is_dir("{$path}{$max_img}"))
    	   unlink("{$path}{$max_img}");*/
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h4>{$l_filearch2[52]}</h4>";

  //подключаем форму
  include("{$gl_path_to_engine_root}mods/filearch2/_items_edit.inc");

  //ссылки назад
  print "<p><a class='chap' href='?mod=filearch2_items_list&amp;id_cat={$id_cat}'>{$l_filearch2[1002]}</a></p>";
  print "<p><a class='chap' href='?mod=filearch2_cats_list'>{$l_filearch2[1000]}</a></p>";
?>