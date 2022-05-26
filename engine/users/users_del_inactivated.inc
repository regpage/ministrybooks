<?php
  //////////////////////////////////////////////////////////////////////////////
  // Удаляет неактивированных пользователей
  //////////////////////////////////////////////////////////////////////////////

  db_delete("DELETE FROM {$gl_db_prefix}users WHERE activated = 'no' AND reg_date < NOW() - INTERVAL 24 HOUR");

  echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=users_list'></HEAD></HTML>";
  exit;
?>