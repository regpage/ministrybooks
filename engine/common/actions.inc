<?php
  //////////////////////////////////////////////////////////////////////////////
  //Модуль осуществляет обработку дейстий, подключение модуля до вывода информации
  //в окно браузера, подключаемый модуль указывается в $_GET['act']
  //////////////////////////////////////////////////////////////////////////////
  //подключение коннектора pub_actions.inc для всех модулей, где он есть
  
  $path = "{$gl_path_to_engine_root}mods/";
  $dir = opendir($path);
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && is_dir("{$path}{$file}"))
    {
     // print 'g';
    // print "{$path}{$file}/integration/pub_actions.inc<br>" ;
      if(file_exists("{$path}{$file}/integration/pub_actions.inc"))
         include("{$path}{$file}/integration/pub_actions.inc");
    }
  }
  closedir($dir);

  //подключаем модули
  switch($gl_act)
  {
    case 'auth_exit'       : include("{$gl_path_to_engine}auth/auth_exit.inc");          break;
    case 'authentification':  include("{$gl_path_to_engine}auth/auth.inc"); break;
    case 'open_site':  include("{$gl_path_to_engine}admin/open_site.inc"); break;
    case 'lock_site':  include("{$gl_path_to_engine}admin/lock_site.inc"); break;
    case 'blockeditor_sel_action':  include("{$gl_path_to_engine}blockeditor/blockeditor_sel_action.inc"); break;
    case 'users_del_inactivated'      : include("{$gl_path_to_engine}users/users_del_inactivated.inc");   break;
  }
?>