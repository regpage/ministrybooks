<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль 
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
//////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);

  //заголовок
  if(empty($id_part_prec))
  {
    print "<h1>{$l_parts[1]}</h1>";
  }
  else
  {
    $query = "SELECT title
                FROM {$gl_db_prefix}parts
               WHERE id_part = {$id_part_prec}";
    $title = stripslashes(db_select_one($query));

    print "<h1>{$l_parts[2]} :: {$title}</h1>";
  }

  //навигация в виде хлебной крошки
  if(!empty($id_part_prec))
  {
    $tmp_id_part_prec = $id_part_prec;

    while($tmp_id_part_prec != 0)
    {
      $query = "SELECT title, id_part, id_part_prec
                FROM {$gl_db_prefix}parts
                WHERE id_part = {$tmp_id_part_prec}";
      $results = db_select($query);
      if(!empty($results))
      {
        $tmp_title = stripslashes($results[0]['title']);
        $tmp_id_part = $results[0]['id_part'];
        $tmp_id_part_prec = $results[0]['id_part_prec'];

        if($tmp_id_part != $id_part_prec)
        {
          $navig = "<a class='Mustdarkred' href='?adm=parts_list&id_part_prec={$tmp_id_part}'>{$tmp_title}</a> / ".$navig;
        }
      }
    }
    $navig = "<a class='Mustdarkred' href='?adm=parts_list'>{$l_parts[24]}</a> / ".$navig;
    $navig = $navig."$title ";
    if(!empty($navig))
    {
      $navig = "<p>{$navig}</p>";
    }

  }

  if(!empty($id_part_prec))
    print $navig;

  print "<br />";

  //Меню Добавить подкаталог | Найти страницу
  if(empty($id_part_prec))
  {
    print "<p><a class='Mustred' href='?adm=parts_add&id_part_prec={$id_part_prec}'>{$l_parts[4]}</a>&nbsp;|&nbsp;<a class='Mustred' href='?adm=parts_pages_search'>{$l_parts[3]}</a></p>";
  }
  else
  {
    //заголовок "Подразделы"
    print "<h2>{$l_parts[73]}</h2>";

    print "<p><a class='Mustred' href='?adm=parts_add&id_part_prec={$id_part_prec}'>{$l_parts[5]}</a>&nbsp;|&nbsp;<a class='Mustred' href='?adm=parts_pages_search'>{$l_parts[3]}</a></p>";
  }
  print "<br />";

  //выводим список (под)разделов
  $query = "SELECT *
              FROM {$gl_db_prefix}parts
             WHERE id_part_prec = {$id_part_prec}
            ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    //шапка таблицы
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0' >";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>{$l_parts[6]}</td>";
        //print "<td class='SiteTblTH'>{$l_parts[88]}</td>";
        print "<td class='SiteTblTH'>{$l_parts[7]}</td>";
        print "<td class='SiteTblTH' width='200'>{$l_parts[8]}</td>";
    print "</tr>";

    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $title = stripslashes($results[$i]['title']);
      $pos   = $results[$i]['pos'];
      $in_site_map = $results[$i]['in_site_map'];
      $id_part = $results[$i]['id_part'];

      print "<tr>";
        //позиция
        print "<td class='SiteTblCenter' width='40'>{$pos}</td>";
        //название раздела
        print "<td class='SiteTblLeft' width='300'>{$title}</td>";
        //опции
        print "<td class='SiteTblLeft' width='130'>";
          //подразделы
          print "<a href='?adm=parts_list&id_part_prec={$id_part}'>{$l_parts[9]}&nbsp;&gt;&gt;</a><br>";
          //параметры
          print "<a href='?adm=parts_edit&id_part_prec={$id_part_prec}&id_part={$id_part}'>{$l_parts[10]}</a><br>";
          //права доступа
 if($_SESSION["{$gl_site_name}_gl_us_name"]== 'admin')
          print "<a href='?adm=parts_perm&id_part_prec={$id_part_prec}&id_part={$id_part}'>{$l_parts[11]}</a><br>";

else
{
print "";
}
          //перенести
          print "<a href='?adm=parts_move&id_part_prec={$id_part_prec}&id_part={$id_part}'>{$l_parts[12]}</a><br>";
          //удалить
          print "<a href='?adm=parts_del&id_part_prec={$id_part_prec}&id_part={$id_part}'>{$l_parts[13]}</a><br>";
          
        print "</td>";
      print "</tr>";
    }
    print "</table>";
  }

  if(!empty($id_part_prec))
  {
    //Страницы, заголовок
    print "<h2>{$l_parts[15]}</h2>";

    //меню "Добавить страницу"
    print "<p>";
      print "<a class='Mustred' href='?adm=parts_items_pages_add&id_part={$id_part}&id_part_prec={$id_part_prec}'>{$l_parts[14]}</a>&nbsp;|&nbsp;";
 //меню "Добавить или редактировать авторов"      
print "<a class='Mustred' href='?adm=author_list&id_part_prec={$id_part_prec}'>{$l_parts[81]}</a>";
    print "</p><br />";

    //выводим страницы подкатегории
    $query = "SELECT *
                FROM {$gl_db_prefix}parts_items
               WHERE id_part = {$id_part_prec}
               ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
      //шапка таблицы
      print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        print "<td class='SiteTblTHPage' width='20'>{$l_parts[16]}</td>";
        print "<td class='SiteTblTHPage'>{$l_parts[17]}</td>";
        print "<td class='SiteTblTHPage' width='200'>{$l_parts[18]}</td>";
      print "</tr>";

      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $id_item  = $results[$i]['id_item'];
        $id_parts  = $results[$i]['id_part'];
        $type     = $results[$i]['i_type'];
        $pos      = $results[$i]['pos'];
        $title    = stripslashes($results[$i]['title']);
        $mod_name = $results[$i]['mod_name'];
        $params   = $results[$i]['params'];
        $params   = unserialize(stripslashes($params));

        print "<tr>";
          //позиция
          print "<td class='SiteTblCenter' width='40'>{$pos}</td>";
          //заголовок
          print "<td class='SiteTblLeft' width='300'>{$title}</td>";
          //опции
          print "<td class='SiteTblLeft' width='130'>";
            //текст
            print "<a href='?adm=parts_items_pages_text&ed_opt=blocks_list&pg={$id_item}&id_part={$id_part_prec}&id_item={$id_item}'>{$l_parts[19]}</a><br>";
//По главам
            print "<a href='?adm=parts_items_pages_chapter&ed_opt=blocks_list_chupters&pg={$id_item}&id_part={$id_part_prec}&id_item={$id_item}'>{$l_parts[86]}</a><br>";
            //параметры
            print "<a href='?adm=parts_items_pages_edit&id_part_prec={$id_part_prec}&id_item={$id_item}'>{$l_parts[20]}</a><br>";
            //url-адрес
            if($type == 'page')
              print "<a href='?adm=parts_items_pages_url&id_part_prec={$id_part_prec}&id_item={$id_item}'>{$l_parts[21]}</a><br>";
            //переместить
            print "<a href='?adm=parts_items_pages_move&id_part_prec={$id_part_prec}&id_item={$id_item}&id_part={$id_part}'>{$l_parts[22]}</a><br>";
            //удалить
            print "<a href='?adm=parts_items_pages_del&id_part_prec={$id_part_prec}&id_item={$id_item}'>{$l_parts[23]}</a><br>";
          print "</td>";
        print "</tr>";
      }
      print "</table>";
    }
  }

  print "<br /><br /><br />";
?>