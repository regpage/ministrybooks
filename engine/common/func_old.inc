<?php
  //////////////////////////////////////////////////////////////////////////////
  // �������� ���� �������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������� �������
  //////////////////////////////////////////////////////////////////////////////


   //���������� ������ �� ������ $email, � ����� $subject, ���������� $message,
   //����������� $headers
   //������� �����, ����� ����� ����� ���� ������������ � �������� ����� �� ������� (���������������� ������������������ ���)
   function send_email($email, $subject, $message, $headers)
   {
   	 if(@mail($email,
	          $subject,
	          $message,
	          $headers)) return 1; else return 0;

	    /*print "@mail($email,
	          $subject,
	          $message,
	          $headers))";

	    return 1;*/
   }

   //������������� ���������� meta-����� descr and keywords ��� �������� $gl_page
   //gl_page - id ��������/������ � ������� parts_items
   //$site_keywords - �������� ����� �����
   //$site_descr - �������� �����
   function setmeta($gl_page, $site_keywords, $site_descr)
   {
     global $gl_db_prefix;

     if(!empty($gl_page))
     {
        $query = "SELECT params
                FROM {$gl_db_prefix}parts_items
               WHERE id_item = {$gl_page}";
        $params = unserialize(stripslashes(db_select_one($query)));
        $site_descr .= " ".$params['descr'];
        $site_keywords .= " ".$params['keywords'];
     }
     print "<META NAME='keywords' CONTENT='$site_keywords'>";
     print "<META NAME='description' CONTENT='$site_descr'>";
   }

   //������� �� ���������� $path ��� �����, ����� ������� ������������� �����������
   //��������� $regexp
   function purge_dir($regexp, $path)
 	 {

	    $dir = opendir($path) ;
	    while($file = readdir($dir))
	    if($file != '.' && $file != '..')
	    {
	      if(preg_match($regexp, $file))
	        unlink($path.$file);

	    }
	    closedir($dir);
	  }

	 //������� ������� $catalog �� ����� ������� � �������������
	 function remove_dir($catalog)
		{
		  $dir = opendir($catalog);
		  while(($file = readdir($dir)))
		  {
		    if(is_file($catalog."/".$file))  unlink($catalog."/".$file);
		    else if (is_dir($catalog."/".$file) &&
		            ($file != ".") &&
		            ($file != "..")) remove_dir($catalog."/".$file);
		  }
		  closedir($dir);
		  rmdir($catalog);
		}

  //���������� � ������ $tpl ������ �� ������� $vars
  //������ vars ����� ������: array("{entity}" => $replace)
  function work_template($tpl, $vars = '')
  {
    $code = $tpl;
    if(is_array($vars))
    {
      foreach($vars as $entity => $value)
      {
        $code = str_replace($entity, $value, $code);
      }
    }
    return $code;
  }

  //��������� ������ �� ����� $tpl_file � ���������� ���
  //������� ���������� �������� �� file_get_contents()
  //���� ������� �������� ��� �������������
  function get_tpl_from_file($tpl_file)
  {
    $tpl = file_get_contents($tpl_file);
    return $tpl;
  }

  //������������ bb-���� � ������ $text � html-���, ���������� ������������ �����
  //mode = 'articles' - ������������ ���� �������������� ������� [JUST] [LEFT] [RIGHT] [CENTER]
  //       'forum' - �� ������������ ���� �������������� ������� [JUST] [LEFT] [RIGHT] [CENTER]
  function convert_bb_tags($text, $mode = 'articles')
  {
    global $l_gen;

    //$text = preg_replace("/(http:\/\/[^\s]+)/", "<a href='$1' target='_blank'>$1</a>", $text);
    $pattern = "#\[url=([^\]]+)\](.+?)\[/url\]#is";
    $replace = "<a href='$1'>$2</a>";
    $text    = preg_replace($pattern, $replace, $text);
    $pattern = "#\[url=(.*?)]#is";
    $replace = "<a href='$1'>$1</a>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[email\](.+?)\[/email\]#is";
    $replace = "<a href='mailto:$1'>$1</a>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[email=([^\]]+)\](.+?)\[/email\]#is";
    $replace = "<a href='mailto:$1'>$2</a>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[img=(.*?)]#is";
    $replace = "<img src='$1'/>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[img\](.+?)\[/img\]#is";
    $replace = "<img src='$1'/>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[color=([^\]]+)\](.+?)\[/color\]#is";
    $replace = "<span style='color:$1'>$2</span>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[red\](.+?)\[/red\]#is";
    $replace = "<span style='color:#AF1532'>$1</span>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[green\](.+?)\[/green\]#is";
    $replace = "<span style='color:#0F6B24'>$1</span>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[blue\](.+?)\[/blue\]#is";
    $replace = "<span style='color:#3B3BA3'>$1</span>";
    $text    = preg_replace($pattern, $replace, $text);

    $pattern = "#\[code\](.+?)\[/code\]#is";
    $replace = "<code>$1</code>";
    $text    = preg_replace($pattern, $replace, $text);

    $text = preg_replace("|\[BR]|i", "<br \>", $text);

    //��������������: ������, ���������
    if($mode == 'articles')
    {
      $text = preg_replace("|\[JUST\]|i", "<div class='Just'>", $text);
    	 $text = preg_replace("|\[/JUST\]|i", "</div>", $text);
	     $text = preg_replace("|\[LEFT\]|i", "<div class='Left'>", $text);
	     $text = preg_replace("|\[/LEFT\]|i", "</div>", $text);
	     $text = preg_replace("|\[RIGHT\]|i", "<div class='Right'>", $text);
	     $text = preg_replace("|\[/RIGHT\]|i", "</div>", $text);
	     $text = preg_replace("|\[CENTER\]|i", "<div class='Center'>", $text);
	     $text = preg_replace("|\[/CENTER\]|i", "</div>", $text);
	     $text = preg_replace("|\[H1\]|i", "<table  class='ContentHeaderTbl' cellspacing='0' cellpadding='0' border='0' width='695'><tr><td class='ContentHeader'>", $text);
	     $text = preg_replace("|\[/H1\]|i", "</td></tr></table>", $text);
	     $text = preg_replace("|\[H2\]|i", "<h2>", $text);
	     $text = preg_replace("|\[/H2\]|i", "</h2>", $text);
	     $text = preg_replace("|\[H3\]|i", "<h3>", $text);
	     $text = preg_replace("|\[/H3\]|i", "</h3>", $text);
      $text = preg_replace("|\[BR]|i", "<br \>", $text);
    }

    //�����������
    $text = preg_replace("#\[cit\]#is", "<div class='Cit'>", $text);
    $text = preg_replace("#\[/cit\]#is", "</div>", $text);
    $text = preg_replace("#\[quote=([^\]]+)\]#is", "<b>$1</b> {$l_gen[30]}:<br /><div class='Cit'>", $text);
    $text = preg_replace("#\[/quote\]#is", "</div>", $text);

    $text = preg_replace("|\[B\]|i", "<b>", $text);
    $text = preg_replace("|\[/B\]|i", "</b>", $text);
    $text = preg_replace("|\[I\]|i", "<i>", $text);
    $text = preg_replace("|\[/I\]|i", "</i>", $text);
    $text = preg_replace("|\[U\]|i", "<u>", $text);
    $text = preg_replace("|\[/U\]|i", "</u>", $text);
    $text = preg_replace("|\[sup\]|i", "<sup>", $text);
    $text = preg_replace("|\[/sup\]|i", "</sup>", $text);
    $text = preg_replace("|\[sub\]|i", "<sub>", $text);
    $text = preg_replace("|\[/sub\]|i", "</sub>", $text);

    return($text);
  }

  //������� bb-code �� ������ $text, ���������� ����� ��� bb-�����
  function strip_bb_tags($text)
  {
    $text = preg_replace("/\[[^]]+\]/i", "", $text);
    return $text;
  }

  //��������������� ��� �������� � ����������� � ������ $text
  function smiles_code_to_img($text)
  {
    global $gl_path_to_root, $gl_admin_url, $gl_db_prefix;

    $query = "SELECT code, img_name, width, height
              FROM {$gl_db_prefix}smiles
              ORDER BY pos";
    $results = db_select($query);

    if(is_array($results))
    {

      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $code    =   stripslashes($results[$i]['code']);
        $img_name = $results[$i]['img_name'];
        $width    = $results[$i]['width'];
        $height   = $results[$i]['height'];
        $img  = "<img class='Smile' src='{$gl_admin_url}images/smiles/{$img_name}' width='{$width}' height='{$height}'> ";;

        $text = str_replace($code, $img, $text);
      }
    }
    return($text);
  }

  //��������� ����������, ������� ���������� �������� $_GET � $_POST � ������ $str
  //�������� $escape ���������� ������������ �� ������ �������� mysqli_escape_string()
  function correct_input($str, $escape=true)
  {
    $str = trim($str);
    if($escape == true)
    {
      //if (!false)
        $str = mysqli_real_escape_string(DBBYMYSQLI::$link,$str);
    }
    if($escape == false)
    {
      //if(false)
        $str = stripslashes($str);
    }
    return($str);
  }

  //��������� ��� �������($sort) ,�� �������� ������ ������������� �������� ��� ������� �� ������� ��
  //���� $sort  ����� ��������� ���
  //���� $sort �� �����, ����������� ��� �������� $default
  function get_sort($sort, $default)
  {
    //$sort = $_GET['sort'];
    if(empty($sort))
      $sort = $default;
    else
      $sort = preg_replace("/[^a-z0-9_]/i", "", $sort);
    return($sort);
  }

  //��������� �������� $mode (ASC/DESC), ��������� ��� �� ������������,
  //���� �������� �� �������� ���������� �������� $def
  function get_mode($mode, $def='ASC')
  {
    $modes = array('ASC', 'DESC');
    if(in_array($mode, $modes))
      return($mode);
    else return $def;
  }


  //��������� ����������� (Feb) ���������� �������� ������� � ������ $str
  //�� ���� ����������
  //�������� �������� ��������� � ������������� ������� months
  function translate_data($str, $months)
  {
    if(!empty($months))
    {
      foreach($months as $key => $value)
        $str = str_replace($key, $value, $str);
    }
    return($str);
  }

  //������� ������������ ��������� �� �����
  
  function create_navigation($pages_count, $url, $part, $var_name='part')
  {
    global $l_gen;
    if($pages_count == 1)
      return;

    $to_left = $part - 4;
    if($to_left < 1)
    {
      $end = 10;
      $begin = 1;
    }
    if($to_left >= 1)
    {
      $begin = $to_left;
      $end = $begin + 9;
      if($end > $pages_count)
      {
        $raznitsa = $end - $pages_count;
        $begin = $begin - $raznitsa + 1;
        if($begin < 1) $begin = 1;
        $end = $pages_count;
      }
    }

    $navig .=  "<div class='ngg-navigation'>";
    //������ �� ������ �������� <img height='7px' width='18px' src='images/double-arrows-left.png' alt='double-arrows-left'>
    //������ �� ���������� ��������
    if($part != 1)
      $navig .=  "<a class='prev' href='{$url}&{$var_name}=1' title='{$l_gen[13]}'>&#9668;&#9668;</a><a class='prev' href='{$url}&{$var_name}=".($part - 1)."' title='{$l_gen[14]}'>&#9668;</a>";
    else
      $navig .=   "";
    //��������
    for($i = $begin; $i <= $end; $i++)
    	 {
       if($i <= $pages_count)
       {
          if($i == $part)
            $navig .= "<span> $i <span>";
          else
            $navig .= "<a class='page-numbers' href='{$url}&{$var_name}={$i}'> $i </a>";
        }
        else break;

	     }
    //������ �� ���������� ��������
    if($part != $pages_count)
      $navig .=  "<a class='next' href='{$url}&{$var_name}=".($part + 1)."' title='{$l_gen[15]}'>&#9658;</a><a class='next' href='{$url}&{$var_name}=".$pages_count."' title='{$l_gen[16]}'>&#9658;&#9658;</a>";
    else
    $navig .=  "";
    $navig .= "</div><br>";
    return($navig);
  }
