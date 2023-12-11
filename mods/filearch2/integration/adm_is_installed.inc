<?php
  //////////////////////////////////////////////////////////////////////////////
  //Проверяет инсталлирован ли модуль
  //////////////////////////////////////////////////////////////////////////////


  $query = "SHOW TABLES";

  $result = mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));

  while ($row = mysqli_fetch_row($result)) {
    if($row[0] == "{$gl_db_prefix}filearch2_cats")
      $installed = true;
  }
?>