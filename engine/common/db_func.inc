<?php
  //////////////////////////////////////////////////////////////////////////////
  // Основные узлы системы
  //////////////////////////////////////////////////////////////////////////////

#ROMANS CODE 06-09-2021
#REFAACTORING TO MYSQLI
class DBBYMYSQLI {
    static $link;
    static $count = 0;

    public static function connect() {
        if(empty(self::$link)) {
            self::$link = @mysqli_connect('localhost', '', '', '') 
                           or die('No connect');

            mysqli_set_charset(self::$link, 'utf8');
        }
    }
}

// Запускаем не отходя от кассы
    DBBYMYSQLI::connect();

// General не используется
function mysqliQueryGnr($query) {
        $result = mysqli_query(DBBYMYSQLI::$link, $query)
                  or die(mysqli_error(DBBYMYSQLI::$link));

        return $result;
}

  //////////////////////////////////////////////////////////////////////////////
  //Функции взаимодействия с базой данных
  //////////////////////////////////////////////////////////////////////////////

// db_insert_mysqli
function db_insert($query) {
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      print $l_gen[2];
      print $query;
      exit;
    }
  }

// db_update_mysqli
function db_update($query) {
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      print $l_gen[35];
      exit;
    } else {
      return db_affected_rows(DBBYMYSQLI::$link);
    }
  }

// db_select_mysqli
function db_select($query) {
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $query)
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
function db_select_one($query) {
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      Header('Location: ?mod=errors');
      exit;
    } else {
      if(mysqli_num_rows($res) > 0) {
        # OLD WAY
        //mysqli_result($res, 0, $field=0);
        # NEW WAY
        $res->data_seek($row);
        $datarow = $res->fetch_array();
        return $datarow[0];
       } else return false;

    }
  }

  // db_delete_mysqli
  function db_delete($query) {
    global $l_gen;
    $res = mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));
    if(!$res) {
      print $l_gen[2];
      print $query;
      exit;
    }
  }

  //возвращает количество измененнных строк
  function db_affected_rows($link) {
    // ??? Не передан аргумент
    return mysqli_affected_rows($link);
  }

  //возвращает последний автоматически назначенный ID
  function db_insert_id() {
    // ??? Не передан аргумент
    return mysqli_insert_id(DBBYMYSQLI::$link);
  }
#END

function max_packet_init(){
  //Set the value to 16 MB.
  db_query('SET SESSION max_allowed_packet=16*1024*1024');
}

?>
