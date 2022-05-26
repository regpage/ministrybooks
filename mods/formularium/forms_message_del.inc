<?php

  //////////////////////////////////////////////////////////////////////////////
  //Удаляет сообщения $id_mess формы $id_form
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_mess = intval($_GET['id_mess']);
  $id_form  = intval($_GET['id_form']);
  $part = intval($_GET['part']);
  $state = intval($_GET['state']);


  //////////////////////////////////////////////////////////////////////////////
  //подтверждение удаления, диалоговое окно
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_forms[89]}</h1><br><br><br><br><div align='center'><a href='index.cfm?mod=forms_message_del&id_form={$id_form}&id_mess={$id_mess}&state=1&part={$part}'>{$l_gen[20]}</a> <a href='index.cfm?mod=forms_message_list&id_form={$id_form}&part={$part}'>{$l_gen[21]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //удаляем поле
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {

    $query = "DELETE FROM {$gl_db_prefix}forms_messages
               WHERE id_mess = {$id_mess}";
    db_delete($query);

    //переходим в список сообщений текущей формы
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_message_list&id_form={$id_form}&part={$part}'></HEAD></HTML>";
    exit;

  }





?>