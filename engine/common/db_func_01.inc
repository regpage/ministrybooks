<?php
  //////////////////////////////////////////////////////////////////////////////
  // Основные узлы системы
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Функции взаимодействия с базой данных
  //////////////////////////////////////////////////////////////////////////////


  //осуществляет соединение с сервером базы данных
  //db_host - сервер бд
  //db_user - пользователь бд
  //db_psw - имя пользователя бд
  //db_name - имя бд
  //db_encoding - кодировка бд
  function db_connect($db_host, $db_user, $db_psw, $db_name, $db_encoding = "utf8")
  {
    global $l_gen;

    $db   = mysql_connect($db_host, $db_user, $db_psw);

    $txt = $l_gen[1];

    if(!$db)
      { print $txt; return(false); }

    if(!mysql_select_db($db_name, $db))
      { print $txt; return(false); }

	   mysql_query("SET NAMES '{$db_encoding}'");
	   mysql_query ("set character_set_client='{$db_encoding}'");
	   mysql_query ("set character_set_results='{$db_encoding}'");
	   mysql_query ("set collation_connection='{$db_encoding}_general_ci'");

  }

  //выполняет запрос типа INSERT INTO
  //обрабатывает ошибки
  function db_insert($query)
  {
    //global $gl_queries;
    global $l_gen;
    $res = mysql_query($query);
    if(!$res)
    {
      print $l_gen[2];
      print mysql_error();
      print $query;
      exit;
    }
    else
    {
    //  $gl_queries .= "\r\n{$gl_queries}";
    }
  }

  //выполняет запрос типа UPDATE
  //обрабатывает ошибки
  //возвращает количество измененных записей
  function db_update($query)
  {
    //global $gl_queries;
    global $l_gen;
    $res = mysql_query($query);
    if(!$res)
    {
      print $l_gen[2];
      print mysql_error();
      print $query;
      exit;
    }
    else
    {
     // $gl_queries .= "\r\n{$gl_queries}";
      return mysql_affected_rows();
    }
  }

  //выполняет запрос типа SELECT
  //обрабатывает ошибки
  //возвращает выбранные записи в виде массива results
  function db_select($query)
  {
   // global $gl_queries;
    global $l_gen;
    $res = mysql_query($query);
    if(!$res)
    { 
	print $l_gen[35];    
      //print $l_gen[2];
      //print mysql_error();
      //print $query;
      exit;
    }
    else
    {
      //$gl_queries .= "\r\n{$gl_queries}";

      if(mysql_num_rows($res) > 0)
    	 {
	        while($arr = mysql_fetch_assoc($res))
	        {

             $results[] = $arr;

	        }
         return($results);
	     }

    }
  }

  //выполняет запрос типа SELECT, выбирает одно значение
  //обрабатывает ошибки
  //возвращает значение
  function db_select_one($query)
  {
    //global $gl_queries;
    global $l_gen;
    $res = mysql_query($query);
    if(!$res)
    {
	print $l_gen[35];       
      //print $l_gen[2];
      //print mysql_error();
      //print $query;
      exit;
    }
    else
    {
      //$gl_queries .= "\r\n{$gl_queries}";
      if(mysql_num_rows($res) > 0)
    	 {

        return mysql_result($res, 0);
	     } else return false;

    }
  }

  //выполняет запрос типа DELETE
  //обрабатывает ошибки
  function db_delete($query)
  {
    //global $gl_queries;
    global $l_gen;
    $res = mysql_query($query);
    if(!$res)
    {
      print $l_gen[2];
      print mysql_error();
      print $query;
      exit;
    }
    else
    {
      //$gl_queries .= "\r\n{$gl_queries}";
    }
  }

  //возвращает количество измененнных строк
  function db_affected_rows()
  {
    return mysql_affected_rows();
  }

  //возвращает количество измененнных строк
  function db_insert_id()
  {
    return mysql_insert_id();
  }
?>