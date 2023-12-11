<?php
  //////////////////////////////////////////////////////////////////////////////
  // Основные узлы системы
  //////////////////////////////////////////////////////////////////////////////

# П Е Р Е Д Е Л А Т Ь   В   П Р О Ц Е Д У Р А Х     НЕТ СОЕДИНЕНИЯ! ВОЗМОЖНО КОНФЛИКТ?
#ROMANS CODE 06-09-2021
#REFAACTORING TO MYSQLI
class DBBYMYSQLI {
    static $link;
    static $count = 0;
    
    public static function connect() {
        //if(empty(self::$link)) {
            self::$link = @mysqli_connect('localhost', '', '', '') 
                           or die('No connect'); 
            
            mysqli_set_charset(self::$link, 'utf8');
        //}
    }
}

// Запускаем не отходя от кассы
    DBBYMYSQLI::connect();
// General
function mysqliQueryGnr($sql) {
        $result = mysqli_query(DBBYMYSQLI::$link, $sql)
                  or die(mysqli_error(DBBYMYSQLI::$link)); 
     
        return $result;
}
mysqliQueryGnr("SELECT * FROM forms");
// db_insert_mysqli
function db_insert_mysqli($query) {    
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $sql)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      print $l_gen[2];
      print $query;
      exit;
    }
  }

// db_update_mysqli
function db_update_mysqli($query) {    
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $sql)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      print $l_gen[35];      
      exit;
    } else {
      // R
        // E 
          // N
            // A
              // M
                // E    V

      return db_affected_rows_mysqli($res);
    }
  }

// db_select_mysqli
function db_select_mysqli($query) {   
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $sql)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      Header('Location: ?mod=errors');   
      exit;
    } else {
      if(mysqli_num_rows($res) > 0) {
          while($arr = mysqli_fetch_assoc($res)) {
             $results[] = $arr;
          }
         return($results);
       }
    }
  }  
 // $resres = db_select_mysqli("SELECT * FROM forms");


// db_select_one_mysqli
function db_select_one_mysqli($query) {    
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $sql)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      Header('Location: ?mod=errors');   
      exit;
    } else {      
      if(mysqli_num_rows($res) > 0) {
        mysqli_data_seek($res, 0);
        mysqli_field_seek($res, 0);
        return mysqli_fetch_field($res);        
        // ????????? try
        //return mysql_result($res, 0);
       } else return false;

    }
  }
  
  // db_delete_mysqli
  function db_delete_mysqli($query) {
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $sql)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      print $l_gen[2];      
      print $query;
      exit;
    }
  }

  //возвращает количество измененнных строк
  function db_affected_rows_mysqli($res) {
    // ??? Не передан аргумент
    return mysqli_affected_rows($res);
  }

  //возвращает последний автоматически назначенный ID
  function db_insert_id_mysqli() {
    // ??? Не передан аргумент
    return mysqli_insert_id(DBBYMYSQLI::$link);
  }
#END

function max_packet_init(){
  //Set the value to 16 MB.
  db_query('SET SESSION max_allowed_packet=16*1024*1024');
}

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

//mysql_query('SET SESSION max_allowed_packet=100000000');
//mysql_query('SET @@session.max_allowed_packet=100000000');
//mysql_query('SET max_allowed_packet=100000000');
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

      print $l_gen[35];      
	//print $l_gen[2];
       //print mysql_error();
       //print $query;
      exit;
    }
    else
    {
     //$gl_queries .= "\r\n{$gl_queries}";

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
 Header('Location: ?mod=errors');  
	//print $l_gen[35]; 
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
 Header('Location: ?mod=errors');  	
//print $l_gen[35];       
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