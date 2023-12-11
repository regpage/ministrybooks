<?php
  //////////////////////////////////////////////////////////////////////////////
  //Справочник url-адресов модуля (доступен из списка модулей по ссылке 'url')
  //////////////////////////////////////////////////////////////////////////////


  print "<h1>{$l_ministrybooks[1]}</h1>";
  print "<p>";
    print "<b>{$l_ministrybooks[2]}</b><br>";
    print "<br>";
    print "<a href='index.cfm?mod=books_list' target='_blank'>index.cfm?mod=books_list</a><br>";
    print "<br>";

    print "<b>{$l_ministrybooks[3]}</b><br>";
    print "<br>";
    print "<a href='{$gl_site}index.cfm?mod=books_list' target='_blank'>{$gl_site}index.cfm?mod=books_list</a><br>";
    print "<br>";

  print "</p>";


  print "<p><a href='index.cfm?adm=mods_list'>{$l_mods[6]}</a></p>";
  print "<p><a href='index.cfm?adm=main'>{$l_adm_gen[1]}</a></p>";


?>