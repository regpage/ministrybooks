<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Модуль редактирует параметры страницы id_item
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_part = intval($_GET['id_part']);
  if(empty($id_part))
      $id_part = intval($_POST['id_part']);

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = intval($_POST['id_part_prec']);

  $id_item = intval($_GET['id_item']);
  if(empty($id_item))
    $id_item = intval($_POST['id_item']);

  $p_save = $_GET['p_save'];
    if(empty($p_save))
  $p_save = $_POST['p_save'];

   //////////////////////////////////////////////////////////////////////////////
  // Выборка текущих значений полей формы
  //////////////////////////////////////////////////////////////////////////////

if(!empty($_POST['save'])) 
// if(!empty($p_save) && $p_save = "saved")
//if(isset($_POST['save']))
    {
        print "<div class='message' style='margin-top:20px;'>$l_parts[89]</div>";

    }
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
      $bookstorelink = stripslashes($results[0]['bookstorelink']);
      $img_book_store = stripslashes($results[0]['img_book_store']);
      $pos   = $results[0]['pos'];
      $old_pos = $pos;
      $date = $results[0]['date'];
      //$date  = date("d-m-Y", strtotime($results[0]['date']));
      $date = explode('-',$date);
      $date = "$date[2]-$date[1]-$date[0]";
      $params = unserialize(stripslashes($results[0]['params']));
      $descr = $params['descr'];
      $keywords = $params['keywords'];
      $date_entry = $results[0]['dateentry'];
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////
  //if(isset($_POST['save']))
  if(!empty($_POST['save']))
  {
    //инициализация, фильтрация переменных формы
    $title = correct_input($_POST['title']);
    $id_author = intval($_POST['id_author']);
    $isbn = correct_input($_POST['isbn']);
    $bookstorelink = correct_input($_POST['bookstorelink']);
    $img_book_store = correct_input($_POST['img_book_store']);
    $date  = strtotime($_POST['date']);
    //$date  = date("d-m-Y", $date);
    $date = explode('-', correct_input($_POST['date']));
    //$date = preg_match("/([0-9]{1,2})-([0-9]{1,2})-([0-9]{4})/i",$date,$reg);
    $date = "$date[2]-$date[1]-$date[0]";

    $pos   = intval($_POST['pos']);
    $old_pos   = intval($_POST['old_pos']);
    if(empty($title))
      $errors[] = $l_parts[60];
    if(empty($id_author))
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
                       bookstorelink   = '{$bookstorelink}',
                       img_book_store   = '{$img_book_store}',
                       date   = '{$date}',
                       pos   = '{$pos}',
                       params = '{$params}'
                 WHERE id_item = '{$id_item}'";
      db_update($query);

 // $p_save = "saved";

  /* осуществляем переход в список разделов.
   echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
   return;
*/
 //echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_items_pages_edit&id_part_prec={$id_part_prec}'></HEAD></HTML>";
  // return;
header("refresh: 1; url=?adm=parts_items_pages_edit&id_part_prec={$id_part_prec}&id_item={$id_item}");     
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////


  //ссылка назад
   print "<p style='padding-top:20px;'><strong>/</strong> <a href='?adm=parts_items_pages_text&ed_opt=blocks_list&pg={$id_item}&id_part={$id_part_prec}&id_item={$id_item}
'>Редактировать книгу</a> <strong>/</strong> <a href='?adm=parts_items_pages_chapter&ed_opt=blocks_list_chupters&pg={$id_item}'>{$l_parts[86]}</a> <strong>/</strong> <a href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a> <strong>/</strong> <a href='?adm=parts_pages_search'>Найти страницу</a> <strong>/</strong></p>";
  // заголовок
if (isset($date_entry) || !is_null($date_entry)) {$date_entry_recorde = "<span style='font-size: 11pt; color: rgb(214,86,43);'> / " . $date_entry . "</span>";}
  print "<h1>{$l_parts[59]} {$date_entry_recorde}</h1>";


  //подключаем форму
  include("{$gl_path_to_engine}parts/_pages_edit.inc");

  //ссылка назад
   print "<p><strong>/</strong> <a href='?adm=parts_items_pages_text&ed_opt=blocks_list&pg={$id_item}&id_part={$id_part_prec}&id_item={$id_item}
'>Редактировать книгу</a> <strong>/</strong> <a href='?adm=parts_items_pages_chapter&ed_opt=blocks_list_chupters&pg={$id_item}'>{$l_parts[86]}</a> <strong>/</strong> <a href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a> <strong>/</strong> <a href='?adm=parts_pages_search'>Найти страницу</a> <strong>/</strong></p>";


?>