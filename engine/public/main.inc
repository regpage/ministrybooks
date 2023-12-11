<?php
  //////////////////////////////////////////////////////////////////////////////
  // Основные узлы системы
  //////////////////////////////////////////////////////////////////////////////
if(empty($gl_page) && empty($gl_mod))
    $gl_mod = 'basic';
  //////////////////////////////////////////////////////////////////////////////
  // Извлекаем адрес предыдущей страницы
  //////////////////////////////////////////////////////////////////////////////

  if(isset($_SESSION['prec_uri']))
    $gl_prec_uri = $_SESSION['prec_uri'];
  else
    $gl_prec_uri = 'index.cfm';
//$gl_page = base64_decode($gl_page);
//$gl_page = xxtea_decrypt($gl_page, '766qohdav9pngl2pr1hnpg4172');
  if(!empty($gl_mod) || !empty($gl_page))
  {
    if($gl_mod != 'auth')
      $_SESSION['prec_uri'] = $_SERVER['REQUEST_URI'];
  }
  //////////////////////////////////////////////////////////////////////////////
  // проверяем не закрыт ли сайт для посетителей
  //////////////////////////////////////////////////////////////////////////////

  if($gl_group != 'admin')
  {
    if(file_exists("{$gl_path_to_root}config/site_is_locked.inc"))
    {
    	 if(file_exists("{$gl_path_to_root}config/site_is_locked_msg.inc"))
				    $site_is_locked_msg = file_get_contents("{$gl_path_to_root}config/site_is_locked_msg.inc");
				  if(empty($site_is_locked_msg))
				    $site_is_locked_msg = "This site  is temporarely locked.";
				  print $site_is_locked_msg;
				  exit;
    }
  }
  //////////////////////////////////////////////////////////////////////////////
  //подключаем языковые файлы для пользовательской части (с префиксом pub_)
  //////////////////////////////////////////////////////////////////////////////

  $path = "{$gl_path_to_engine_root}langfiles/";
  $dir = opendir($path);
  while($file = readdir($dir))
  {

    if($file != '.' && $file != '..' && !is_dir("{$path}{$file}"))
    {
      if(strpos($file, 'pub_') !== false)
        { include("{$path}{$file}"); }
    }
  }
  closedir($dir);


  //////////////////////////////////////////////////////////////////////////////
  // подключаем конф. файл с настройками сайта, все переменные имеют тип site_
  //////////////////////////////////////////////////////////////////////////////

  include("{$gl_path_to_root}config/site_settings.inc");


  //////////////////////////////////////////////////////////////////////////////
  //задействуем механизм обработки действий: подключение модулей в зависимости
  //от значения $_GET['act'] ($gl_act - в системе)
  //////////////////////////////////////////////////////////////////////////////

  include("{$gl_path_to_engine}common/actions.inc");


  //////////////////////////////////////////////////////////////////////////////
  //определяем начальную страницу сайта, если нужно
  //////////////////////////////////////////////////////////////////////////////

 if(empty($gl_mod) && empty($gl_page))
  {
    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items
   	           WHERE id_item = {$site_begin_id_item}";

	   $results = db_select($query);
	   $i_type  = $results[0]['i_type'];
    $id_part = $results[0]['id_part'];
    $title   = stripslashes($results[0]['title']);
    $site_title .= " :: $title";
	   $params  = unserialize(stripslashes($results[0]['params']));
    if($i_type == 'page')
    {
      $gl_page =  $site_begin_id_item;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Выбираем параметры текущей страницы
  //////////////////////////////////////////////////////////////////////////////

  elseif(!empty($gl_page))
  {
    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items
   	           WHERE id_item = {$gl_page}";
	   $results = db_select($query);
	   $i_type  = $results[0]['i_type'];
    $id_part = $results[0]['id_part'];
    $title   = stripslashes($results[0]['title']);
    $site_title .= " :: $title";
	   $params  = unserialize(stripslashes($results[0]['params']));
  }


  //////////////////////////////////////////////////////////////////////////////

  //Проверяем права доступа к странице
  //////////////////////////////////////////////////////////////////////////////

  if($gl_group != 'admin' && !empty($id_part))
  {
    $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = {$gl_id_group}
               AND act = 'view'";

    $tmp = db_select_one($query);

    if($tmp)
    {
      $query = "SELECT title
                  FROM {$gl_db_prefix}parts
                 WHERE id_part = id_part";
      $part_title = stripslashes(db_select_one($query));
      //print "<h1>Запрещенная зона</h1><p>Пользователи группы {$gl_group} не могут<br/>просмотривать страницы раздела {$part_title}.</p>";
      $tmp = $l_gen[22];
      $tmp = str_replace("{gl_group}", $gl_group, $tmp);
      $tmp = str_replace("{part_title}", $part_title, $tmp);
      print $tmp;
//include("errors.inc");
      exit;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Выводим версию для печати, завершаем работу системы
  //////////////////////////////////////////////////////////////////////////////

  if($gl_mod == 'print_page')
  {

    $path = "{$gl_path_to_templates}/site/print_page.inc";
    if(file_exists($path))
      { include($path); }
    return;
  }
  //////////////////////////////////////////////////////////////////////////////
  //Выбираем шаблон сайта для текущего раздела.
  //Шаблон сайта для модулей определяется через коннектор integration/pub_actions.inc
  //подключается в основном узле /engine/common/actions.inc
  //////////////////////////////////////////////////////////////////////////////

  if(empty($gl_id_tpl))
  {
  	 if(!empty($id_part))
	   {
	     $query = "SELECT id_tpl
	                 FROM {$gl_db_prefix}parts
	                WHERE id_part = {$id_part}";
	     $gl_id_tpl = db_select_one($query);
	   }

    //если шаблон сайта для раздела не задан, выбираем шаблон по умолчанию
	   if(empty($gl_id_tpl))
	   {
	      $query = "SELECT id_tpl
	               FROM {$gl_db_prefix}sitetpl
	              WHERE maintpl = 'yes'";
	      $gl_id_tpl = db_select_one($query);
	   }
  }

  //если в системе не создано ни одного шаблона сайта, выводим сообщение, завершаем
  //работу системы
  if(empty($gl_id_tpl))
  {
    print $l_gen[23]; exit;
  }


  //////////////////////////////////////////////////////////////////////////////
  //Выбираем параметры шаблона gl_id_tpl: файл и заголовок
  //////////////////////////////////////////////////////////////////////////////

  $query = "SELECT file, title
              FROM {$gl_db_prefix}sitetpl
             WHERE id_tpl = {$gl_id_tpl}";
  $results = db_select($query);
  $tplfile = $results[0]['file'];
  $tpl_title = $results[0]['title'];


  //////////////////////////////////////////////////////////////////////////////
  //Подключаем через include шаблон сайта
  //////////////////////////////////////////////////////////////////////////////

  $path = "{$gl_path_to_templates}site/{$tplfile}.inc";
  if(file_exists($path))
    { include($path); }
  else
  {
    $tmp = $l_gen[24];
    $tmp = str_replace("{tpl_title}", $tpl_title, $tmp);
    print $tmp;
  }
  //////////////////////////////////////////////////////////////////////////////
  // Обрабатываем коннектор pub_after_site_is_created.inc для всех
  // модулей, где он есть
  //////////////////////////////////////////////////////////////////////////////

  $path = "{$gl_path_to_engine_root}mods/";
  $dir = opendir($path);
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && is_dir("{$path}{$file}"))
    {
    // print "{$path}{$file}/integration/pub_actions.inc" ;
      if(file_exists("{$path}{$file}/integration/pub_after_site_is_created.inc"))
         include("{$path}{$file}/integration/pub_after_site_is_created.inc");
    }
  }
  closedir($dir);
?>