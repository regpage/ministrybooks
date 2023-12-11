<?php
  //////////////////////////////////////////////////////////////////////////////
  // Основные узлы системы
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Функции для работы с utf-8
  //Автор: ControlStyle (http://www.pcre.ru/docs/general/text/phputf/)
  //////////////////////////////////////////////////////////////////////////////


		function utf8_strlen($s)
		{
		  return preg_match_all('/./u', $s, $tmp);
		}

		function utf8_substr($s, $offset, $len = 'all')
		{
		  if ($offset<0) $offset = utf8_strlen($s) + $offset;
		  if ($len!='all')
		  {
		    if ($len<0) $len = utf8_strlen($s) - $offset + $len;
		    $xlen = utf8_strlen($s) - $offset;
		    $len = ($len>$xlen) ? $xlen : $len;
		    preg_match('/^.{' . $offset . '}(.{0,'.$len.'})/us', $s, $tmp);
		  }
		  else
		  {
		    preg_match('/^.{' . $offset . '}(.*)/us', $s, $tmp);
		  }
		  return (isset($tmp[1])) ? $tmp[1] : false;
		}



		function utf8_strpos($haystack, $needle, $offset = 0)
		{
		  // get substring (if isset offset param)
		  $offset = ($offset<0) ? 0 : $offset;
		  if ($offset>0)
		  {
		    preg_match('/^.{' . $offset . '}(.*)/us', $haystack, $dummy);
		    $haystack = (isset($dummy[1])) ? $dummy[1] : '';
		  }

		  // get relative pos
		  $p = strpos($haystack, $needle);
		  if ($haystack=='' or $p===false) return false;
		  $r = $offset;
		  $i = 0;

		  // calc real pos
		  while($i<$p)
		  {
		    if (ord($haystack[$i])<128)
		    {
								// ascii symbol
								$i = $i + 1;
		    }
		    else
		    {
		      // non-ascii symbol with variable length
		      // (handling first byte)
		      $bvalue = decbin(ord($haystack[$i]));
		      $i = $i + strlen(preg_replace('/^(1+)(.+)$/', '\1', $bvalue));
		    }
		    $r++;
		  }

		  return $r;
		}

		function utf8_substr_count($h, $n)
		{
		  // preparing $n for using in reg. ex.
		  $n = preg_quote($n, '/');

		  // select all matches
		  preg_match_all('/' . $n . '/u', $h, $dummy);
		  return count($dummy[0]);
		}


?>