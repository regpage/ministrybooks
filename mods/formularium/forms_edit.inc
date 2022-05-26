<?php
  //////////////////////////////////////////////////////////////////////////////
  // Изменение параметров формы $id_form
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_form = intval($_GET['id_form']);
  if(empty($id_form))
    $id_form = intval($_POST['id_form']);


  //////////////////////////////////////////////////////////////////////////////
  //выбираем предыдущие значения
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT * FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
    $results = db_select($query);
    if(is_array($results))
    {
      $title       = stripslashes($results[0]['title']);
	     $encoding    = stripslashes($results[0]['encoding']);
	     $email_from  = stripslashes($results[0]['email_from']);
	     $subject     = stripslashes($results[0]['subject']);
	     $sended_mess = stripslashes($results[0]['sended_mess']);
	     $sended_den  = stripslashes($results[0]['sended_den']);
      $pos      = $results[0]['pos'];
      $old_pos  = $pos;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтрация данных формы
    $title       = correct_input($_POST['title']);
	   $pos         = intval($_POST['pos']);
    $old_pos     = intval($_POST['old_pos']);
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

    //калибруем позицию
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}forms
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}forms
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    //обновляем базу данных
    if(empty($errors))
    {
       $query = "UPDATE {$gl_db_prefix}forms
                    SET title         = '{$title}',
                        encoding      = '{$encoding}',
                        subject       = '{$subject}',
                        sended_mess   = '{$sended_mess}',
                        sended_den    = '{$sended_den}',
                        email_from    = '{$email_from}',
                        pos           = {$pos}
                 WHERE id_form = {$id_form} ";
      db_update($query);

      //переходим в список форм
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_list'></HEAD></HTML>";
      exit;

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_forms[72]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine_root}mods/formularium/_forms_edit.inc");

  //ссылка назад
  print "<p><a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[73]}</a></p>";
?>