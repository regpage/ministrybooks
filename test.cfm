<?php
//$iv = mcrypt_create_iv (mcrypt_get_iv_size (MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB), MCRYPT_RAND);
//$key = "This is a very secret key";
//$text = "Meet me at 11 o'clock behind the monument.";
//echo strlen ($text)."\n";

//$crypttext = mcrypt_encrypt (MCRYPT_RIJNDAEL_256, $key, $text, MCRYPT_MODE_ECB, $iv);
//echo strlen ($crypttext)."\n";

//============================================================================================================
//  ||||||||||||||||||||||||||||         ТЕСТИРОВАНИЕ ШИФРОВАНИЕ URL       ||||||||||||||||||||||||||||||||
//============================================================================================================
session_start();
$var_pasword = session_id();
echo "=========================================================================================================<br/>";
echo "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| ТЕСТИРОВАНИЕ ШИФРОВАНИЯ URL               |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||<br/>";
echo "=========================================================================================================<br/>";
$url="174";
$url_1="174";
//$url = xxtea_encrypt($url, '111111');
//echo "<br/><br/>";
echo "||||||||||| ТЕСТИРОВАНИЕ СЕСИИ |||||||||||<br/><br/> SESSION_ID() == " . session_id();
echo "<br/>Переменная для передачи функции<br/>шифрования в качестве ключа <b>var_pasword</b> == " . $var_pasword;
echo "<br/>";
echo "NAME_ID() == " . session_name();
echo "<br/>";
$url_crypt = user_encode($url, $var_pasword);
echo '<br/>Зашифрованная URL ф-цией [encrypt {'. $url_crypt . '}] == <a href="http://ministrybooks.ru/?mb='. $url_crypt . '">testing_encrypt</a>';
$url_1 = user_encode($url_crypt, $var_pasword);
echo '<br/>Расшифрованная URL  ф-цией [decrypt {'. user_decode($url_crypt, $var_pasword) . '}] == <a href="http://ministrybooks.ru/?mb='. user_decode($url_crypt, $var_pasword) . '">testing_decrypt</a><br/>';

//С‚РµРєСѓС‰Р°СЏ СЃС‚СЂР°РЅРёС†Р°
//$url_2 = preg_replace("/[^a-z0-9-:._]/i", "", $_GET['mb']);
//$url_2 = user_decode($url_1, $var_pasword);
echo '<br/><a href="http://ministrybooks.ru/?mb='. $url_1 . '">testing2</a><br/><br/>';
echo $url;
echo "<br/><br/>**********************************************<br/><br/>";
phpinfo(); 
  
$path = "/var/www/vhosts/ministrybooks.ru/httpdocs/content/{$url_2}/{$url_2}.inc";
  
  if(file_exists($path))
        print $path;
    else
    {
      print "<div class = 'mege'><p>{$l_pages[1]}</p></div>";
      return;
    }


//============================================================================================================
//||||||||||||||||||||||||||||               ФУНКЦИИ ШИФРОВАНИЯ               ||||||||||||||||||||||||||||||||
//============================================================================================================

 function encrypt( $string, $key )  
 {  
   // $key = "BXcfTYewQ";  
   $result = '';  
   for( $i = 1; $i <= iconv_strlen( $string, 'utf-8' ); $i++ )  
   {  
     $char = iconv_substr( $string, $i - 1, 1, 'utf-8' );  
     $keychar = iconv_substr( $key, ( $i % iconv_strlen( $key, 'utf-8') ) - 1, 1 );  
     $char = chr( ord( $char ) + ord( $keychar ) );  
     $result .= $char;  
   }  
   return $result;  
 }  
    
 function decrypt( $string, $key)  
 {  
   //$key = "BXcfTYewQ";  
   $result = '';  
   for( $i = 1; $i <= strlen( $string ); $i++ )  
   {  
     $char = substr( $string, $i - 1, 1 );  
     $keychar = substr( $key, ( $i % strlen( $key ) ) - 1, 1);  
     $char = chr( ord( $char ) - ord( $keychar ) );  
     $result .= $char; 
     
   }  
   return $result;  
 }




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

// ������� ������ � 22 | Eugene77 | �������� ������ ����� ����� ����� �����

