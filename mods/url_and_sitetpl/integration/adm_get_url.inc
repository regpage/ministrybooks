<?php
  //////////////////////////////////////////////////////////////////////////////
  //Справочник url-адресов модуля (доступен из списка модулей по ссылке 'url')
  //////////////////////////////////////////////////////////////////////////////


  print "<h1>{$l_url_and_sitetpl[1]}</h1>";
  print "<p>";

    print "<b>{$l_url_and_sitetpl[2]}</b><br>";
    print "<br>";
    print "<a href='index.cfm?mod=url_and_sitetpl_list' target='_blank'>index.cfm?mod=url_and_sitetpl_list</a><br>";
    print "<br>";

    print "<b>{$l_url_and_sitetpl[3]}</b><br>";
    print "<br>";
    print "<a href='{$gl_site}index.cfm?mod=url_and_sitetpl_list' target='_blank'>{$gl_site}index.cfm?mod=url_and_sitetpl_list</a><br>";
    print "<br>";

  print "</p>";


  print "<p><a href='index.php?adm=mods_list'>{$l_mods[6]}</a></p>";
  print "<p><a href='index.php?adm=main'>{$l_adm_gen[1]}</a></p>";


?>