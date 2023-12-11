<?php
  //////////////////////////////////////////////////////////////////////////////
  //Модуль проверки доменного имени (доступен из списка модулей по ссылке 'url')
  //////////////////////////////////////////////////////////////////////////////


  print "<h1>{$l_whois[1]}</h1>";
  print "<p>";

    print "<b>{$l_whois[2]}</b><br>";
    print "<br>";
    print "<a href='index.php?mod=whois' target='_blank'>index.php?mod=whois</a><br>";
    print "<br>";

    print "<b>{$l_whois[3]}</b><br>";
    print "<br>";
    print "<a href='{$gl_site}index.php?mod=whois' target='_blank'>{$gl_site}index.php?mod=whois</a><br>";
    print "<br>";

  print "</p>";


  print "<p><a href='index.php?adm=mods_list'>{$l_mods[6]}</a></p>";
  print "<p><a href='index.php?adm=main'>{$l_adm_gen[1]}</a></p>";
?>