function create_navigation_old($pages_count, $url, $part, $var_name='part')
  {
    global $l_gen;

    if($pages_count == 1)
      return;

    $to_left = $part - 4;
    if($to_left < 1)
    {
      $end = 10;
      $begin = 1;
    }
    if($to_left >= 1)
    {
      $begin = $to_left;
      $end = $begin + 9;
      if($end > $pages_count)
      {
        $raznitsa = $end - $pages_count;
        $begin = $begin - $raznitsa + 1;
        if($begin < 1) $begin = 1;
        $end = $pages_count;
      }
    }

    $navig .=  "<table  align=center class='NavigTbl' cellspacing='0' cellpadding='0' border='0'>";
    $navig .=  "<tr>";
    //������ �� ������ ��������
    $navig .=   "<td class='NavigTD'><a href='{$url}&{$var_name}=1' title='{$l_gen[13]}'>&lt;&lt;</a></td>";
    //������ �� ���������� ��������
    if($part != 1)
      $navig .=  "<td class='NavigTD'><a href='{$url}&{$var_name}=".($part - 1)."' title='{$l_gen[14]}'>&lt;</a></td>";
    else
      $navig .=   "<td class='NavigTDCurPageArr'>&lt;</td>";
    //��������
    for($i = $begin; $i <= $end; $i++)
    	 {
       if($i <= $pages_count)
       {
          if($i == $part)
            $navig .= "<td class='NavigTDCurPage'> $i </td>";
          else
            $navig .= "<td class='NavigTD'><a href='{$url}&{$var_name}={$i}'> $i </a></td>";
        }
        else break;

	     }
    //������ �� ���������� ��������
    if($part != $pages_count)
      $navig .=  "<td class='NavigTD'><a href='{$url}&{$var_name}=".($part + 1)."' title='{$l_gen[15]}'>&gt;</a></td>";
    else
      $navig .=  "<td class='NavigTDCurPageArr'>&gt;</td>";
    $navig .=  "<td class='NavigTD'><a href='{$url}&{$var_name}=".$pages_count."' title='{$l_gen[16]}'>&gt;&gt;</a></td>";
    $navig .= "</tr>";
    $navig .= "</table>";
    return($navig);
  }


  function copy_dir($source, $destination)
  {
    $dir = opendir($source);

    if(!$dir)
    {
      print "Directory $source not exists on the server";
      return;
    }
    while($file = readdir($dir))
    {
      if($file != '.' && $file != '..')
      {
        if(is_dir($source.$file))
        {
          mkdir($destination.$file, 0777);
          copy_dir($source.$file.'/', $destination.$file.'/');
        }
        else
        {
          copy($source.$file, $destination.$file);
          chmod($destination.$file, 0777);
        }
      }
    }
    closedir($dir);
  }


   //���������� ������ � ����
  function save_in_file($filename, $str, $mode = 'w')
  {

    $fp = fopen ($filename, $mode);
    if($fp)
    {
      if(flock($fp, LOCK_EX))
      {
        fwrite ($fp, $str);
        flock($fp, LOCK_UN);
        fclose ($fp);
        chmod($filename, 0777);
      }

    }
  }

  //������� ����� ���������
  //js_field_def - js ����������� ���� �����, ���� ����� ����������� ��� �������� ��� ����� �� ����: document.edit_form.post.value
  function get_smiles($js_field_def)
  {
    global $gl_path_to_engine_root, $gl_db_prefix;
    $query = "SELECT emotion, code, img_name, width, height
              FROM {$gl_db_prefix}smiles
              ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
      $smiles = '';
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $emotion = stripslashes($results[$i]['emotion']);
        $code    = $results[$i]['code'];
        $img_name = $results[$i]['img_name'];
        $width    = $results[$i]['width'];
        $height   = $results[$i]['height'];
        $smiles .= " <img class='Smile' src='{$gl_admin_url}images/smiles/{$img_name}' onClick=\"{$js_field_def}={$js_field_def} + '{$code}'\" width='{$width}' height='{$height}'> ";;
      }
    }

    if(!empty($smiles))
      $smiles = ' '.$smiles;

    return($smiles);
  }

