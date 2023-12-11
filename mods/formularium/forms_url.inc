<?php
  //////////////////////////////////////////////////////////////////////////////
  //Страница, где дается url-адрес страницы с формой $id_form
  //////////////////////////////////////////////////////////////////////////////


  //инициализация переменных
  $id_form = intval($_GET['id_form']);

  //выбираем название формы
  $query = "SELECT title FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
  $f_title = stripslashes(db_select_one($query));

  //html-код страницы
  print "<h1>{$l_forms[118]} {$f_title}</h1>";
  print "<br />";
  print "<p><b>{$l_forms[119]}:</a></b> <a href='index.cfm?mod=forms_get_form&id_form={$id_form}'>index.cfm?mod=forms_get_form&id_form={$id_form}</a></p>";
  print "<br />";
  print "<p><b>{$l_forms[120]}:</a></b> <a href='{$gl_site}index.cfm?mod=forms_get_form&id_form={$id_form}'>{$gl_site}index.cfm?mod=forms_get_form&id_form={$id_form}</a></p>";
  print "<br />";

  //ссылка "назад"
  print "<p><a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[121]}</a></p>";
?>