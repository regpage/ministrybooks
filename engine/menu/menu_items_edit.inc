<?php
  //////////////////////////////////////////////////////////////////////////////
  //  онструктор меню
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ћодуль измен€ет параметры пункта меню id_item
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализаци€ переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_item_prec = intval($_GET['id_item_prec']);
  if(empty($id_item_prec))
    $id_item_prec = intval($_POST['id_item_prec']);

  $id_menu = intval($_GET['id_menu']);
  if(empty($id_menu))
    $id_menu = intval($_POST['id_menu']);

  $id_item = intval($_GET['id_item']);
  if(empty($id_item))
    $id_item = intval($_POST['id_item']);


  //////////////////////////////////////////////////////////////////////////////
  // ¬ыборка текущих значений полей формы
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}menu_items
               WHERE id_item = {$id_item}";
    $results = db_select($query);
    if(is_array($results))
    {
      $url = stripslashes($results[0]['url']);
      $pos = $results[0]['pos'];
      $old_pos = $pos;
      $caption = stripslashes($results[0]['caption']);
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  // ќбработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтраци€ данных
    $caption = correct_input($_POST['caption']);
    $url     = correct_input($_POST['url']);
    $pos     = intval($_POST['pos']);
    $old_pos = intval($_POST['old_pos']);

    if(empty($caption))
      $errors[] = $l_menu[55];
    if(empty($url))
      $errors[] = $l_menu[56];
    if($pos < 1)
      $errors[] = $l_menu[57];

    //калибруем позицию
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}menu_items
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}
                         AND id_item_prec = {$id_item_prec}
                         AND id_menu = {$id_menu}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}menu_items
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}
                         AND id_item_prec = {$id_item_prec}
                         AND id_menu = {$id_menu}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    if(empty($errors))
    {
      //обновл€ем параметры пункта
      $query = "UPDATE {$gl_db_prefix}menu_items SET
                   caption = '{$caption}',
                   url = '{$url}',
                   pos   = {$pos}
               WHERE id_item = {$id_item}";
      db_update($query);

      //осуществл€ем переход в список пунктов меню id_menu
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=menu_items_list&id_menu={$id_menu}&id_item_prec={$id_item_prec}'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //‘орма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_menu[54]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}menu/_items_edit.inc");

  //вернутьс€ в список меню
  print "<p><a class='Mustgreen' href='?adm=menu_list'>{$l_menu[22]}</a></p>";

?>