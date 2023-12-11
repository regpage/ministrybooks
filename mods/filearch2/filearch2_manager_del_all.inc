<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Файловый менеджер, удаление группы файлов
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $state    = intval($_GET['state']);
  if(empty($state))
    $state    = intval($_POST['state']);

  $id_cat     = intval($_GET['id_cat']);
  if(empty($id_cat))
    $id_cat     = intval($_POST['id_cat']);

  $to_del = $_POST['items'];

  //выбираем параметры категории
  $path      = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно с подтверждением удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST['del_all']))
  {
    if(is_array($to_del))
    {
    	 print "<h1>{$l_filearch2[77]}</h1>";
	     print "<form name='del_form' action='' method='post'>";
	     print "<br /><br / ><br / ><br / ><br />";
	     print "<div align='center'><input type='submit' name='del_all' value='{$l_gen[20]}'>&nbsp;<input type='button' name='back' value='{$l_gen[21]}' onClick=\"location.href='?mod=filearch2_manager_list&amp;state=1&amp;id_cat={$id_cat}'\"></div>";

      foreach($to_del as $key => $file)
      {
        print "<input type='hidden' name='items[$key]' value='$file'>";
      }
      print "<input type='hidden' name='mod' value='filearch2_manager_del_all'>";
      print "<input type='hidden' name='id_cat' value='{$id_cat}'>";
      print "</form>";
    }
    else
    {
      print "<h3>{$l_filearch2[78]}</h3>";
      print "<p>{$l_filearch2[79]}<br><a class='chap' href='?mod=filearch2_manager_list&amp;id_cat={$id_cat}'>{$l_filearch2[80]}</a></p>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //удаляем файлы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['del_all']))
  {

    foreach($to_del as $key => $file)
    {
	      $file_to_del = "{$path}{$file}";
       if(file_exists($file_to_del) && !is_dir($file_to_del))
         unlink($file_to_del);
    }

    //переходим в список файлов
	   echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=filearch2_manager_list&amp;id_cat={$id_cat}'></HEAD></HTML>";
	   exit;
  }


  print "<br />";
  print "<br />";


?>