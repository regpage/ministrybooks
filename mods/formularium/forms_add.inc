<?php

  //////////////////////////////////////////////////////////////////////////////
  // ƒобавл€ение новой формы
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтраци€ данных формы
    $title       = correct_input($_POST['title']);
	   $pos         = intval($_POST['pos']);
    $encoding    = correct_input($_POST['encoding']);
    $email_from  = correct_input($_POST['email_from']);
    $subject     = correct_input($_POST['subject']);
    $sended_mess = correct_input($_POST['sended_mess']);
    $sended_den  = correct_input($_POST['sended_den']);

    if($pos < 1)
      $errors[] = $l_forms[68];
    if(empty($title))
      $errors[] = $l_forms[69];
    if(empty($subject))
      $errors[] = $l_forms[70];

    //обновл€ем базу данных
    if(empty($errors))
    {
      //калибруем позицию
      $query = "UPDATE {$gl_db_prefix}forms
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}";
      db_update($query);

      $query = "INSERT INTO {$gl_db_prefix}forms
                    SET id_form = NULL,
                        title         = '{$title}',
                        encoding      = '{$encoding}',
                        subject       = '{$subject}',
                        sended_mess   = '{$sended_mess}',
                        sended_den    = '{$sended_den}',
                        email_from    = '{$email_from}',
                        pos           = {$pos}";
      db_insert($query);

      //вставл€ем пустой шаблон сообщени€ созданной формы
      $id_form = db_insert_id();
      $query = "INSERT INTO {$gl_db_prefix}forms_messtpl VALUES (NULL, '', {$id_form})";
      db_insert($query);

      //переходим в список форм
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_list'></HEAD></HTML>";
      exit;

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //‘орма
  //////////////////////////////////////////////////////////////////////////////

  //выбираем предполагаемую позицию новой формы
  if(empty($pos))
  {
    $query = "SELECT MAX(pos)
               FROM {$gl_db_prefix}forms";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;
  }

  //заголовок
  print "<h1>{$l_forms[71]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine_root}mods/formularium/_forms_edit.inc");

  //ссылка назад
  print "<p><a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[73]}</a></p>";
?>