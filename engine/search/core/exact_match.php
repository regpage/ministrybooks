<?php
/*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
      +                          Точное совпадение                      +
      +----------------------------------------------------------------*/
/*
// СТАРЫЙ КОД
	$tpl = trim($templateid);    
    if (str_word_count > 1) { $tplconvert_case = mb_convert_case($tpllower, MB_CASE_TITLE, "UTF-8");}
    $stemmed = array();
    $stemmed[] = $tplucfirst;       // Первая буква заглавная
    if (str_word_count > 1) { $stemmed[] = $tplconvert_case; } 
    
    
*/
    /* ****************************************************************************************************************
    * РАЗРАБОТКА
    * Добавить каждое слово с большой буквы во фразе
    * Все варианты с большой буквы во фразе (Массив из фразы и все возможные варианты)
    * ОСНОВНАЯ ЗАДАЧА
    * Поиск заголовков, но исключение словоформ (приставок и окончаний).
    * То есть до и после фразы должны отсутствовать какие либо символы, то же со знаками в начале слова.
    *******************************************************************************************************************/
   $simbolsfosearch = [' ', '.', ',', '!', '?', ':', ';', '-']; //, '"', "'"
    function search_with_simbol($template, $simbol, $register) {
      if ($simbol == 'space') {
        $tpl = mysqli_real_escape_string(DBBYMYSQLI::$link, ' ' . trim($template) . ' ');
      } else {
        $tpl = mysqli_real_escape_string(DBBYMYSQLI::$link, ' ' . trim($template) . $simbol);
      }
      $tpl = htmlspecialchars($tpl);  // преобразование в HTML сущности
      $tpl = stripcslashes($tpl);   // Удаляет экранирование символов
      $tpl = stripslashes($tpl);   // Удаляет экранирование символов
      $tpllower = mb_strtolower($tpl, 'utf-8');  // Все буквы маленькие
      if ($register == 'l') {
        return $tpllower;  // Все буквы маленькие
      } elseif ($register == 'f'){
        return mb_ucfirst($tpllower); // Первая буква заглавная
      } elseif ($register == 'u') {
        return mb_strtoupper($tpl, 'utf-8'); // Все буквы большие
      } elseif ($register == 'o') {
        return $tpl;
      }
    }
    // Обрезает пробелы, НУЖНО УЧИТЫВАТЬ ПЕРВЫЙ ПРОБЕЛ ПЕРЕД ИСКОМОЙ ФРАЗОЙ В ПРЕДЛОЖЕНИИ
    $tpl = trim($templateid);
    $tpl = mysqli_real_escape_string(DBBYMYSQLI::$link,$tpl);
    $tpl = htmlspecialchars($tpl);  // преобразование в HTML сущности
    $tpl = stripcslashes($tpl);   // Удаляет экранирование символов
    $tpl = stripslashes($tpl);   // Удаляет экранирование символов
    $tpllower = mb_strtolower($tpl, 'utf-8');  // Все буквы маленькие
    $tplucfirst = mb_ucfirst($tpllower); // Первая буква заглавная
    $tplupper = mb_strtoupper($tpl, 'utf-8'); // Все буквы большие
    // if ($str_word_count > 1) { $tplconvert_case = mb_convert_case($tpllower, MB_CASE_TITLE, "UTF-8");}
    $stemmed = array();
    # ROMANS CODE DEBUG

    /* ОРИГИНАЛЬНОЙ ФРАЗЫ ИЗ ЗАПРОСА БЫТЬ НЕ ДОЛЖНО В МАССИВЕ, ПРОБЛЕМА ЕСЛИ КТО
     ТО ПОСТАВИТ ЗНАК ПРИПИНАНИЯ В ЗАПРОСЕ? Вопросительный знак ошибка при поиске
     и возможно точка. Лучше удалять знаки препинаня в запросе на первой и последней
     позиции, или разработать отдельный запрос для таких запросов. Регулярки.*/
    // Первая буква заглавная
  //  if (true) { // Если знак припинания на последнем месте в строке

// выбор логики    
    if ($logic != 'OR') {
      $templateid_arr = array($templateid);
    } else {
      $templateid_arr = explode(' ', $templateid);
    }
    
    // формируем массив слов для запроса
