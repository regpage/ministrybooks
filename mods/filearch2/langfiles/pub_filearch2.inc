<?php
		if((strpos($gl_mod, 'filearch2_') !== false) || strpos($gl_act, 'filearch2_') !== false)
  {
  //filearch2_settings.inc
    //h1
    $l_filearch2[1]  = "Настройки";
    //form select options
    $l_filearch2[2]  = "нет (основной шаблон)";
    //form field captions
    $l_filearch2[3]  = "Шаблон сайта";
    $l_filearch2[4]  = "Заголовок главной страницы модуля";
  //pub_actions.inc
    $l_filearch2[5]  = "Файловый архив";
  //filearch2_cats_list.inc
    //main menu items
    $l_filearch2[6]  = "Добавить категорию";
    $l_filearch2[7]  = "Вся статистика";
    $l_filearch2[8]  = "Настройки";
    //info
    $l_filearch2[9]  = "Не добавлено ни одной категории.";
    //form field captions
    $l_filearch2[10] = "Название категории";
    $l_filearch2[11] = "Папка с файлами (относительный путь от корня сайта)";
    $l_filearch2[12] = "Создать папку";
    $l_filearch2[13] = "Позиция";
    $l_filearch2[14] = "Описание";
  //filearch2_cats_add.inc, _edit.inc
    //h1
    $l_filearch2[15] = "Добавить категорию";
    $l_filearch2[16] = "Параметры категории";
    //errors
    $l_filearch2[17] = "Заполните, пожалуйста, поле <b>заголовок</b>.";
    $l_filearch2[18] = "Введите целое положительное число в поле <b>позиция</b>.";
    $l_filearch2[19] = "Не удается создать директорию {dir}";
    //options
    $l_filearch2[20] = "параметры";
    $l_filearch2[21] = "удалить";
  //filearch2_cats_del.inc
    $l_filearch2[22] = "Хотите удалить эту категорию?";
    $l_filearch2[23] = "Директория {dir} и файлы в ней не будут удалены.";
  //filearch2_items_list.inc
    //h1
    $l_filearch2[24] = "файлы";
    //main menu
    $l_filearch2[25] = "Добавить файл";
    $l_filearch2[26] = "Автозагрузка файлов";
    $l_filearch2[27] = "Статистика";
    $l_filearch2[28] = "Файловый менеджер";
    //file options
    $l_filearch2[29] = "параметры";
    $l_filearch2[30] = "удалить";
    //caption
    $l_filearch2[31] = "Добавлен";
    //info
    $l_filearch2[32] = "Пока в этой категории нет файлов.";
    $l_filearch2[33] = "Добавить файл";
  //_items_edit.inc
    //form field captions
    $l_filearch2[34] = "Название файла";
    $l_filearch2[35] = "Файл, выбрать";
    $l_filearch2[36] = "Файл, загрузить";
    $l_filearch2[37] = "Позиция";
    $l_filearch2[38] = "Краткое описание";
    //form select option
    $l_filearch2[39] = "нет";
  //filearch2_items_add.inc, _edit.inc
    //error
    $l_filearch2[40] = "Введите целое положительное число в поле <b>позиция</b>.";
  //filearch2_items_stat.inc
    $l_filearch2[41] = "скачать";
  //filearch2_items_autoload.inc
    //info
    $l_filearch2[42] = "Загрузите файлы в папку {path}";
    $l_filearch2[43] = "Укажите необходимые опции в настройках, нажмите на кнопку \"Подтвердить\". Новые файлы должны добавиться в категорию.";
    //h2
    $l_filearch2[44] = "Информация";
    //form field caption
    $l_filearch2[45] = "Добавить файлы";
    //form select options
    $l_filearch2[46] = "в начало";
    $l_filearch2[47] = "в конец";
    //h2
    $l_filearch2[48] = "Эти файлы были добавлены";
    $l_filearch2[49] = "Эти файлы не были добавлены";
    //info
    $l_filearch2[50] = "Не добавлено ни одного файла.";
    //h1
    $l_filearch2[51] = "Автозагрузка файлов в категорию";
  //filearch2_items_edit.inc
    $l_filearch2[52] = "Параметры файла";
  //filearch2_items_del.inc
    $l_filearch2[53] = "Хотите удалить этот файл?";
  //filearch2_items_list.inc
    //captions
    $l_filearch2[54] = "С отмеченными";
    //button
    $l_filearch2[55] = "Удалить";
  //filearch2_items_del_all.inc
    //del question
    $l_filearch2[56] = "Хотите удалить эти файлы?";
    //h1
    $l_filearch2[57] = "Предупреждение";
    //info
    $l_filearch2[58] = "Не выбрано ни одного файла.";
    //link
    $l_filearch2[59] = "Вернуться";
  //filearch2_items_stat.inc
    //h1
    $l_filearch2[60] = "статистика по скачиванию файлов";
    //th
    $l_filearch2[61] = "файл";
    $l_filearch2[62] = "дата добавления";
    //h2
    $l_filearch2[63] = "Полезная информация";
    //info
    $l_filearch2[64] = "Кликните на значения в полях today, yest, month, чтобы получить детальную статистику по пользователям, скачавшим файл.";
    //h1
    $l_filearch2[65] = "Подробная статистика по скачиваниям файла {file} {period}";
    $l_filearch2[66] = "за сегодня";
    $l_filearch2[67] = "за вчера";
    $l_filearch2[68] = "за месяц";
    //th
    $l_filearch2[69] = "количество скачиваний";
    $l_filearch2[70] = "дата последнего скачивания";
  //filearch2_manager_list.inc
    //h1
    $l_filearch2[71] = "файловый менеджер";
    //info
    $l_filearch2[72] = "Пока в директории нет файлов.";
    //th
    $l_filearch2[73] = "файл";
    $l_filearch2[74] = "опции";
    //option
    $l_filearch2[75] = "удалить";
    //button
    $l_filearch2[76] = "Удалить";
  //filearch2_manager_del.inc
    //del question
    $l_filearch2[77] = "Хотите удалить этот файл?";
  //filearch2_manager_del_all.inc
    //del question
    $l_filearch2[78] = "Хотите удалить эти файлы?";
    //h1
    $l_filearch2[79] = "Предупреждение";
    //info
    $l_filearch2[80] = "Не выбрано ни одного файла.";
    //link
    $l_filearch2[81] = "Вернуться";
  //filearch2_items_stat.inc
    $l_filearch2[82] = "Статистика скачивания по всем файлам";
    $l_filearch2[83] = "Опции";
    $l_filearch2[84] = "Название категории";
    $l_filearch2[85] = "";
    $l_filearch2[86] = "";
    $l_filearch2[87] = "";
    $l_filearch2[88] = "";
    $l_filearch2[89] = "";
    $l_filearch2[90] = "";
    $l_filearch2[91] = "";
    $l_filearch2[92] = "";
    $l_filearch2[93] = "";
    $l_filearch2[94] = "";
    $l_filearch2[95] = "";
    $l_filearch2[96] = "";
    $l_filearch2[97] = "";
    $l_filearch2[98] = "";
    $l_filearch2[99] = "";

		  $l_filearch2[1000] = "Вернуться на главную страницу файлового архива";
		  $l_filearch2[1001] = "Вернуться на страницу \"Статистика\"";
		  $l_filearch2[1002] = "Вернуться в текущую категорию";
		}
?>