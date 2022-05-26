<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive
  // Добавление файла в категорию $id_cat
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_cat = intval($_GET['id_cat']);
  if(empty($id_cat))
    $id_cat = intval($_POST['id_cat']);

  $part = intval($_GET['part']);
  if(empty($part))
    $part = intval($_POST['part']);


  //////////////////////////////////////////////////////////////////////////////
  // выбираем параметры категории
  //////////////////////////////////////////////////////////////////////////////

  $query     = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}";
  $results   = db_select($query);
  $cat_title = stripslashes($results[0]['title']);
  $path      = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";


  //////////////////////////////////////////////////////////////////////////////
  // обработчик формы, добавление файла
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных формы
    $title          = correct_input($_POST['title']);
    $descr          = correct_input($_POST['descr']);
    $pos            = intval($_POST['pos']);
    $file_sel    = correct_input($_POST['file_sel']);

    if($pos < 1)
      $errors[] =  $l_filearch2[40];

    if(empty($errors))
    {
		    //загружаем файл
		    if(!empty($_FILES['file']['name']))
		    {                                                              //не более 2-х мегов
		      $arr = form_file_copy($path, 'file', $old_file_name = '');
		      if(!empty($arr['error']))
		        $errors[] = $arr['error'];
		      else
		        $file = $arr['new_file_name'];
		    }
		    //выбираем файл
		    elseif(!empty($file_sel))
		    {
		      $file = $file_sel;
		    } else $file = '';

		  }

    //обновляем базу
    if(empty($errors))
    {
      if(empty($title))
        $title = $file;

      //калибруем позицию
      $query = "UPDATE {$gl_db_prefix}filearch2_items
                   SET pos = pos + 1
                 WHERE pos >= {$pos}
                   AND id_cat = {$id_cat}";
      db_update($query);

      $query = "INSERT INTO {$gl_db_prefix}filearch2_items
                        SET id_item = NULL,
                            title = '{$title}',
                            descr = '{$descr}',
                            file    = '{$file}',
                            pos     = {$pos},
                            date    = NOW(),
                            id_cat  = {$id_cat}";
      db_insert($query);

      //осуществляем переход в список файлов категории $id_cat
      //echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0'; URL='index.cfm?mod=filearch2_items_list&id_cat={$id_cat}'></HEAD></HTML>";
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=filearch2_items_list&amp;id_cat={$id_cat}'></HEAD></HTML>";

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
  // форма
  //////////////////////////////////////////////////////////////////////////////

  //выбираем предполагаемую позицию файла
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}filearch2_items
              WHERE id_cat = {$id_cat} ";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //заголовок
  print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h4>{$l_filearch2[33]}</h4>";

  //форма
  include("{$gl_path_to_engine_root}mods/filearch2/_items_edit.inc");

  //ссылка назад
  print "<p><a class='chap' href='?mod=filearch2_items_list&amp;id_cat={$id_cat}&amp;part={$part}'>{$l_filearch2[1002]}</a></p>";
  print "<p><a class='chap' href='?mod=filearch2_cats_list'>{$l_filearch2[1000]}</a></p>";
?>