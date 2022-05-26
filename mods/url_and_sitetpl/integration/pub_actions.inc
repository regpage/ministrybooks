<?php
  //////////////////////////////////////////////////////////////////////////////
  //Коннектор, подключается в основном узле /engine/common/actions.inc
  //Выполняет какие-либо действия или подключает модуль до вывода информации
  //в браузер.
  //////////////////////////////////////////////////////////////////////////////

  //проверяем инсталлирован ли модуль
  include("{$gl_path_to_engine_root}mods/url_and_sitetpl/integration/adm_is_installed.inc");
  if($installed != true)
    return;

  //полный адрес текущей страницы
  $cur_url = "http://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];

  //выбираем соответствия, определяем шаблона сайта при совпадении с адресом страницы
  $query = "SELECT * FROM {$gl_db_prefix}url_and_sitetpl ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $url   = $results[$i]['url'];
      $id_tpl = $results[$i]['id_tpl'];
      if(strpos($gl_site, $url) !== false)
      {
        $gl_id_tpl = $id_tpl;
        break;
      }
    }
  }

?>