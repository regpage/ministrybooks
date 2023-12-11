<?php
  //////////////////////////////////////////////////////////////////////////////
  //  онструктор меню
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ћодуль выводит список пунктов меню id_menu
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализаци€ переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_menu = intval($_GET['id_menu']);
  $id_item_prec = intval($_GET['id_item_prec']);

  //название меню
  $query = "SELECT title
              FROM {$gl_db_prefix}menu
             WHERE id_menu = {$id_menu}";
  $m_title = db_select_one($query);

  //выводим заголовок
  print "<h1>{$m_title} :: {$l_menu[24]}</h1>";

  //навигаци€ в виде хлебной крошки
  $tmp_id_item_prec = $id_item_prec ;
  while($tmp_id_item_prec != 0)
  {
    $query = "SELECT caption, id_item, id_item_prec
              FROM {$gl_db_prefix}menu_items
              WHERE id_item = {$tmp_id_item_prec}";
    $res = mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res)
    {
      print "<p>{$l_err[0]}</p>";
    }
    else
    {
      $arr = mysqli_fetch_assoc($res);
      $caption = stripslashes($arr['caption']);
      $tmp_id_item_prec = $arr['id_item_prec'];

      $id_item = $arr['id_item'];
      if($id_item != $id_item_prec)
        $navig = "<a class='Mustgreen' href='?adm=menu_items_list&id_item_prec={$id_item}&id_menu={$id_menu}'>{$caption}</a> / ".$navig;
      else
        $navig = "{$caption} / ".$navig;
    }
  }
  if($id_item_prec != 0)
    $navig = "<a class='Mustdarkred' href='?adm=menu_items_list&id_menu={$id_menu}&id_item_prec=0'>{$m_title}</a> / ".$navig;
  else
    $navig = "{$m_title} / ".$navig;
  $navig = "<a class='Mustdarkred' href='?adm=menu_list'>{$l_menu[25]}</a> / ".$navig;

  $navig = "<p>{$navig}</p>";

  //ссылка ƒобавить пункт
  print "<br /><p><a class='Mustred' href='?adm=menu_items_add&id_menu={$id_menu}&id_item_prec={$id_item_prec}'>{$l_menu[26]}</a></p>";
  print "<br />";

  //выборка пунктов
  print $navig; print "<br />";

  $query = "SELECT *
              FROM {$gl_db_prefix}menu_items
             WHERE id_item_prec = {$id_item_prec}
               AND id_menu = {$id_menu}
            ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    //шапка таблицы
    print "<table class='SiteTbl' cellspacing='0' cellpadding='0' border='0' >";
    print "<tr>";
      print "<td class='SiteTblTH'>{$l_menu[27]}</td>";
      print "<td class='SiteTblTH'>{$l_menu[28]}</td>";
      print "<td class='SiteTblTH'>{$l_menu[29]}</td>";
    print "</tr>";
    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $caption = stripslashes($results[$i]['caption']);
      $pos   = $results[$i]['pos'];
      $id_item   = $results[$i]['id_item'];
      print "<tr>";
        //позици€
        print "<td class='SiteTblLeft' width='40'>{$pos}</td>";
        //название
        print "<td class='SiteTblLeft' width='300'>{$caption}</td>";
        //опции
        print "<td class='SiteTblLeft' width='130'>";
          //параметры
          print "<a href='?adm=menu_items_edit&id_item_prec={$id_item_prec}&id_menu={$id_menu}&id_item={$id_item}'>{$l_menu[30]}</a><br>";
          //подпункты
          print "<a href='?adm=menu_items_list&id_item_prec={$id_item}&id_menu={$id_menu}'>{$l_menu[31]}&nbsp;&gt;&gt;</a><br>";
          //удалить
          print "<a href='?adm=menu_items_del&id_item_prec={$id_item_prec}&id_menu={$id_menu}&id_item={$id_item}'>{$l_menu[32]}</a><br>";
        print "</td>";
      print "</tr>";
    }
    print "</table>";
  } else print "<p><br />{$l_menu[33]}<br /><br /></p>";



?>