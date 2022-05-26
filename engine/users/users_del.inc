<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Моудль удаляет одного пользователя
  //////////////////////////////////////////////////////////////////////////////



  $id_user = intval($_GET['id_user']);
  $state    = intval($_GET['state']);
  $part     = intval($_GET['part']);
  $sort = correct_input($_GET['sort']);
  $mode = correct_input($_GET['mode']);

  if(empty($state))
  {
    print "<h1>{$l_user[36]}</h1><br><br><br><br><br><br><br><div align='center'><a href='{$gl_site}?adm=users_del&id_user={$id_user}&state=1&part={$part}&sort={$sort}&mode={$mode}'>{$l_adm_gen[5]}</a> <a href='{$gl_site}?adm=users_list&part={$part}&sort={$sort}&mode={$mode}'>{$l_adm_gen[6]}</a></div>";
  }

  if($state == 1)
  {

    //удаляем элемент
    $query = "DELETE FROM {$gl_db_prefix}users
               WHERE id_user = {$id_user}";
    db_delete($query);

    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=users_list'></HEAD></HTML>";
    exit;
  }




?>