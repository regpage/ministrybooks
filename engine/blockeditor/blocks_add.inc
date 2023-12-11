<?php

  //////////////////////////////////////////////////////////////////////////////
  //Модуль добавляет блок в текст страницы.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициалзиация переменных
  //////////////////////////////////////////////////////////////////////////////

  $block_gen_type = $_GET['block_gen_type'];
  if(empty($block_gen_type))
    $block_gen_type = $_POST['block_gen_type'];



  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //инициализация и фильтрация значений переменных
    $block_type     = $_POST['block_type'];
    $block_gen_type = $_POST['block_gen_type'];
    $nl2br = $_POST['nl2br'];

    $pos            = intval($_POST['pos']);
    if($pos < 1 )
      $errors[] = $l_blockeditor[46];

    if($nl2br != 'yes') $nl2br = 'no';

    //текстовый блок
    if($block_gen_type == 'text')
    {
      $text = $_POST['text'];

      $text = correct_input($text);
      if(empty($text))
        $errors[] = $l_blockeditor[47];

      $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET id_block = NULL,
                       type     = '{$block_type}',
                       gen_type     = '{$block_gen_type}',
                       content      = '{$text}',
                       params = '',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}";
    }

    //блок списка
    if($block_gen_type == 'list')
    {
      $l_name = $_POST['l_name'];

      $text = $_POST['text'];
      $text = correct_input($text);
      $l_name = correct_input($l_name);
      $params['l_name'] = $l_name;
      $params = serialize($params);

      $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET id_block = NULL,
                       type     = '{$block_type}',
                       gen_type     = '{$block_gen_type}',
                       content      = '{$text}',
                       params = '{$params}',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}";
    }

    //таблица
    if($block_gen_type == 'table')
    {
      $t_name = $_POST['t_name'];

      $text = $_POST['text'];
      $text = correct_input($text);
      preg_match("#<table.+?<\/table>#ims", $text, $matches);
      $text = $matches[0];
      $t_name = correct_input($t_name);
      $params['t_name'] = $t_name;
      $params = serialize($params);

      $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET id_block = NULL,
                       type     = '{$block_type}',
                       gen_type     = '{$block_gen_type}',
                       content      = '{$text}',
                       params = '{$params}',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}";
    }

    //ряд изображений
    if($block_gen_type == 'images')
    {
      $i_name = correct_input($_POST['i_name']);
      $in_row = intval($_POST['in_row']);

      $params['in_row'] = $in_row;
      $params = serialize($params);

      $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET id_block = NULL,
                       type     = '{$block_type}',
                       gen_type     = '{$block_gen_type}',
                       content      = '{$i_name}',
                       params = '{$params}',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}";
    }

    //файловый блок
    if($block_gen_type == 'file')
    {
      $f_name = correct_input($_POST['f_name']);

      //загрузка файла
      if(empty($errors))
    	 {
	       //$dir = "img/command/";
	       if(!empty($_FILES['file']['name']))
	       {
	         $arr = form_file_copy($ed_path_to_file, 'file', $old_file_name = '');
	         if(!empty($arr['error']))
	           $errors[] = $arr['error'];
	         else
	           $file = $arr['new_file_name'];
	       } else $errors[] = $l_blockeditor[48];
	     }

      //формируем запрос на добавление блока в бд
      if(empty($errors))
    	 {
        $params['file'] = $file;
        $params = serialize($params);

        $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET id_block = NULL,
                       type     = 'file',
                       gen_type     = 'file',
                       content      = '{$f_name}',
                       params = '{$params}',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}";
      }
    }

    //новая страница
    if($block_gen_type == 'newpage')
    {

      $query = "INSERT INTO {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET id_block = NULL,
                       type     = 'newpage',
                       gen_type     = 'newpage',
                       content      = 'newpage',
                       params = '',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}";
    }

    //обновляем бд
    if(empty($errors))
    {
      //калибруем позицию остальных блоков
      $query_pos = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                       SET pos = pos + 1
                      WHERE pos >= {$pos}
                        AND id_pg = {$ed_pg}";
      db_update($query_pos);

      //вставляем блок
      db_insert($query);

      //получаем html-код всей страницы
      $page = ed_process_data($ed_tbl_pref, $ed_pg);

      //пересохраняем страницу
      save_in_file("{$ed_path_to_file}{$ed_pg}.inc", $page, 'w');

      //переходим в список блоков
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'></HEAD></HTML>";
      exit;

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //выбираем предполагаемую позицию блока
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
               WHERE id_pg = {$ed_pg}";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //заголовок
  print "<h3>{$l_blockeditor[50]}</h3>";

  //подключаем форму
  include("{$ed_path_to_editor}_block_edit.inc");

  //ссылка "назад"
  //print "<p><a class='Mustgreen' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'>{$l_blockeditor[71]}</a></p>";
?>