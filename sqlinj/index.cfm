<form action="index.php" method="post">
	<textarea id="txtUrls" name="txtUrls" rows="10" style="width: 350px"></textarea>
	<br />
	<input type="submit"  value="Сканировать" />
</form>

<?
/* 
 * Пример к статье "Автоматизация поиска SQL Injection"
 * Автор: Немиро Алексей, 12.05.2008
 * http://aleksey.nemiro.ru
 * http://kbyte.ru
*/
	$taskUrls = array(); // очередь адресов
	$analUrls = array(); // адреса для анализа
	set_time_limit(0);   // ставим максимальное время выполнения скрипта

	if ($txtUrls != NULL)
	{
		$taskUrls = split("\r\n", $txtUrls);
		foreach ($taskUrls as $k => $v)
		{ // список url для сканирования
		 echo $v."<br />";
		}
		
		Process(); // запуск процесса сканирования
	}

	// фукнция выполняет GET-запрос
	function ExecuteHTTPGetRequest($url, $deleteAllTags)
	{
		$url = parse_url($url);
		$host = $url["host"];	$path = $url["path"];
		$req = "GET $path HTTP/1.1\r\nUser-Agent: Bulbulator\r\nHost: $host\r\nConnection: Close\r\n\r\n";
		$fp = fsockopen($host, 80); // открываем сокет
		if (!$fp)
		{
			return "Error.";
		}
		else
		{
			fputs($fp, $req); // отправляем запрос
			// считываем полученные данные в переменную
			$data = "";
			while (!feof($fp)) 
			{
				$data .= @fgetss($fp, 256, $deleteAllTags === true ? "<a>" : NULL);
			}
			fclose($fp); // закрываем сокет
			/*
				TODO: можно распарсить заголовки и проверить, какой ответ дал сервер
				Например, на случай, если сервер сделает редирект (301, 302 коды)
			*/
			return $data; // возвращает полученные данные
		}
	}
	
	// функция производит поиск адресов страниц, и фильтрует их
	function SearchUrls($host, $source)
	{
		global $taskUrls,	$analUrls;
		// шаблон регулярного выражения для поиска url-ов
		$pattern = "#href\s*=\s*(\"|\\')?(.*?)(\"|\\'|\s|\>)#si";
		preg_match_all($pattern, $source, $mtchs);
		if (count($mtchs) < 3) return; // ничего не найдено, выходим
		foreach ($mtchs[2] as $k => $v)
		{
		  // если это E-Mail или JavaScript, то пропускаем его
			if (strpos(strtolower($v), "mailto:") === false && strpos(strtolower($v), "javascript:") === false)
			{ 
				$newUrl = $v; $isNew = true;
				if (ereg("[a-zA-Z]+:\/\/(.*)", $newUrl) === false)
				{ // если адрес начинается не с http://, анализируем и добавляем http://
					$newUrl = strtr(trim($newUrl), "\\", "/"); // меняем слеши, на всякий случай :)
					$arrPath = explode("/", $newUrl); // разбиваем путь на части для анализа
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
				// если url не относится к текущему домену, то добавлять его не надо
				// $nu = parse_url($newUrl);
				// $isNew = ($nu["host"] === $host);
				// смотрим, может у нас такой адрес уже стоит в очереди
				if ($isNew && $taskUrls != NULL) $isNew = !in_array($newUrl, $taskUrls);
				// добавляем в список заданий
				if ($isNew) $taskUrls[] = $newUrl;
				// если у адреса есть параметры, добавляем в список для поиска SQL Injection
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
	
	// сканирование Интернета на наличие SQL Injection :)
	function Process()
	{
		global $taskUrls, $complUrls, $analUrls;
		if (count($taskUrls) <= 0)
		{
			echo "Адреса для сканирования не найдены.";
			return;
		}
		// этап первый, сбор адресов		
		for ($i = 0; $i <= count($taskUrls); $i++)
		{
			$nu = parse_url($taskUrls[$i]);
			SearchUrls($nu["host"], ExecuteHTTPGetRequest($taskUrls[$i], true));
			if ($i > 49) break; // сканируем только 50 страниц
		}
		echo "<hr />";
		// этап второй, поиск уязвимостей
		echo "Интернет просканирован. Найдено ссылок: ".count($analUrls)."<br />";
		// слова и сочетания слов, которые встречаются в сообщениях об ошибках при работы с БД
		$errorMessages = array( 
		"sql syntax", "sql error",
		"ole db error", "incorrect syntax", "unclosed quotation mark",
		"sql server error", "microsoft jet database engine error", "'microsoft.jet.oledb.4.0' reported an error", "reported an error",
		"provider error", "oracle database error", "database error", "db error", "syntax error in string in query expression",
		"ошибка синтаксиса", "синтаксическая ошибка", 
		"ошибка бд", "ошибочный запрос", "ошибка доступа к бд"
		);
		echo "<hr />";
		foreach ($analUrls as $k => $v)
		{
			// особо фантазировать не будем, просто вляпаем одинарную кавычку сразу после знака =
			echo "$k. Анализ ссылки $v ";
			$data = ExecuteHTTPGetRequest(str_replace("=", "='", $v), false);
			// с надеждой, ищем сообщение об ошибке из словаря
			foreach ($errorMessages as $ek => $ev)
			{
				if (stripos($data, $ev) !== false)
				{ // что-то найдено, записываем адрес в журнал
					echo " &nbsp;&nbsp; <span style='color:red'><strong>SQL Injection!</strong></span>";
					break;
				}
			}
			echo "<br />";
		}
	}
?>