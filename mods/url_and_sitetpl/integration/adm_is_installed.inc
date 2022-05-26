<?php
  //////////////////////////////////////////////////////////////////////////////
  // Проверяет инсталлирован ли модуль
  //////////////////////////////////////////////////////////////////////////////

  $query = "SHOW TABLES";

  $result = mysql_query($query);

  while ($row = mysql_fetch_row($result)) {
    if($row[0] == "{$gl_db_prefix}url_and_sitetpl")
      $installed = true;
  }
?>