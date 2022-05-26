<?php

  //////////////////////////////////////////////////////////////////////////////
  // Удаляет поле $id_field формы $id_form
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_field = intval($_GET['id_field']);
  $id_form  = intval($_GET['id_form']);
  $page     = intval($_GET['page']);
  $state    = intval($_GET['state']);


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно подтверждение удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_forms[139]}</h1><br><br><br><br><div align='center'><a href='index.cfm?mod=forms_fields_del&id_form={$id_form}&id_field={$id_field}&state=1&page={$page}'>{$l_gen[20]}</a> <a href='index.cfm?mod=forms_fields_list&id_form={$id_form}&id_field={$id_field}&page={$page}'>{$l_gen[21]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //удаляем поле
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    //выбираем параметры удаляемого поля
    $query   = "SELECT *
                FROM {$gl_db_prefix}forms_fields
               WHERE id_field = {$id_field}";
    $results = db_select($query);
    $pos     = $results[0]['pos'];
    $page    = $results[0]['page'];
    $type    = $results[0]['type'];
    $field_name     = $results[0]['field_name'];

    //удалеям поле
    $query = "DELETE FROM {$gl_db_prefix}forms_fields
               WHERE id_field = {$id_field}";
    db_delete($query);

    //калибруем позицию
    $query = "UPDATE {$gl_db_prefix}forms_fields
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_form = {$id_form}
                 AND page = {$page}";
    db_update($query);

    //переходим к редактированию шаблона сообщения
    if($type != 'groupe_title')
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_messtpl&context=del&field_name={$field_name}&id_form={$id_form}&page={$page}'></HEAD></HTML>";
    //переходим в список полей текущей формы
    else
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_fields_list&id_form={$id_form}&id_field={$id_field}&page={$page}'></HEAD></HTML>";
    exit;

  }





?>