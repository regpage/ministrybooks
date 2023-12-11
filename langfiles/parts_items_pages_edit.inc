<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль редактирует параметры страницы id_item
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = intval($_POST['id_part_prec']);

  $id_item = intval($_GET['id_item']);
  if(empty($id_item))
    $id_item = intval($_POST['id_item']);

  //////////////////////////////////////////////////////////////////////////////
  // Выборка текущих значений полей формы
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}parts_items
               WHERE id_item = {$id_item}";
    $results = db_select($query);
    if(is_array($results))
    {
      $title = stripslashes($results[0]['title']);
      $id_author = $results[0]['id_author'];
      $isbn = stripslashes($results[0]['isbn']);
      $pos   = $results[0]['pos'];
      $old_pos = $pos;
      $date = $results[0]['date'];
      $date = explode('-',$date);
      $date = "$date[2]-$date[1]-$date[0]";
      $params = unserialize(stripslashes($results[0]['params']));
      $descr = $params['descr'];
      $keywords = $params['keywords'];
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //инициализация, фильтрация переменных формы
    $title = correct_input($_POST['title']);
    $id_author = intval($_POST['id_author']);
    $isbn = correct_input($_POST['isbn']);
    $date = explode('-',$_POST['date']);
    //$date = preg_match("/([0-9]{1,2})-([0-9]{1,2})-([0-9]{4})/i",$date,$reg);
    $date = "$date[2]-$date[1]-$date[0]";
    $pos   = intval($_POST['pos']);
    $old_pos   = intval($_POST['old_pos']);
    if(empty($title))
      $errors[] = $l_parts[60];
    if(empty($id_author) Or $id_author = $l_parts[80])
      $errors[] = $l_parts[79];
    if($pos < 1)
      $errors[] = $l_parts[61];
    $params['descr'] = correct_input($_POST['descr']);
    $params['keywords'] = correct_input($_POST['keywords']);
    $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));

    //калибруем позицию
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}parts_items
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}
                         AND id_part = {$id_part_prec}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}parts_items
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}
                         AND id_part = {$id_part_prec}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    //обновляем базу данных
    if(empty($errors))
    {
      //добавляем новый элемент

      $query = "UPDATE {$gl_db_prefix}parts_items
                   SET title = '{$title}',
                       id_author   = '{$id_author}',
                       isbn   = '{$isbn}',
                       date   = '{$date}',
                       pos   = '{$pos}',
                       params = '{$params}'
                 WHERE id_item = '{$id_item}'";
      db_update($query);

      //осуществляем переход в список разделов.
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_parts[59]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}parts/_pages_edit.inc");

  //ссылка назад
  print "<p><a class='Mustgreen' href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a></p>";

?>