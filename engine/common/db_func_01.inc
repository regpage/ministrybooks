<?php
  //////////////////////////////////////////////////////////////////////////////
  // �������� ���� �������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������� �������������� � ����� ������
  //////////////////////////////////////////////////////////////////////////////


  //������������ ���������� � �������� ���� ������
  //db_host - ������ ��
  //db_user - ������������ ��
  //db_psw - ��� ������������ ��
  //db_name - ��� ��
  //db_encoding - ��������� ��
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

  //��������� ������ ���� INSERT INTO
  //������������ ������
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

  //��������� ������ ���� UPDATE
  //������������ ������
  //���������� ���������� ���������� �������
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

  //��������� ������ ���� SELECT
  //������������ ������
  //���������� ��������� ������ � ���� ������� results
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

  //��������� ������ ���� SELECT, �������� ���� ��������
  //������������ ������
  //���������� ��������
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

  //��������� ������ ���� DELETE
  //������������ ������
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

  //���������� ���������� ����������� �����
  function db_affected_rows()
  {
    return mysql_affected_rows();
  }

  //���������� ���������� ����������� �����
  function db_insert_id()
  {
    return mysql_insert_id();
  }
?>