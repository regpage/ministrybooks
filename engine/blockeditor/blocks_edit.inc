<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль изменяет параметры блока страницы.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $block_gen_type = $_GET['block_gen_type'];
  if(empty($block_gen_type))
    $block_gen_type = $_POST['block_gen_type'];

  $id_block = $_GET['id_block'];
  if(empty($id_block))
    $id_block = $_POST['id_block'];


  //////////////////////////////////////////////////////////////////////////////
  //Выборка текущих значений полей формы
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
               WHERE id_block = {$id_block}";
    $results = db_select($query);
    if(is_array($results))
    {
      $content = stripslashes($results[0]['content']);
      $params  = $results[0]['params'];
      $params  = unserialize($params);
      $block_gen_type = $results[0]['gen_type'];
      $block_type     = $results[0]['type'];
      $pos = $results[0]['pos'];
      $old_pos = $pos;

      if($block_gen_type == 'text')
        $text = $content;

      if($block_gen_type == 'list')
      {
        $l_name = $params['l_name'];
        $text = $content;
      }

      if($block_gen_type == 'table')
      {
        $t_name = $params['t_name'];
        $text = $content;
      }

      if($block_gen_type == 'images')
      {
        $in_row = $params['in_row'];
        $i_name = $content;
      }

      if($block_gen_type == 'file')
      {
        $file = $params['file'];
        $old_file = $file;

        $f_name = $content;
      }
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //инициализация переменных, фильтрация значенийы
    $block_type     = $_POST['block_type'];
    $block_gen_type = $_POST['block_gen_type'];
    $pos            = intval($_POST['pos']);
    $old_pos        = intval($_POST['old_pos']);
    $nl2br          = $_POST['nl2br'];

    if($pos < 1 )
      $errors[] = $l_blockeditor[46];

    if($nl2br != 'yes') $nl2br = 'no';

    //текствовый блок, фильтрация полей
    if($block_gen_type == 'text')
    {
      $text = $_POST['text'];
      $text = correct_input($text);

      if(empty($text))
        $errors[] = $l_blockeditor[47];

     $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET type     = '{$block_type}',
                       content      = '{$text}',
                       params = '',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}
                 WHERE id_block = {$id_block}";
    }

    //список, фильтрация полей
    if($block_gen_type == 'list')
    {
      $l_name = $_POST['l_name'];

      $text = $_POST['text'];
      $text = correct_input($text);
      $l_name = correct_input($l_name);
      $params['l_name'] = $l_name;
      $params = serialize($params);

      if(empty($text))
        $errors[] = $l_blockeditor[47];

      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET type     = '{$block_type}',
                       content      = '{$text}',
                       params = '{$params}',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}
                 WHERE id_block = {$id_block}";
    }

    //изображения, фильтрация полей
    if($block_gen_type == 'images')
    {
      $i_name = $_POST['i_name'];
      $in_row = intval($_POST['in_row']);

      $params['in_row'] = $in_row;
      $params = serialize($params);

      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET type     = '{$block_type}',
                       gen_type     = '{$block_gen_type}',
                       content      = '{$i_name}',
                       params = '{$params}',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}
                WHERE id_block = {$id_block}       ";
    }

    //таблица, фильтрация полей
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

      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET type     = '{$block_type}',
                       gen_type     = '{$block_gen_type}',
                       content      = '{$text}',
                       params = '{$params}',
                       pos    = {$pos},
                       id_pg  = {$ed_pg}
                 WHERE id_block = {$id_block}";
    }

    //файловый блок, фильтрация полей
    if($block_gen_type == 'file')
    {
      $old_file = correct_input($_POST['old_file']);
      $f_name   = correct_input($_POST['f_name']);

      //перезагружаем файл
      if(empty($errors))
    	 {
	       //$dir = "img/command/";
	       if(!empty($_FILES['file']['name']))
	       {
	         $arr = form_file_copy($ed_path_to_file, 'file', $old_file);
	         if(!empty($arr['error']))
	           $errors[] = $arr['error'];
	         else
	           $file = $arr['new_file_name'];
	       } else $file = $old_file;
	     }

      //формируем запрос на обновление базы
      if(empty($errors))
    	 {
        $params['file'] = $file;
        $params = serialize($params);

        $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks SET
                       content      = '{$f_name}',
                       params = '{$params}',
                       pos    = {$pos}
                  WHERE id_block = {$id_block}";
      }
    }

    //новая страница
    if($block_gen_type == 'newpage')
    {
      $query = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                   SET pos    = {$pos}
                WHERE id_block = {$id_block}       ";
    }


    //калибруем позицию
    $results = db_select("SELECT id_block
                            FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
                           WHERE id_block != {$id_block}
                             AND id_pg = {$ed_pg}
                        ORDER BY pos");
    if(is_array($results))
    {
      $cnt = count($results);
      $tmp_pos = 1;

      for($i = 0; $i < $cnt; $i++)
      {
        if($pos == $tmp_pos) $tmp_pos++;
        $tmp_id_block = $results[$i]['id_block'];
        db_update("UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                      SET pos = {$tmp_pos}
                     WHERE id_block = {$tmp_id_block}");
        $tmp_pos++;
      }
    }

    /*if(empty($errors))
    {
      if($old_pos > $pos)
    	 {
	         $query_pos = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
	                          SET pos = pos + 1
	                        WHERE pos >= {$pos}
	                          AND pos < {$old_pos}
	                          AND id_pg = {$ed_pg}";
	     }
	     if($old_pos < $pos)
	     {
	       $query_pos = "UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
	                        AND pos <= {$pos}
	                        AND id_pg = {$ed_pg}";
	     }
	     if(!empty($query_pos))
	     {
	       db_update($query_pos);
	     }
    }*/

    //обновляем блоки
    if(empty($errors))
    {
      //обнвовляем базу
      db_update($query);

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

  //заголовок
  print "<h3>{$l_blockeditor[49]}</h3>";

  //подключаем форму
  include("{$ed_path_to_editor}_block_edit.inc");

  //ссылка "назад"
  print "<p><a class='Mustgreen' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'>{$l_blockeditor[71]}</a></p>";
?>