//������� ��������� ������� ������ � ����� �����.

function getPrewText( $text, $maxwords = 20, $maxchar = 300 )
 {
    $sep = ' ';
    $words = split( $sep, $text );
    $char = iconv_strlen($text, 'utf-8');

         if(count($words) > $maxwords)
      {
          $text = join($sep, array_slice($words, 0, $maxwords));
      }
    if ($char > $maxchar)
      {
        $text = iconv_substr( $text, 0, $maxchar, 'utf-8' );
      }
   return $text;
  } 

function err_handler($errno, $errmsg, $filename, $linenum) {

    if (!in_array($errno, Array(E_NOTICE, E_STRICT, E_WARNING))) {
    
        $date = date('Y-m-d H:i:s (T)');
    
        $f = fopen('errors.log', 'a');
        
        if (!empty($f)) {
        
            $err  = "<error>\r\n";
            $err .= "  <date>$date</date>\r\n";
            $err .= "  <errno>$errno</errno>\r\n";
            $err .= "  <errmsg>$errmsg</errmsg>\r\n";
            $err .= "  <filename>$filename</filename>\r\n";
            $err .= "  <linenum>$linenum</linenum>\r\n";
            $err .= "</error>\r\n";
            fwrite($f, $err);
            fclose($f);
            
        }
        
    }

}

