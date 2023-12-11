<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль добавляет изображение в блок.
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_block = intval($_GET['id_block']);
  if(empty($id_block))
    $id_block = intval($_POST['id_block']);


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтрация данных
    $title      = correct_input($_POST['title']);
    $text       = correct_input($_POST['text']);
    $pos        = intval($_POST['pos']);

    if(empty($pos) || $pos < 1)
      $errors[] = $l_blockeditor[68] ;
    if(empty($title))
      //$errors[] = "Заполните, пожалуйста, поле <b>название</b>.";
      $title = $pos;

    //копируем уменьш. копию изображения
    if(empty($errors))
    {
	     //$dir = "img/command/";
      if(!empty($_FILES['img_min']['name']))
      {
        $arr = form_image_copy($ed_path_to_img, 'img_min', $old_img_name = '');
        if(!empty($arr['error']))
          $errors[] = $arr['error'];
        else
          $img_min = $arr['new_img_name'];
      } else $errors[] = $l_blockeditor[69] ;

    }

    //копируем увеличенную копию изображения
    if(empty($errors))
    {
	     //$dir = "img/command/";
      if(!empty($_FILES['img_max']['name']))
      {
        $arr = form_image_copy($ed_path_to_img, 'img_max', $old_img_name = '', 512000);
        if(!empty($arr['error']))
          $errors[] = $arr['error'];
        else
          $img_max = $arr['new_img_name'];
      } else $img_max = '';

    }

    //удаляем изображения в случае ошибок
    if(!empty($errors))
    {
      if(!empty($img_min))
        if(is_file("{$ed_path_to_img}{$img_min}"))
          unlink("{$ed_path_to_img}{$img_min}");
      if(!empty($img_max))
        if(is_file("{$ed_path_to_img}{$img_max}"))
          unlink("{$ed_path_to_img}{$img_max}");
    }

    if(empty($errors))
    {
      //калибруем позицию остальных изображений в блоке
      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_images
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                      AND id_block = {$id_block}";
      db_update($query);

      //добавляем изображение в блок
      $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_images
                    SET id_img = NULL,
                        title      = '{$title}',
                        text      = '{$text}',
                        img_min    = '{$img_min}',
                        img_max    = '{$img_max}',
                        pos        = {$pos},
                        id_pg      = {$ed_pg},
                        id_block   = {$id_block}";

      db_insert($query);

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
  print "<h1>{$l_blockeditor[66]}</h1>";

  //выбираем предполагаемую позицию изображения
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}{$ed_tbl_pref}_images
               WHERE id_block = {$id_block}";
              // print $query;
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //подключаем форму
  include("{$ed_path_to_editor}_images_edit.inc");

  //ссылка "назад"
  print "<p><a class='Mustgreen' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'>{$l_blockeditor[71]}</a></p>";

?>