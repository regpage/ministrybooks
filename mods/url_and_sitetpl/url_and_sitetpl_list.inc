<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������ ������� ������ ������������
  //////////////////////////////////////////////////////////////////////////////


  //���������
  print "<h1>{$l_url_and_sitetpl[9]}</h1>";

  //������� ���� ��������
  print "<br /><p>
           <a span class='Mustred' href='index.cfm?mod=url_and_sitetpl_add'>{$l_url_and_sitetpl[10]}</a>
         </p><br />";

  //�������� ������������ �� ��
  $query = "SELECT *
              FROM {$gl_db_prefix}url_and_sitetpl
             ORDER BY pos";
  $results = db_select($query);

  if(is_array($results))
  {
    //����� �������
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>pos</td>";
      print "<td class='SiteTblTH'>{$l_url_and_sitetpl[12]}</td>";
      print "<td class='SiteTblTH'>{$l_url_and_sitetpl[13]}</td>";
    print "</tr>";

    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $id_item  = $results[$i]['id_item'];
      $pos     = $results[$i]['pos'];
      $url   = stripslashes($results[$i]['url']);
      $id_tpl     = $results[$i]['id_tpl'];
      $tpl_title = stripslashes(db_select_one("SELECT title FROM {$gl_db_prefix}sitetpl WHERE id_tpl = {$id_tpl}"));
      if(empty($tpl_title))
        $tpl_title = $l_url_and_sitetpl[3];

      print "<tr>";
          //�������
          print "<td class='SiteTblLeft'>{$pos}</td>";
          //������������
          print "<td class='SiteTblLeft'>{$tpl_title}<br />{$url}</td>";

          //�����
          print "<td class='SiteTblLeft' width='250'>";
            //���������
            print "<a href='index.cfm?mod=url_and_sitetpl_edit&amp;id_item={$id_item}'>{$l_url_and_sitetpl[14]}</a><br>";
            //�������
            print "<a href='index.cfm?mod=url_and_sitetpl_del&amp;id_item={$id_item}'>{$l_url_and_sitetpl[15]}</a><br>";
          print "</td>";
        print "</tr>";
    }
    print "</tr></table>";
                   //�� ��������� �� ������ ������������
  } else print "<p>{$l_url_and_sitetpl[11]}</p>";

?>