foreach ($templateid_arr as $key => $value) {
      if (empty($value) || mb_strlen(trim($value)) < 3) {
        continue;
      }

      // если последний символ знак препинания
      if (substr(trim($value),-1) === '.' || substr(trim($value),-1) === ',' || substr(trim($value),-1) === '!' || substr(trim($value),-1) === '?' || substr(trim($value),-1) === ':' || substr(trim($value),-1) === ';' || substr(trim($value),-1) === '-' || substr(trim($value),-1) === '»' || substr(trim($value),-1) === ')') {

      	// если оригинальная фраза отличается от вариаций
      	if (trim($value) !== search_with_simbol(trim($value), '', 'f') && trim($value) !== search_with_simbol(trim($value), '', 'l') && trim($value) !== search_with_simbol(trim($value), '', 'u')) {
        	
        	// оригинальный запрос
        	// Двойные ковычки
        	$stemmed[] = search_with_simbol(trim($value), 'space', 'o');
        	$stemmed[] = search_with_simbol(trim($value), '', 'o');
        	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'o'));
	        $stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'o'));
      	}      
		
		// Первые буквы заглавные
      	$stemmed[] = search_with_simbol(trim($value), 'space', 'f');
      	$stemmed[] = search_with_simbol(trim($value), '', 'f');
      	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'f'));
      	$stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'f'));
		
		// Все буквы маленькие
      	$stemmed[] = search_with_simbol(trim($value), 'space', 'l');
    	$stemmed[] = search_with_simbol(trim($value), '', 'l'); 
      	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'l'));
      	$stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'l'));
		
		// Все буквы большие
      	$stemmed[] = search_with_simbol(trim($value), 'space', 'u');
      	$stemmed[] = search_with_simbol(trim($value), '', 'u');
      	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'u'));
      	$stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'u'));
	} else {
    	// если оригинальная фраза отличается от вариаций
    	if (trim($value) !== search_with_simbol(trim($value), '', 'f') && trim($value) !== search_with_simbol(trim($value), '', 'l') && trim($value) !== search_with_simbol(trim($value), '', 'u')) {
	        // оригинальный запрос
	        // Двойные ковычки
        	$stemmed[] = search_with_simbol(trim($value), 'space', 'o');  // оригинальный запрос
        	$stemmed[] = search_with_simbol(trim($value), ',', 'o');
        	$stemmed[] = search_with_simbol(trim($value), '.', 'o');
        	$stemmed[] = search_with_simbol(trim($value), "!", "o");
        	$stemmed[] = search_with_simbol(trim($value), "?", "o");
        	$stemmed[] = search_with_simbol(trim($value), ":", "o");
        	$stemmed[] = search_with_simbol(trim($value), ";", "o");
        	$stemmed[] = search_with_simbol(trim($value), "-", "o");
        	$stemmed[] = search_with_simbol(trim($value), '»', 'o');
        	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'o'));
        	$stemmed[] = search_with_simbol(trim($value), ')', 'o');
        	$stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'o'));
    	}

    	// Первые буквы заглавные
    	$stemmed[] = search_with_simbol(trim($value), 'space', 'f');       // Первые буквы заглавные
    	$stemmed[] = search_with_simbol(trim($value), ',', 'f');
    	$stemmed[] = search_with_simbol(trim($value), '.', 'f');
    	$stemmed[] = search_with_simbol(trim($value), "!", "f");
    	$stemmed[] = search_with_simbol(trim($value), "?", "f");
    	$stemmed[] = search_with_simbol(trim($value), ":", "f");
    	$stemmed[] = search_with_simbol(trim($value), ";", "f");
    	$stemmed[] = search_with_simbol(trim($value), "-", "f");
	    //$stemmed[] = search_with_simbol(trim($value), '"', "f");
    	//$stemmed[] = search_with_simbol(trim($value), "'", "f");
    	//$stemmed[] = search_with_simbol(trim($value), "`", "f");
    	$stemmed[] = search_with_simbol(trim($value), '»', 'f');
    	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'f'));
    	$stemmed[] = search_with_simbol(trim($value), ')', 'f');
    	$stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'f'));

    	// Все буквы маленькие
    	$stemmed[] = search_with_simbol(trim($value), 'space', 'l');       // Все буквы маленькие
    	$stemmed[] = search_with_simbol(trim($value), ',', 'l');
    	$stemmed[] = search_with_simbol(trim($value), '.', 'l');
    	$stemmed[] = search_with_simbol(trim($value), "!", "l");
    	$stemmed[] = search_with_simbol(trim($value), "?", "l");
    	$stemmed[] = search_with_simbol(trim($value), ":", "l");
    	$stemmed[] = search_with_simbol(trim($value), ";", "l");
    	$stemmed[] = search_with_simbol(trim($value), "-", "l");
    	$stemmed[] = search_with_simbol(trim($value), '»', 'l');
    	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'l'));
    	$stemmed[] = search_with_simbol(trim($value), ')', 'l');
    	$stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'l'));

    	// Все буквы большие
    	$stemmed[] = search_with_simbol(trim($value), 'space', 'u');       // Все буквы большие
    	$stemmed[] = search_with_simbol(trim($value), ',', 'u');
    	$stemmed[] = search_with_simbol(trim($value), '.', 'u');
    	$stemmed[] = search_with_simbol(trim($value), "!", "u");
    	$stemmed[] = search_with_simbol(trim($value), "?", "u");
    	$stemmed[] = search_with_simbol(trim($value), ":", "u");
    	$stemmed[] = search_with_simbol(trim($value), ";", "u");
    	$stemmed[] = search_with_simbol(trim($value), "-", "u");
    	$stemmed[] = search_with_simbol(trim($value), '»', 'u');
    	$stemmed[] = '«' . trim(search_with_simbol(trim($value), '', 'u'));
    	$stemmed[] = search_with_simbol(trim($value), ')', 'u');
	    $stemmed[] = '(' . trim(search_with_simbol(trim($value), '', 'u'));
  	}
}

// Проверяем есть ли исходная фраза в массиве, и если нет добавляем в массив
//if (!in_array($tpl, $stemmed)) { $stemmed[] = $tpl; }