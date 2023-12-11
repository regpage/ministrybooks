<?php
  ///////////////////////////////////////////////////
  // Задействует Antf Blockeditor или WYSIWYG editor
  // для редактирования текста страницы в пользовательской части
  /////////////////////////////////////////////////

  //сохраняем нужные get - переменные
  $new_page = intval($_GET['new_page']);
  if($new_page == 1)
  {
    $id_item = intval($_GET['pg']);
    $_SESSION['be_id_item'] = $id_item;
  }
  else
  {
    $id_item = intval($_SESSION['be_id_item']);
  }


  ///////////////////////////////////////////////////
  //формируем ссылку "Назад"
  /////////////////////////////////////////////////

  //выбираем название раздела
  $query = "SELECT title, id_part
              FROM {$gl_db_prefix}parts_items
             WHERE id_item = {$id_item}";
  $res = mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));

  $results = db_select($query);
  if(is_array($results))
  {
    $ed_item_title = stripslashes($results[0]['title']);
    $id_part = $results[0]['id_part'];

  }
  $ed_back_href = "<a href='?mb={$id_item}'>{$l_pages[4]} &laquo;{$ed_item_title}&raquo;</a>";
 // $ed_back_href = "<a href='?mb={$id_item}'>{$l_pages[4]} &laquo;{$ed_item_title}&raquo;</a>";

  ///////////////////////////////////////////////////
  //Проверяем права <img height='18px' width='34px' src='images/double-arrows-left.png' alt='double-arrows-left'>
  /////////////////////////////////////////////////

  if($gl_group == 'unregistered')
    exit;
  if($gl_group == 'editors')
  {
    $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = {$gl_id_group}
               AND act = 'edit'";

    $tmp = db_select_one($query);

    if($tmp)
    {
      $query = "SELECT title
                  FROM {$gl_db_prefix}parts
                 WHERE id_part = {$id_part}";
      $part_title = stripslashes(db_select_one($query));
      print "{$l_pages[2]} {$gl_group} {$l_pages[3]} {$part_title}.</p>";
      exit;
    }
  }

  ///////////////////////////////////////////////////
  //Ключевые переменные
  /////////////////////////////////////////////////

  //заголовок
  $query = "SELECT title
              FROM {$gl_db_prefix}parts
             WHERE id_part = {$id_part}";
  $ed_part_title = stripslashes(db_select_one($query));
  $ed_h1_prefix = "{$l_pages[2]} :: {$ed_part_title} :: {$l_pages[3]} :: {$ed_item_title}";

  //адрес этого модуля
  $ed_url = "?mod=pages_text";
  //префикс mysql-таблиц с блоками
  $ed_tbl_pref = 'pages';
  //текущая страница редактора
  $ed_opt = preg_replace("/[^a-z0-9_]/", '', $_GET['ed_opt']);
  //id_item редактируемой страницы
  $ed_pg  = preg_replace("/[^a-z0-9_]/", '', $_GET['pg']);
  if(empty($ed_pg))
    $ed_pg  = preg_replace("/[^a-z0-9_]/", '', $_POST['pg']);
  //путь к редактору
  $ed_path_to_editor = "{$gl_path_to_engine}blockeditor/";
  //путь к директории, где сохраняется html-код страницы
  $ed_path_to_file   = "{$gl_path_to_root}content/{$ed_pg}/";
  //путь к директории, где сохраняется изображения страницы
  $ed_path_to_img   = "{$gl_path_to_root}content/{$ed_pg}/";
  //путь к директории, где сохраняется изображения страницы для url
  $ed_path_to_img_for_url = "content/{$ed_pg}/";

  //подключение функций редактора
  include("{$ed_path_to_editor}func.inc");

  //выборка текущего модуля редактора в зависимости от переменной ed_post
  include("{$ed_path_to_editor}blocks_pages.inc");

  //ссылка назад
  //print "<p>{$ed_back_href}</p>";
?>