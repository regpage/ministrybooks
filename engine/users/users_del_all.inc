<?php
  //////////////////////////////////////////////////////////////////////////////
  // —истема управлени€ пользовател€ми
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ћодуль удал€ет несколько выбранных пользователей
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //»нициализаци€ переменных
  //////////////////////////////////////////////////////////////////////////////

  $state    = intval($_GET['state']);
  if(empty($state))
    $state    = intval($_POST['state']);

 $part     = intval($_GET['part']);
  if(empty($part))
    $part     = intval($_POST['part']);

  $sort = correct_input($_GET['sort']);
  if(empty($sort))
    $sort = correct_input($_POST['sort']);

  $mode = correct_input($_GET['mode']);
  if(empty($mode))
    $mode = correct_input($_POST['mode']);

  $to_del = $_POST['to_del'];


  //////////////////////////////////////////////////////////////////////////////
  //ƒиалоговое окно подтверждени€ удалени€
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST['del_all']))
  {
    if(is_array($to_del))
    {
    	 print "<h1>{$l_user[33]}</h1>";
	     print "<form name='del_form' action='' method='post'>";
	     print "<br><br><br><br><br>";
	     print "<div align='center'><input type='submit' name='del_all' value='{$l_adm_gen[5]}'>&nbsp;<input type='button' name='back' value='{$l_adm_gen[6]}' onClick=\"location.href='?adm=users_list&id_user={$id_user}&state=1&part={$part}&sort={$sort}&mode={$mode}'\"></div>";
      print "<p class='Center'><br><br><b>{$l_user[34]}:</b><br>";
      foreach($to_del as $id_user => $value)
      {
        print "<input type='hidden' name='to_del[$id_user]' value='$value'>";
        $query = "SELECT name FROM {$gl_db_prefix}users WHERE id_user = {$id_user}";
        $us_name = stripslashes(db_select_one($query));
        print "{$us_name}<br>";
      }
      print "</p>";
      print "<input type='hidden' name='adm' value='users_del_all'>";
      print "<input type='hidden' name='sort' value='{$sort}'>";
      print "<input type='hidden' name='mode' value='{$mode}'>";
      print "<input type='hidden' name='part' value='{$part}'>";
      print "</form>";
    }
    //сообщение о том, что ни один пользователь не выбран
    else
    {
      print "<h1>{$l_user[33]}</h1>";
      print "<p>{$l_user[35]}<br><a href='?adm=users_del&id_user={$id_user}&state=1&part={$part}&sort={$sort}&mode={$mode}'>{$l_adm_gen[11]}</a></p>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //”дал€ем выбранных пользователей
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['del_all']))
  {
    foreach($to_del as $id_user => $value)
    {

      $query = "DELETE FROM {$gl_db_prefix}users WHERE id_user = {$id_user}";
      db_delete($query);

    }

    //переходим в список зарегистр. пользователей в админе
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=users_list'></HEAD></HTML>";
    exit;
  }




?>