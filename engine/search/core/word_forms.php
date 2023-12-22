<?php
/*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
     +                          Включая все словоформы                 +
     +----------------------------------------------------------------*/
$tpl = preg_replace("/[^\w\x7F-\xFF\s]/", " ", $templateid);  // убираем все "ненормальные" символы
$tpl = str_replace('?', '_', $tpl);
$tpl = str_replace('*', '%', $tpl);
$tpl = trim(preg_replace("/\s(\S{1,2})\s/", " ", $tpl));     // ограничение по количеству вводимых символов
//$tpl = ereg_replace(" +", " ", $tpl);                        // сжатие 2-х пробелов  .+$
$tpl = mb_ereg_replace(" +", " ", $tpl);
//$tpl = preg_replace(" +", " ", $tpl);                        // сжатие 2-х пробелов  .+$
$words = explode(" ", $tpl);                                 // $words = preg_split("/[\s,]+/", $tpl);// разбиваем строку по произвольному числу запятых и пробельных символов,
// которые включают в себя  " ", \r, \t, \n и \f
$stemmer = new \NXP\Stemmer();
$stemmed = array();
$arr_wrd_cnt = array();

foreach ($words as $word) {
    if (!in_array(mb_strtolower($word, 'utf-8'), $noise_words)) {
        $word = $stemmer->getWordBase($word);           //  Слова в исходном состоянии
        $tpllower = mb_strtolower($word, 'utf-8');      //  Буквы маленькие
        $tplupper = mb_strtoupper($tpllower, 'utf-8');  //  Буквы большие

        $stemmed[] = mb_ucfirst($tpllower);     //  Помещаем в массив первая заглавная буква
        $stemmed[] = $tplupper;  //  Помещаем в массив заглавных букв
        $stemmed[] = $tpllower;  //  Помещаем в массив маленькие буквы
        if (!in_array($word, $stemmed)) {
        	$stemmed[] = $word;
        }  // Проверяем есть ли исходная фраза в массиве, и если нет добавляем в массив
    }
}