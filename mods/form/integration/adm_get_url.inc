<?php
  //////////////////////////////////////////////////////////////////////////////
  //Справочная страница url-адресов модуля
  //////////////////////////////////////////////////////////////////////////////

  print "<h1>{$l_form[1]}</h1>";

  print "<p>";

    print "<b>{$l_form[2]}</b><br>";
    print "<br>";
    print "<a href='index.php?mod=form'>index.php?mod=form</a><br>";
    print "<br>";

    print "<b>{$l_form[3]}</b><br>";
    print "<br>";
    print "<a href='{$gl_site}index.php?mod=form'>{$gl_site}index.php?mod=form</a><br>";
    print "<br>";

  print "</p>";

  //навигация
  print "<p><a href='index.php?adm=mods_list'>{$l_mods[6]}</a></p>";
  print "<p><a href='index.php?adm=main'>{$l_adm_gen[1]}</a></p>";


?>