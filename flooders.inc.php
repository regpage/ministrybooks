<?
class Flooders {
	var $filename;    /* Имя файла, в котором хранится список  */
                      /* запрещенных IP адресов                */

	var $timeout;     /* Время, на которое производится бан IP */
                      /* адреса. По умолчанию - 600 (10 минут) */

	var $log;         /* Имя лог-файла.                        */

	var $AGENTS;      /* Массив - список разрешенных агентов   */

	/*                                                             */
	/* Конструктор - в параметрах можно указать основные настройки */
    /*                                                             */
    /*   $filename - имя файла, в котором хранится список          */
    /*               забаненных адресов.                           */
    /*   $timeout - время, в секундах, на которое банится IP.      */
    /*                                                             */
    /* Пример: $f=new Flooders("ban.txt",3600);                    */
	/*                                                             */

	function __construct($filename="flooders.txt",$timeout=600) {
		$this->filename=$filename;
		$this->timeout=$timeout;
		$this->AGENTS=Array();
		$this->log="";
		}

	/*                                                             */
	/* Задает имя лог-файла. Если имя файла пустое, то лог-файл    */
    /* не испольщуется                                             */ 
	/*                                                             */

	function SetLogFileName($filename) {
		$this->log=$filename;
		}
    
	/*                                                             */
    /* Проверка IP адреса на нахождение в бан-листе.               */
	/*	                                                           */
    /* Если $http_errror==0, то возвращает true, если IP адрес     */
    /* забанен, и false, если IP адрес разрешен.                   */
    /*                                                             */
    /* Если $http_error==404 и IP адрес забанен, то выводится      */
    /* стандартная страница 404 сервера Apache                     */
    /*                                                             */
    /* Если $http_error==403 и IP адрес забанен, то выводится      */
    /* стандартная страница 403 сервера Apache                     */
	/*                                                             */

	function Check($http_error=0) {
		GLOBAL $HTTP_SERVER_VARS;

		$ip1=$HTTP_SERVER_VARS["REMOTE_ADDR"];
		$ip2=$HTTP_SERVER_VARS["HTTP_X_FORWARDED_FOR"];
		$ip1=str_replace(":","_",$ip1);
		$ip2=str_replace(":","_",$ip2);

		$curtime=time();

		$d=@file($this->filename);
		if (!is_array($d)) {print "Ошибка чтения из файла &quot;".$this->filename."&quot;.";return(false);}

		$found=false;
		for ($i=0;$i<count($d);$i++) {
			$e=explode(" : ",$d[$i]);
			if ($e[1]==$ip1 && trim($e[2])==$ip2 && $e[0]+$this->timeout>$curtime) {$found=true;break;}
			}
		if ($http_error==404 && $found==true) {
			header("HTTP/1.0 404 Not Found");
			die("<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n<HTML><HEAD>\n<TITLE>404 Not Found</TITLE>\n</HEAD><BODY>\n<H1>Not Found</H1>\nThe requested URL ".$HTTP_SERVER_VARS["REQUEST_URI"]." was not found on this server.<P>\n<HR>\n".$HTTP_SERVER_VARS["SERVER_SIGNATURE"]."\n</BODY></HTML>");
			}
		if ($http_error==403 && $found==true) {
			header("HTTP/1.0 403 Forbidden");
			die("<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n<HTML><HEAD>\n<TITLE>403 Forbidden</TITLE>\n</HEAD><BODY>\n<H1>Forbidden</H1>\nYou don't have permission to access ".$HTTP_SERVER_VARS["REQUEST_URI"]."\non this server.<P>\n<HR>\n".$HTTP_SERVER_VARS["SERVER_SIGNATURE"]."\n</BODY></HTML>");
			}
		return($found);
		}

    /*                                                             */
	/* Добавления IP адреса в бан-лист                             */
	/*                                                             */

	function Ban() {
		GLOBAL $HTTP_SERVER_VARS;

		$agent=" ".$HTTP_SERVER_VARS["HTTP_USER_AGENT"];
		for ($i=0;$i<count($this->AGENTS);$i++) {
			if (strpos($agent,$this->AGENTS[$i])) return;
			}

		$ip1=$HTTP_SERVER_VARS["REMOTE_ADDR"];
		$ip2=$HTTP_SERVER_VARS["HTTP_X_FORWARDED_FOR"];
		$ip1=str_replace(":","_",$ip1);
		$ip2=str_replace(":","_",$ip2);

		$curtime=time();

		$d=@file($this->filename);
		if (!is_array($d)) {print "Ошибка чтения из файла &quot;".$this->filename."&quot;.";}

		for ($i=0;$i<count($d);$i++) {
			$e=explode(" : ",$d[$i]);
			if ($e[1]==$ip1 && trim($e[2])==$ip2) unset($d[$i]);
			}

		if (need_add) {
			if (!empty($this->log)) {
				$fw=fopen($this->log,"at");
				if ($fw) {
					fputs($fw, date("Y-m-d H:i:s")." [".$ip1."|".$ip2."]".$agent."\n");
					fclose($fw);
					}
				}
			$d[]=$curtime." : ".$ip1." : ".$ip2."\n";
			}

		$fw=@fopen($this->filename,"wt");
		if (!$fw) {print "Ошибка записи в файла &quot;".$this->filename."&quot;.";return;}

		foreach ($d as $e) fputs($fw,$e);
		fclose($fw);
		}
	
	function AddAlowAgent($agent) {
		$this->AGENTS[]=$agent;
		}
	}
?>
