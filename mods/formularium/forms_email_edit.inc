<?php
  //////////////////////////////////////////////////////////////////////////////
  // Изменяет адрес $id_email
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_form = intval($_GET['id_form']);
  if(empty($id_form))
    $id_form = intval($_POST['id_form']);

  $id_email = intval($_GET['id_email']);
  if(empty($id_email))
    $id_email = intval($_POST['id_email']);


  //////////////////////////////////////////////////////////////////////////////
  //выбираем данные для заполнения полей формы
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT email FROM {$gl_db_prefix}forms_emails_to WHERE id_email = {$id_email}";
    $email = stripslashes(db_select_one($query));
  }


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтрация данных формы
    $email       = correct_input($_POST['email']);

    //обновляем базу данных
    if(empty($errors))
    {

      $query = "UPDATE {$gl_db_prefix}forms_emails_to
                    SET email   = '{$email}'
                 WHERE id_email = {$id_email}";
      db_insert($query);

      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_email_list&id_form={$id_form}'></HEAD></HTML>";
      exit;

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_forms[3]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine_root}mods/formularium/_email_edit.inc");

  //ссылка назад
  print "<p><a class='Mustgreen' href='index.cfm?mod=forms_email_list&id_form={$id_form}&page={$page}'>{$l_forms[4]}</a></p>";
?>