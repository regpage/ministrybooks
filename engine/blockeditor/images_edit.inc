<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль позволяет поменять параметры изображения блока.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_block = intval($_GET['id_block']);
  if(empty($id_block))
    $id_block = intval($_POST['id_block']);

  $id_img = intval($_GET['id_img']);
  if(empty($id_img))
    $id_img = intval($_POST['id_img']);


  //////////////////////////////////////////////////////////////////////////////
  //выборка предыдущих значений формы
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT title, text, img_min, img_max, pos
                FROM {$gl_db_prefix}{$ed_tbl_pref}_images
               WHERE id_img = {$id_img}";
    $results = db_select($query);
    if(is_array($results))
    {
      $title   = stripslashes($results[0]['title']);
      $text    = stripslashes($results[0]['text']);
      $img_min = stripslashes($results[0]['img_min']);
      $img_max = stripslashes($results[0]['img_max']);
      $pos = $results[0]['pos'];
      $old_pos = $pos;
      $old_img_min = $img_min;
      $old_img_max = $img_max;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтрация данных
    $title      = correct_input($_POST['title']);
    $text      = correct_input($_POST['text']);
    $pos       = intval($_POST['pos']);

    if(empty($pos) || $pos < 1)
      $errors[] = $l_blockeditor[68];
    if(empty($title))
      //$errors[] = "Заполните, пожалуйста, поле <b>название</b>.";
      $title = $pos;

    $old_pos       = intval($_POST['old_pos']);
    $old_img_max = $_POST['old_img_max'];
    $old_img_min = $_POST['old_img_min'];

    //перезаписываем уменьшенную. копию изображения
    if(empty($errors))
    {
	     //$dir = "img/command/";
      if(!empty($_FILES['img_min']['name']))
      {
        $arr = form_image_copy($ed_path_to_img, 'img_min', $old_img_min);
        if(!empty($arr['error']))
          $errors[] = $arr['error'];
        else
          $img_min = $arr['new_img_name'];
      } else $img_min = $old_img_min;

    }

    //перезаписываем увеличенную. копию изображения
    if(empty($errors))
    {
	     //$dir = "img/command/";
      if(!empty($_FILES['img_max']['name']))
      {
        $arr = form_image_copy($ed_path_to_img, 'img_max', $old_img_max, 512000);
        if(!empty($arr['error']))
          $errors[] = $arr['error'];
        else
          $img_max = $arr['new_img_name'];
      } else $img_max = $old_img_max;

    }

    //калибруем позицию остальных изображений в блоке
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_images
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}
                         AND id_block = {$id_block}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_images
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}
                         AND id_block = {$id_block}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    if(empty($errors))
    {
      //обновляем базу данных
      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_images
                  SET title      = '{$title}',
                      text       = '{$text}',
                      img_min    = '{$img_min}',
                      img_max    = '{$img_max}',
                      pos        = {$pos}
                WHERE id_img = {$id_img} ";

      db_update($query);

      //получаем html-код всей страницы
      $page = ed_process_data($ed_tbl_pref, $ed_pg);

      //пересохраняем страницу
      save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $page, 'w');

      //переходим в список изображений блока
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$ed_url}&ed_opt=blocks_images_list&pg={$ed_pg}&id_block={$id_block}'></HEAD></HTML>";
      exit;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_blockeditor[67]}</h1>";

  //подключаем форму
  include("{$ed_path_to_editor}_images_edit.inc");

  //ссылка назад
  print "<p><a class='Mustgreen' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'>{$l_blockeditor[71]}</a></p>";

?>