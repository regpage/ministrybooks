<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль добавляет новую страницу в раздел id_part
  //////////////////////////////////////////////////////////////////////////////


  //инициализация переменных
  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
      $id_part_prec = intval($_POST['id_part_prec']);
  if(empty($id_part_prec))
   return;

  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //инициализация, фильтрация переменных
    $title = correct_input($_POST['title']);
    $id_author = correct_input($_POST['id_author']);
    $isbn = correct_input($_POST['isbn']);
    $bookstorelink = correct_input($_POST['bookstorelink']);
    $img_book_store = correct_input($_POST['img_book_store']);
    $pos   = intval($_POST['pos']);    
    $date = explode("-",$_POST['date']);
    $date = "$date[2]-$date[1]-$date[0]";
    if(empty($title))
      $errors[] = $l_parts[60];
    if(empty($id_author))
      $errors[] = $l_parts[79];
    if($pos < 1)
      $errors[] = $l_parts[61];
    $params['descr'] = correct_input($_POST['descr']);
    $params['keywords'] = correct_input($_POST['keyworkds']);
    $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));

    //обновляем базу данных
    if(empty($errors))
    {
      //калибруем позицию
      $query = "UPDATE {$gl_db_prefix}parts_items
                   SET pos = pos + 1
                 WHERE id_part = {$id_part_prec}
                   AND pos >= {$pos}";
      db_update($query);

      //добавляем новый элемент
      $query = "INSERT INTO {$gl_db_prefix}parts_items
                   SET id_item = NULL,
                       i_type = 'page',
                       title = '{$title}',
                       id_author = '{$id_author}',
                       date   = '{$date}',                                   
                       isbn = '{$isbn}',
                       bookstorelink   = '{$bookstorelink}',
                       img_book_store   = '{$img_book_store}',
                       pos   = {$pos},
                       params = '{$params}',
                       id_part = {$id_part_prec}";
      db_insert($query);

      //создаем директорию в папке content
      $id_item = db_insert_id();
      mkdir("content/{$id_item}", 0777);

      //осуществляем переход в список разделов.
/*      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
      return; */
header("refresh: 1; url=?adm=parts_items_pages_edit&id_part_prec={$id_part_prec}&id_item={$id_item}"); 
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //выбираем предполагаемую позицию элемента
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}parts_items
               WHERE id_part = {$id_part_prec}";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //заголовок
  print "<h1>{$l_parts[58]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}parts/_pages_edit.inc");

  //ссылка "назад"
  print "<p><a href='?adm=parts_list&id_part_prec={$id_part_prec}'> &#9668; {$l_parts[36]}</a></p>";

?>