// ��� ��������� ��������� ������������ ����� ���� ����������� ������������ �������
// � ������� �����������.
// ��� ����� ���� �� ������� ���������� � ������ ��������, ����� ���������� �� �����
// ���������� ������ ���������. �� ��� ������� ����� �� ��������������� ������, �������������
// ����� ����������� � ��� ������ ������ ����������� ��������  bubble.
// �������  bubble  ������ ������ ������� ����� ���� �������, ���� ��� ����� �� �� �������.
// � ��� �� ��� ���, ���� �� ��������� ���� ������.

function bubble($abc){
for($unsorted=true; $unsorted; ){
    $unsorted=false;
    for($i=0; $i<84; $i++) {
        if($abc[$i]> $abc[$i+1]) {
            $tmp = $abc[$i];
            $abc[$i] = $abc[$i+1];
            $abc[$i+1] = $tmp;
            $unsorted = true;
        }
    }
}
return $abc;
}


// ������� user_encode �� ������� ����� ��������� ������� ������ �� ������� ������
// � ������ ��������� ����� ��������� �� ������ �� ������� ������ ������ ������ �,
// ���� ����, ��������� �������� ��������� $k �� �������� ����� �������.
// �� ������ ����� ����������� ������� ������ (�������) � ����� �����
// � ������� ��������� ����� "while" ���������� ����������� ���������� �������� ������� � ������ ������� ������
// ��� ���� ������� ��������� ��������� ���������� �������������� ������ (��������� ����� ���������� � ������ ������)
// � �������� ����� ����, �������, �������� ����� � 85-������ ������� ���������. (52200625 === 85*85*85*85)
// ����� ����������� ���� ���������� ��� ���� �� ����  ($pentet)
// ����� ���� �� ������� ������ � �������, �� ������� ������������� ����� ����������� ������ ����� �� ��������.

function user_encode($data, $abc) {
$abc=bubble($abc);
for($resalt = "", $i=0; $kvartet=substr($data, $i, 4);  $i+=4){
    for($k=4; $kvartet == substr($data, $i, $k-1); $k--);
    for($bin_kvartet=0, $j=0; $j<$k; $j++) $bin_kvartet=($bin_kvartet<<8)+ord($kvartet[$j]);
    while($j++ < 4) $bin_kvartet=($bin_kvartet<<8)+ord($abc[84]);
    for($pentet = "", $j=0, $d=52200625, $remnant = $bin_kvartet; $j<=$k; $j++){
        $remnant2 = $remnant%$d;
        $index = ($remnant-$remnant2)/$d;
        $pentet .= $abc[$index];
        $remnant = $remnant2;
        $d /= 85;
     }
    $resalt .= $pentet;
}
return $resalt;
}

// ������� user_decode ������� �� ������ ������ � ���� ��������� �����,
// ������������ ������� ����� �� ������ ������.
// � ������ �����������, ������������� �� ��� ������, � �������������� ���������� $k, ���� ����
// ������ ������� ����� - �������� �� ������ ������ �������� ������ ����� �����
// ��� ����� ���������� ���� �������������� ����� � ���������������� �� ��������� ������.
// ������ ���� "while", ����� ��, �������������. ������ ���� ��-�� ������� �������������� ������������ �����, �� �����.
// �������� ���� �������� ��������� ����� �� ������ ����� � ����������� �� � �����.

function user_decode($text, $abc){
$abc=bubble($abc);

for($resalt = "", $i=0; $pentet=substr($text, $i, 5);  $i+=5){
    for($k=5; $pentet == substr($text, $i, $k-1); $k--);
    for($bin_kvartet=0, $j=0; $j<$k; $j++){
        $pos = strpos($abc, $pentet[$j]);
        $bin_kvartet = $bin_kvartet*85+$pos;
    }
    while($j++<5) $bin_kvartet *= 85;
    for($kvartet = "", $j=24; $j>=8*(5-$k); $j -= 8){
        $digit = $bin_kvartet>>$j;
        $bin_kvartet -= $digit<<$j;
        $kvartet .= chr($digit);
}
$resalt .= $kvartet;
}
return $resalt;
}




//$query_string = 'foo=' . urlencode('65656') . '&bar=' . urlencode('65656');
//echo '<a href="mycgi?' . htmlentities($query_string) . '">u</a>';
//'index.php?action=hal_redirect&link_id='.urlencode($hal['link_id']);
//phpinfo(); 
?>