set_error_handler('err_handler');
 /* XXTEA encryption arithmetic library. 
 * 
 * Copyright (C) 2006 Ma Bingyao <andot@ujn.edu.cn> 
 * Version:      1.5 
 * LastModified: Dec 5, 2006 
 * This library is free.  You can redistribute it and/or modify it. 
 */  
   
 function long2str($v, $w) {  
     $len = count($v);  
     $n = ($len - 1) << 2;  
     if ($w) {  
         $m = $v[$len - 1];  
         if (($m < $n - 3) || ($m > $n)) return false;  
         $n = $m;  
     }  
     $s = array();  
     for ($i = 0; $i < $len; $i++) {  
         $s[$i] = pack("V", $v[$i]);  
     }  
     if ($w) {  
         return substr(join('', $s), 0, $n);  
     } else {  
         return join('', $s);  
     }  
 }  
   
 function str2long($s, $w) {  
     $v = unpack("V*", $s. str_repeat("\0", (4 - strlen($s) % 4) & 3));  
     $v = array_values($v);  
     if ($w) {  
         $v[count($v)] = strlen($s);  
     }  
     return $v;  
 }  
   
 function int32($n) {  
     while ($n >= 2147483648) $n -= 4294967296;  
     while ($n <= -2147483649) $n += 4294967296;  
     return (int)$n;  
 }  
   
 function xxtea_encrypt($str, $key) {  
     if ($str == "") {  
         return "";  
     }  
     $v = str2long($str, true);  
     $k = str2long($key, false);  
     if (count($k) < 4) {  
         for ($i = count($k); $i < 4; $i++) {  
             $k[$i] = 0;  
         }  
     }  
     $n = count($v) - 1;  
   
     $z = $v[$n];  
     $y = $v[0];  
     $delta = 0x9E3779B9;  
     $q = floor(6 + 52 / ($n + 1));  
     $sum = 0;  
     while (0 < $q--) {  
         $sum = int32($sum + $delta);  
         $e = $sum >> 2 & 3;  
         for ($p = 0; $p < $n; $p++) {  
             $y = $v[$p + 1];  
            $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));  
             $z = $v[$p] = int32($v[$p] + $mx);  
         }  
         $y = $v[0];  
         $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));  
         $z = $v[$n] = int32($v[$n] + $mx);  
    }  
     return long2str($v, false);  
 }  
  
 function xxtea_decrypt($str, $key) {  
     if ($str == "") {  
         return "";  
     }  
     $v = str2long($str, false);  
     $k = str2long($key, false);  
     if (count($k) < 4) {  
         for ($i = count($k); $i < 4; $i++) {  
             $k[$i] = 0;  
         }  
     }  
     $n = count($v) - 1;  
   
     $z = $v[$n];  
     $y = $v[0];  
     $delta = 0x9E3779B9;  
    $q = floor(6 + 52 / ($n + 1));  
     $sum = int32($q * $delta);  
     while ($sum != 0) {  
         $e = $sum >> 2 & 3;  
         for ($p = $n; $p > 0; $p--) {  
             $z = $v[$p - 1];  
            $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));  
             $y = $v[$p] = int32($v[$p] - $mx);  
         }  
         $z = $v[$n];  
         $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));  
         $y = $v[0] = int32($v[0] - $mx);  
         $sum = int32($sum - $delta);  
    }  
     return long2str($v, true);  
} 

 
/////////////////////////////////////////////////////////////////////////////////////

function navigation_books($pages_count, $url, $part, $var_name='part')
  {
    global $l_gen;
    if($pages_count == 1)
      return;

    $to_left = $part - 4;
    if($to_left < 1)
    {
      $end = 10;
      $begin = 1;
    }
    if($to_left >= 1)
    {
      $begin = $to_left;
      $end = $begin + 9;
      if($end > $pages_count)
      {
        $raznitsa = $end - $pages_count;
        $begin = $begin - $raznitsa + 1;
        if($begin < 1) $begin = 1;
        $end = $pages_count;
      }
    }
$navig .=  "<ul class='button-group radius'>";
    if($part != 1)
      $navig .=  "<li><a class='button radius' href='{$url}&{$var_name}=".($part - 1)."' title='{$l_gen[14]}'>� Previous Section</a></li>";
    else
      $navig .=   "";
    if($part != $pages_count)
      $navig .=  "<li><a  class='button radius' href='{$url}&{$var_name}=".($part + 1)."' title='{$l_gen[15]}'>Next Section �</a></li>";
    else
    $navig .=  "";
    $navig .= "</ul>";
    return($navig);
  }
?>