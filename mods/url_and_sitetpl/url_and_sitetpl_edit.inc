<?php
  //////////////////////////////////////////////////////////////////////////////
  // Модуль изменяет параметры соответствия $id_item
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_item = intval($_GET['id_item']);
  if(empty($id_item))
    $id_item = intval($_POST['id_item']);


  //////////////////////////////////////////////////////////////////////////////
  // выборка предыдущих значений
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
  	 $query = "SELECT * FROM {$gl_db_prefix}url_and_sitetpl WHERE id_item = {$id_item}";
  	 $results = db_select($query);

    $url            = stripslashes($results[0]['url']);
    $id_tpl         = $results[0]['id_tpl'];
    $pos            = $results[0]['pos'];
    $id_item        = $results[0]['id_item'];
    $old_pos        = $pos;
  }


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы, изменение параметров соответствия
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных формы
    $url          = correct_input($_POST['url']);
    $id_tpl       = intval($_POST['id_tpl']);
    $pos          = intval($_POST['pos']);
    $old_pos      = intval($_POST['old_pos']);

    if(empty($url))
      $errors[] = $l_url_and_sitetpl[8];
    if($pos < 1)
      $errors[] =  $l_url_and_sitetpl[7];

     //калибруем позицию
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}url_and_sitetpl
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}url_and_sitetpl
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    //обновляем данные в таблице url_and_sitetpl
    if(empty($errors))
    {
      $query = "UPDATE {$gl_db_prefix}url_and_sitetpl SET
                   url      = '{$url}',
                   id_tpl   = {$id_tpl},
                   pos      = {$pos}
                 WHERE id_item = {$id_item}";
      db_insert($query);

      //осуществляем переход в список соответствий
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=url_and_sitetpl_list'></HEAD></HTML>";
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_url_and_sitetpl[6]}</h1>";

  //форма
  include("{$gl_path_to_engine_root}mods/url_and_sitetpl/_form.inc");

  //ссылка назад
  print "<p><a class='Mustgreen' href='index.cfm?mod=url_and_sitetpl_list'>{$l_url_and_sitetpl[1000]}</a></p>";
?>