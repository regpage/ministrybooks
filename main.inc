<?php

  //error_reporting(E_NONE);
  //session_start();
  ////////////////////////////////////////////////////////////////////
  //инициализаци¤ глобальных переменных, определ¤ющих текущию страницу
  ////////////////////////////////////////////////////////////////////
  //текуща¤ страница
  if(!empty($_POST['mb']))
    $gl_page = preg_replace("/[^a-z0-9-:._]/i", "", $_POST['mb']);
  elseif(!empty($_GET['mb']))
     $gl_page = preg_replace("/[^a-z0-9-:._]/i", "", $_GET['mb']);
  //текущий модуль системы администрировани¤
  if(!empty($_POST['adm']))
    $gl_adm = preg_replace("/[^a-z0-9_\.]/i", "", $_POST['adm']);
  elseif(!empty($_GET['adm']))
    $gl_adm = preg_replace("/[^a-z0-9_\.]/i", "", $_GET['adm']);

  //текущий модуль без вывода содержимого всего сайта
  if(!empty($_GET['act']))
    $gl_act = preg_replace("/[^a-z0-9_\.]/i", "", $_GET['act']);
  elseif(!empty($_POST['act']))
    $gl_act = preg_replace("/[^a-z0-9_\.]/i", "", $_POST['act']);

  //текущий модуль пользовательской части
  if(!empty($_POST['mod']))
    $gl_mod = preg_replace("/[^a-z0-9_\.]/i", "", $_POST['mod']);

  elseif(!empty($_GET['mod']))
    $gl_mod = preg_replace("/[^a-z0-9_\.]/i", "", $_GET['mod']);


  /////////////////////////////////////////////////////////////////////////////
  //ќпредел¤ем важные системные пути
  /////////////////////////////////////////////////////////////////////////////
 //исправлено начало !!!!
  $gl_site = "http://".$_SERVER['SERVER_NAME'];
  preg_match("/([\a-z_-]+)index.cfm/", $_SERVER['PHP_SELF'], $matches);
  $gl_subdir .= $matches[1];
  $_SESSION['gl_subdir'] = $gl_subdir;
  $gl_site .= $gl_subdir;
 //исправлено конец !!!!

  //путь к корневому каталогу ведущего сайта (сайта с модул¤ми движка, папкой engine)
  if(empty($gl_path_to_engine_root))
  {
    $gl_path_to_engine_root = $_SERVER['DOCUMENT_ROOT'].$gl_subdir;
  }
  //путь к папке с модул¤ми движка (engine)
  $gl_path_to_engine        = $gl_path_to_engine_root."engine/";
  //путь к  визуальному редактору BbCode Editor
  $gl_path_to_widg          = "{$gl_path_to_engine_root}ext_prm/widg/";
  //редактор тегов
  $gl_path_to_bbcodeeditor  = "{$gl_path_to_engine_root}ext_prm/bbcodeeditor/";
  //путь к шаблонам
  $gl_path_to_templates     = "{$gl_path_to_root}templates/";

  /////////////////////////////////////////////////////////////////////////////
  //подключаем служебные модули
  /////////////////////////////////////////////////////////////////////////////

  //функции дл¤ обращени¤ с базой данных
  include("{$gl_path_to_engine}common/db_func.inc");
  //функции построени¤ и обработки данных форм
  include("{$gl_path_to_engine}common/forms_func.inc");
  //функции, общие
  include("{$gl_path_to_engine}common/func.inc");
  //модуль осуществл¤ет подключение к бд
  if(file_exists("{$gl_path_to_root}config/db_connect.inc"))
    include("{$gl_path_to_root}config/db_connect.inc");
  else
    { print ""; return; }
  //функции построени¤ меню
  include("{$gl_path_to_engine}common/menu_func.inc");
  //функции дл¤ работы с utf-8
  include("{$gl_path_to_engine}common/utf8_func.inc");

  //авторизаци¤ c использованием cookie
  if(empty($_SESSION["{$gl_site_name}_gl_group"]))
  {

    if(!empty($_COOKIE["{$gl_site_name}_auth_psw"]))
      include("{$gl_path_to_engine}auth/auth_cookie.inc");
  }

  /////////////////////////////////////////////////////////////////////////////
  //инициализаци¤ переменнных, определ¤ющих статус пользовател¤
  /////////////////////////////////////////////////////////////////////////////

  $gl_id_user = $_SESSION["{$gl_site_name}_gl_id_user"];
  $gl_group   = $_SESSION["{$gl_site_name}_gl_group"];
  $gl_us_name = $_SESSION["{$gl_site_name}_gl_us_name"];

  if(empty($gl_group))
  {
    $gl_id_user = 0;
    $gl_group   = 'unregistered';
    $gl_us_name = 'guest';
  }
  switch($gl_group)
  {
    case 'editors': $gl_id_group = 2; break;
    case 'user':    $gl_id_group = 1; break;
    case 'admin':   $gl_id_group = -1; break;
    default: $gl_id_group = 0; break;
  }

  /*if(file_exists("{$gl_path_to_engine_root}install"))
  {
    print "<h1>—ообщение</h1>";
    print "<p>”далите папку install из корневой директории сайта.</p>";
    return;
  }*/


  //переходим в админку
  if(!empty($gl_adm))
  {
    include("{$gl_path_to_engine}admin/main.inc");
  }
  //переходим в пользовательскую часть
  else
  {
    include("{$gl_path_to_engine}public/main.inc");
  }
?>