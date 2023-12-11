<?php
  
  //////////////////////////////////////////////////////////////////////////////
  //ћодуль добавл€ет нового автора книги в систему
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализаци€ переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
      $id_part_prec = intval($_POST['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = 0;


  //////////////////////////////////////////////////////////////////////////////
  // ќбработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //инициализаци€, фильтраци€ переменных формы
    $author = correct_input($_POST['author']);
    $id_author   = intval($_POST['id_author']);
    $about_author = correct_input($_POST['about_author']);
    $pos   = intval($_POST['pos']);

    if(empty($author))
      $errors[] = $l_parts[33];
    if($pos < 1)
      $errors[] = $l_parts[34];

    //обновл€ем базу данных
    if(empty($errors))
    {
     //провер€ем им€ на уникальность
    $query = "SELECT id_author
                FROM {$gl_db_prefix}parts_author
               WHERE author = '{$author}'";
    $result = db_select_one($query);
    if(!empty($result))
    {
      //$errors[] = "јвтор <b>{$author}</b> уже используетс€, введите другой.";
      $tmp = $l_users[19];
      $tmp = str_replace("{author}", $author, $tmp);
      $errors[] = $tmp;
    }
}
 if(empty($errors))
    {
       //калибруем позицию
      $query = "UPDATE {$gl_db_prefix}parts_author
                   SET pos = pos + 1
                 WHERE pos >= {$pos}";
      db_update($query);


      //добавл€ем новый раздел
      $query = "INSERT INTO {$gl_db_prefix}parts_author
                   SET id_author = NULL,
                      author = '{$author}',
                      pos   = {$pos},
                     about_author = '{$about_author}'";
      db_insert($query);

      //осуществл€ем переход в список разделов.
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=author_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // ‘орма
  //////////////////////////////////////////////////////////////////////////////

//выбираем предполагаемую позицию раздела
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}parts_author";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }


  //заголовок
  print "<h1>{$l_parts[31]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}parts/_author_edit.inc");

  //ссылка "назад"
  print "<p><a class='Mustgreen' href='?adm=author_list&id_part_prec='{$id_part_prec}'>{$l_parts[36]}</a></p>";

?>