<form action="index.php" method="post">
	<textarea id="txtUrls" name="txtUrls" rows="10" style="width: 350px"></textarea>
	<br />
	<input type="submit"  value="�����������" />
</form>

<?
/* 
 * ������ � ������ "������������� ������ SQL Injection"
 * �����: ������ �������, 12.05.2008
 * http://aleksey.nemiro.ru
 * http://kbyte.ru
*/
	$taskUrls = array(); // ������� �������
	$analUrls = array(); // ������ ��� �������
	set_time_limit(0);   // ������ ������������ ����� ���������� �������

	if ($txtUrls != NULL)
	{
		$taskUrls = split("\r\n", $txtUrls);
		foreach ($taskUrls as $k => $v)
		{ // ������ url ��� ������������
		 echo $v."<br />";
		}
		
		Process(); // ������ �������� ������������
	}

	// ������� ��������� GET-������
	function ExecuteHTTPGetRequest($url, $deleteAllTags)
	{
		$url = parse_url($url);
		$host = $url["host"];	$path = $url["path"];
		$req = "GET $path HTTP/1.1\r\nUser-Agent: Bulbulator\r\nHost: $host\r\nConnection: Close\r\n\r\n";
		$fp = fsockopen($host, 80); // ��������� �����
		if (!$fp)
		{
			return "Error.";
		}
		else
		{
			fputs($fp, $req); // ���������� ������
			// ��������� ���������� ������ � ����������
			$data = "";
			while (!feof($fp)) 
			{
				$data .= @fgetss($fp, 256, $deleteAllTags === true ? "<a>" : NULL);
			}
			fclose($fp); // ��������� �����
			/*
				TODO: ����� ���������� ��������� � ���������, ����� ����� ��� ������
				��������, �� ������, ���� ������ ������� �������� (301, 302 ����)
			*/
			return $data; // ���������� ���������� ������
		}
	}
	
	// ������� ���������� ����� ������� �������, � ��������� ��
	function SearchUrls($host, $source)
	{
		global $taskUrls,	$analUrls;
		// ������ ����������� ��������� ��� ������ url-��
		$pattern = "#href\s*=\s*(\"|\\')?(.*?)(\"|\\'|\s|\>)#si";
		preg_match_all($pattern, $source, $mtchs);
		if (count($mtchs) < 3) return; // ������ �� �������, �������
		foreach ($mtchs[2] as $k => $v)
		{
		  // ���� ��� E-Mail ��� JavaScript, �� ���������� ���
			if (strpos(strtolower($v), "mailto:") === false && strpos(strtolower($v), "javascript:") === false)
			{ 
				$newUrl = $v; $isNew = true;
				if (ereg("[a-zA-Z]+:\/\/(.*)", $newUrl) === false)
				{ // ���� ����� ���������� �� � http://, ����������� � ��������� http://
					$newUrl = strtr(trim($newUrl), "\\", "/"); // ������ �����, �� ������ ������ :)
					$arrPath = explode("/", $newUrl); // ��������� ���� �� ����� ��� �������
					$newUrl = "";
					foreach($arrPath as $kk => $vv) 
					{
						if ($vv != ".") 
						{
							if (!$kk && (strlen($vv) > 1 && $vv[1] === ":" || $vv === "")) 
							{
								$newUrl = $vv;
							} 
							elseif ($vv === "..") 
							{
								if (strlen($newUrl) > 1 && $newUrl[1] === ":") 
								{
								 continue;
								}
								$p = dirname($newUrl);
								if ($p === "/" || $p === "\\" || $p === ".") 
								{
									$newUrl = "";
								} 
								else 
								{
									$newUrl = $p;
								}
							} 
							elseif ($vv !== "") 
							{
								$newUrl .= "/$vv";
							}
						}
					}
					$newUrl = $newUrl !== "" ? $newUrl : "/";
					$newUrl = "http://".$host.$newUrl;
				}
				// ���� url �� ��������� � �������� ������, �� ��������� ��� �� ����
				// $nu = parse_url($newUrl);
				// $isNew = ($nu["host"] === $host);
				// �������, ����� � ��� ����� ����� ��� ����� � �������
				if ($isNew && $taskUrls != NULL) $isNew = !in_array($newUrl, $taskUrls);
				// ��������� � ������ �������
				if ($isNew) $taskUrls[] = $newUrl;
				// ���� � ������ ���� ���������, ��������� � ������ ��� ������ SQL Injection
				if (strpos($newUrl, "?") && !in_array($newUrl, $analUrls))
				{
					foreach ($analUrls as $k => $v)
					{
						if (strtolower(strrev(stristr(strrev($v), "?"))) === strtolower(strrev(stristr(strrev($newUrl), "?"))))
						{
							$isNew = false;
							break;
						}
					}
				 	if ($isNew) $analUrls[] = $newUrl;
				}
			}
		}
	}
	
	// ������������ ��������� �� ������� SQL Injection :)
	function Process()
	{
		global $taskUrls, $complUrls, $analUrls;
		if (count($taskUrls) <= 0)
		{
			echo "������ ��� ������������ �� �������.";
			return;
		}
		// ���� ������, ���� �������		
		for ($i = 0; $i <= count($taskUrls); $i++)
		{
			$nu = parse_url($taskUrls[$i]);
			SearchUrls($nu["host"], ExecuteHTTPGetRequest($taskUrls[$i], true));
			if ($i > 49) break; // ��������� ������ 50 �������
		}
		echo "<hr />";
		// ���� ������, ����� �����������
		echo "�������� �������������. ������� ������: ".count($analUrls)."<br />";
		// ����� � ��������� ����, ������� ����������� � ���������� �� ������� ��� ������ � ��
		$errorMessages = array( 
		"sql syntax", "sql error",
		"ole db error", "incorrect syntax", "unclosed quotation mark",
		"sql server error", "microsoft jet database engine error", "'microsoft.jet.oledb.4.0' reported an error", "reported an error",
		"provider error", "oracle database error", "database error", "db error", "syntax error in string in query expression",
		"������ ����������", "�������������� ������", 
		"������ ��", "��������� ������", "������ ������� � ��"
		);
		echo "<hr />";
		foreach ($analUrls as $k => $v)
		{
			// ����� ������������� �� �����, ������ ������� ��������� ������� ����� ����� ����� =
			echo "$k. ������ ������ $v ";
			$data = ExecuteHTTPGetRequest(str_replace("=", "='", $v), false);
			// � ��������, ���� ��������� �� ������ �� �������
			foreach ($errorMessages as $ek => $ev)
			{
				if (stripos($data, $ev) !== false)
				{ // ���-�� �������, ���������� ����� � ������
					echo " &nbsp;&nbsp; <span style='color:red'><strong>SQL Injection!</strong></span>";
					break;
				}
			}
			echo "<br />";
		}
	}
?>