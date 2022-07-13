<?php
  //////////////////////////////////////////////////////////////////////////////
  // Конструктор меню
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль добавляет меню в систему
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных формы
    $title = correct_input($_POST['title']);

    $separator = $_POST['separator'];
    if(true) //!get_magic_quotes_gpc()
      $separator = mysqli_escape_string(DBBYMYSQLI::$link,$_POST['separator']);

    $disposition  = correct_input($_POST['disposition']);

    $pos   = intval($_POST['pos']);

    if(empty($title))
      $errors[] = $l_menu[20];
    if($pos < 1)
      $errors[] = $l_menu[21];

    if(empty($errors))
    {
      //калибруем позицию
      $query = "UPDATE {$gl_db_prefix}menu
                   SET pos = pos + 1
                 WHERE pos >= {$pos}";
      db_update($query);

      //добавляем меню в таблицу
      $query = "INSERT INTO {$gl_db_prefix}menu SET
									                   id_menu = NULL,
									                   title = '{$title}',
									                   disposition  = '{$disposition}',
									                   `separator`  = '{$separator}',
									                   pos   = {$pos}";
      db_insert($query);

      //осуществляем переход в список меню
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=menu_list'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //выбираем предполагаемую позицию элемента
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}menu";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //заголовок
  print "<h1>{$l_menu[18]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}menu/_menu_edit.inc");

  //вернуться в список меню
  print "<p><a class='Mustgreen' href='?adm=menu_list'>{$l_menu[22]}</a></p>";

?>