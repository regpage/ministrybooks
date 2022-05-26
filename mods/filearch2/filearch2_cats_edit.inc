<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive
  // Модуль изменяет параметры категории $id_cat
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_cat = intval($_GET['id_cat']);
  if(empty($id_cat))
  $id_cat = intval($_POST['id_cat']);


  //////////////////////////////////////////////////////////////////////////////
  // выборка предыдущих значений
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
  	 $query = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}";
  	 $results = db_select($query);

    $title          = stripslashes($results[0]['title']);
    $descr         = stripslashes($results[0]['descr']);
    $pos            = $results[0]['pos'];
    $old_pos        = $pos;
  }


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы, изменение параметров категории
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных формы
    $title          = correct_input($_POST['title']);
    $descr          = correct_input($_POST['descr']);
    $pos            = intval($_POST['pos']);
    $old_pos        = intval($_POST['old_pos']);

    if(empty($title))
      $errors[] = $l_filearch2[17];
    if($pos < 1)
      $errors[] =  $l_filearch2[18];

     //калибруем позицию
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}filearch2_cats
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}filearch2_cats
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    //обновляем данные категории в таблице filearch2_cats
    if(empty($errors))
    {
      $query = "UPDATE {$gl_db_prefix}filearch2_cats SET
                   title    = '{$title}',
                   descr    = '{$descr}',
                   pos      = {$pos}
              WHERE id_cat = {$id_cat} ";
      db_insert($query);

      //осуществляем переход в список категорий
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0'; URL='index.cfm?mod=filearch2_cats_list'></HEAD></HTML>";
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h4>{$l_filearch2[16]}</h4>";

  //форма
  include("{$gl_path_to_engine_root}mods/filearch2/_cats_edit.inc");

  //ссылка назад
  print "<p><a class='chap' href='index.cfm?mod=filearch2_cats_list'>{$l_filearch2[1000]}</a></p>";
  print "<br />";
  print "<br />";

?>