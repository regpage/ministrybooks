<?php
  //////////////////////////////////////////////////////////////////////////////
  // ����������� ����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ������ ���� �����
  //////////////////////////////////////////////////////////////////////////////


  //���������
  print "<h1>{$l_menu[1]}</h1>";

  //�������� ����, ������
  print "<br /><p><a class='Mustred' href='?adm=menu_add'>$l_menu[2]</a></p><br />";

  //�������� ������
  $query = "SELECT id_menu, title, pos
              FROM {$gl_db_prefix}menu
             ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    //����� �������
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>{$l_menu[3]}</td>";
      print "<td class='SiteTblTH'>{$l_menu[5]}</td>";
      print "<td class='SiteTblTH' width='100'>$l_menu[4]</td>";
      print "<td class='SiteTblTH' width='200'>{$l_menu[6]}</td>";
    print "</tr>";

    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $id_menu = $results[$i]['id_menu'];
      $pos = $results[$i]['pos'];
      $title  = stripslashes($results[$i]['title']);

      print "<tr>";
          //�������
          print "<td class='SiteTblLeft'>{$pos}</td>";
          //��������
          print "<td class='SiteTblLeft'>{$title}</td>";
          //���
          print "<td class='SiteTblLeft'>[MENU={$id_menu}]</td>";
          //�����
          print "<td class='SiteTblLeft'>";
            //������
            print "<a href='?adm=menu_items_list&id_menu={$id_menu}'>{$l_menu[7]}&nbsp;&gt;&gt;</a><br>";
            //���������
            print "<a href='?adm=menu_edit&id_menu={$id_menu}'>{$l_menu[8]}</a><br>";
            //�������
            print "<a href='?adm=menu_del&id_menu={$id_menu}'>{$l_menu[9]}</a><br>";
          print "</td>";
        print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_menu[10]}</p>";

  //����
  print "<h2>{$l_adm_gen[20]}</h2>";
  print "<p>{$l_menu[11]}</p>";

?>