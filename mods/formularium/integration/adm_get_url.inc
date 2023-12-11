<?php
  //////////////////////////////////////////////////////////////////////////////
  // Formularium (universal form constructor)
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Коннектор, выводит список url-адресов модуля
  //////////////////////////////////////////////////////////////////////////////


  print "<h1>{$l_forms[1]}</h1>";
  print "<h2>{$l_forms[2]}</h2>";
  print "<p>";

    print "<b>{$l_forms[3]}</b><br>";
    print "<br>";
    print "<a href='index.php?mod=forms_list' target='_blank'>index.php?mod=forms_list</a><br>";
    print "<br>";

    print "<b>{$l_forms[4]}</b><br>";
    print "<br>";
    print "<a href='{$gl_site}index.php?mod=forms_list' target='_blank'>{$gl_site}index.php?mod=forms_list</a><br>";
    print "<br>";

  print "</p>";

  //навигационная панель
  print "<p><a href='index.php?adm=mods_list'>{$l_mods[6]}</a></p>";
  print "<p><a href='index.php?adm=main'>{$l_adm_gen[1]}</a></p>";


?>