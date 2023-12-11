<?
class Flooders {
	var $filename;    /* ��� �����, � ������� �������� ������  */
                      /* ����������� IP �������                */

	var $timeout;     /* �����, �� ������� ������������ ��� IP */
                      /* ������. �� ��������� - 600 (10 �����) */

	var $log;         /* ��� ���-�����.                        */

	var $AGENTS;      /* ������ - ������ ����������� �������   */

	/*                                                             */
	/* ����������� - � ���������� ����� ������� �������� ��������� */
    /*                                                             */
    /*   $filename - ��� �����, � ������� �������� ������          */
    /*               ���������� �������.                           */
    /*   $timeout - �����, � ��������, �� ������� ������� IP.      */
    /*                                                             */
    /* ������: $f=new Flooders("ban.txt",3600);                    */
	/*                                                             */

	function __construct($filename="flooders.txt",$timeout=600) {
		$this->filename=$filename;
		$this->timeout=$timeout;
		$this->AGENTS=Array();
		$this->log="";
		}

	/*                                                             */
	/* ������ ��� ���-�����. ���� ��� ����� ������, �� ���-����    */
    /* �� ������������                                             */ 
	/*                                                             */

	function SetLogFileName($filename) {
		$this->log=$filename;
		}
    
	/*                                                             */
    /* �������� IP ������ �� ���������� � ���-�����.               */
	/*	                                                           */
    /* ���� $http_errror==0, �� ���������� true, ���� IP �����     */
    /* �������, � false, ���� IP ����� ��������.                   */
    /*                                                             */
    /* ���� $http_error==404 � IP ����� �������, �� ���������      */
    /* ����������� �������� 404 ������� Apache                     */
    /*                                                             */
    /* ���� $http_error==403 � IP ����� �������, �� ���������      */
    /* ����������� �������� 403 ������� Apache                     */
	/*                                                             */

	function Check($http_error=0) {
		GLOBAL $HTTP_SERVER_VARS;

		$ip1=$HTTP_SERVER_VARS["REMOTE_ADDR"];
		$ip2=$HTTP_SERVER_VARS["HTTP_X_FORWARDED_FOR"];
		$ip1=str_replace(":","_",$ip1);
		$ip2=str_replace(":","_",$ip2);

		$curtime=time();

		$d=@file($this->filename);
		if (!is_array($d)) {print "������ ������ �� ����� &quot;".$this->filename."&quot;.";return(false);}

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
	/* ���������� IP ������ � ���-����                             */
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
		if (!is_array($d)) {print "������ ������ �� ����� &quot;".$this->filename."&quot;.";}

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
		if (!$fw) {print "������ ������ � ����� &quot;".$this->filename."&quot;.";return;}

		foreach ($d as $e) fputs($fw,$e);
		fclose($fw);
		}
	
	function AddAlowAgent($agent) {
		$this->AGENTS[]=$agent;
		}
	}
?>
