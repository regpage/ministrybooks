<?php

  //////////////////////////////////////////////////////////////////////////////
  //Модуль выводит сообщение об успешной аутентификации
  //////////////////////////////////////////////////////////////////////////////


  //выводим начальные теги html
  //подключаем языковой файл
  include("{$gl_path_to_root}langfiles/pub_auth.inc");

    if($group == 'admin')
    {
      //print "Здравствуйте, {$name}, авторизация прошла успешно. Ваш статус администратор. <br><a href='index.cfm'>Перейти на сайт</a><br><a href='index.cfm?adm=main'>Перейти в систему администрирования</a>";
      $tmp = $l_auth[8];
      $tmp = str_replace("{name}", $name, $tmp);
      print $tmp;
    }
    if($group == 'user')
    {
      //print "Здравствуйте, {$name}, авторизация прошла успешно. <a href='index.cfm'>Перейти на сайт</a>";
      $tmp = $l_auth[9];
      $tmp = str_replace("{name}", $name, $tmp);
      print $tmp;
    }
    if($group == 'editors')
    {
      //print "Здравствуйте, {$name}, авторизация прошла успешно. Теперь вы можете работать с сайтом как редактор. <a href='index.cfm'>Перейти на сайт</a>";
      $tmp = $l_auth[10];
      $tmp = str_replace("{name}", $name, $tmp);
      print $tmp;
    }

  print "<p id='backto'><a href='http://ministrybooks.ru/' title='Назад на сайт Публикации онлайн'>&laquo; Назад на сайт Публикации онлайн</a></p>";

    print "</body></html>";

    exit;


?>