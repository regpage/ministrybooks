<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� �������� �������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ����� ������ � �������
  //////////////////////////////////////////////////////////////////////////////


  //���������
  print "<h1>{$l_sites[1]}</h1>";

  //����� "�������� ����"
  print "<br><p><a class='Mustred' href='?adm=sites_add'>{$l_sites[2]}</a></p><br>";

  //������� ������ ������
  $dir = opendir("{$gl_path_to_engine_root}config/sites");
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..')
      $sites[] = $file;
  }
  closedir($dir);

  if(is_array($sites))
  {
    //����� �������
    print "<table width='650' class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>�</td>";
      print "<td class='SiteTblTH'>{$l_sites[3]}</td>";
      print "<td class='SiteTblTH' width='200'>{$l_sites[4]}</td>";
    print "</tr>";

    $cnt = count($sites);
    for($i = 0; $i < $cnt; $i++)
    {
      $site = str_replace('.inc', '', $sites[$i]);
      print "<tr>";
      	 //���������� �����
      	 print "<td class='SiteTblLeft'>".($i + 1)."</td>";
	       //����. �����
	       print "<td class='SiteTblLeft'>{$site}</td>";
        //�����
        print "<td class='SiteTblLeft'>";
          //���������
          print "<a href='?adm=sites_edit&site={$sites[$i]}'>{$l_sites[5]}</a><br>";
          //�������
          print "<a href='?adm=sites_del&site={$sites[$i]}'>{$l_sites[6]}</a>";
        print "</td>";
	     print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_sites[7]}</p>";

  //����
  print "<br><p>{$l_sites[8]}</p>";

?>