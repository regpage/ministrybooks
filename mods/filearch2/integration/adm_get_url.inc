<?php

  //////////////////////////////////////////////////////////////////////////////
  // оннектор, выводит список url-адресов модул€
  //////////////////////////////////////////////////////////////////////////////

  print "<h1>{$l_filearch2[1]}</h1>";
  print "<h2>{$l_filearch2[2]}</h2>";
  print "<p>";
    print "<b>{$l_filearch2[3]}</b><br>";
    print "<br>";
    print "<a href='index.cfm?mod=filearch2_cats_list' target='_blank'>index.cfm?mod=filearch2_cats_list</a><br>";
    print "<br>";
      print "<b>{$l_filearch2[4]}</b><br>";
    print "<br>";
    print "<a href='{$gl_site}index.cfm?mod=filearch2_cats_list' target='_blank'>{$gl_site}index.cfm?mod=filearch2_cats_list</a><br>";
    print "<br>";
  print "</p>";



  print "<p><a href='index.cfm?adm=mods_list'>{$l_mods[6]}</a></p>";
  print "<p><a href='index.cfm?adm=main'>{$l_adm_gen[1]}</a></p>";


?>