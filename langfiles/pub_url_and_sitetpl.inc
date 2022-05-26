<?php
if((strpos($gl_mod, 'url_and_sitetpl_') !== false) || strpos($gl_act, 'url_and_sitetpl_') !== false)
{
		//_form.inc
		  //form field captions
		  $l_url_and_sitetpl[1] = "Шаблон сайта";
		  $l_url_and_sitetpl[2] = "Введите URL или его часть";
		  //form select options
		  $l_url_and_sitetpl[3] = "нет (основной шаблон)";
		  //form field captions
		  $l_url_and_sitetpl[4] = "Позиция";
		//url_and_sitetpl_add.inc, _edit.inc
		  //h1
		  $l_url_and_sitetpl[5] = "Добавить соответсвие";
		  $l_url_and_sitetpl[6] = "Параметры соответствия";
		  //errors
		  $l_url_and_sitetpl[7] = "Введите целое положительное число в поле <b>позиция</b>.";
		  $l_url_and_sitetpl[8] = "Заполните, пожалуйста, поле <b>url</b>.";
		//url_and_sitetpl_list.inc
		  //h1
		  $l_url_and_sitetpl[9] = "Соответствия";
		  //option
		  $l_url_and_sitetpl[10] = "Добавить соответствие";
		  //info
		  $l_url_and_sitetpl[11] = "Не добавлено ни одного соответствия.";
		  //th
		  $l_url_and_sitetpl[12] = "соответствие";
		  $l_url_and_sitetpl[13] = "опции";
		  //options
		  $l_url_and_sitetpl[14] = "параметры";
		  $l_url_and_sitetpl[15] = "удалить";
		//url_and_sitetpl_del.inc
		  $l_url_and_sitetpl[16] = "Хотите удалить эту связку?";
		  $l_url_and_sitetpl[17] = "";
		  $l_url_and_sitetpl[18] = "";
		  $l_url_and_sitetpl[19] = "";
		  $l_url_and_sitetpl[20] = "";

		  $l_url_and_sitetpl[1000] = "Вернуться в список соответствий";
}
?>