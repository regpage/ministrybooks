<?php

  //////////////////////////////////////////////////////////////////////////////
  //Форма установки/изменения параметров страницы
  //Подключается в модулях parts_items_pages_add.inc, parts_items_pages_edit.inc
  //////////////////////////////////////////////////////////////////////////////

   //выбираем автора книги 
 /*if(empty($id_item))
  {
    $query = "SELECT id_author
               FROM parts_author
               WHERE id_author = {$id_author}";
    $id_author = db_select_one($query);
   }*/
  
    //опции для select'а выбора автора
                
   if($gl_adm != 'parts_items_pages_add')
    $options = form_get_options_from_db("parts_author", "id_author", "author", $id_author);
  else
    $options = form_get_options_from_db("parts_author", "id_author", "author", 0);
    $options = "<option value='0'>{$l_parts[80]}</option>".$options;

  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //заголовок
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[54],
                                                    "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='')));
  //автор публикации
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[75],
                                                    "{field}" => form_create_select("id_author", $options,  $css = 'SiteFInputMA')));
  
  //ISBN
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[76],
                                                    "{field}" => form_create_input("isbn", $css = 'SiteFInputM', $size ='20')));

  //Дата когда сделано сообщение 
if (!empty($date)) { $arr = explode("-", $date);} else {$arr = explode("-", date("d-m-Y"));}
$res_d = $arr[0];
$res_m = $arr[1]-1;
$res_y = $arr[2];
// print $date ." // " . $res_d ." // " . $res_m ." // " . $res_y;
// http://t1m0n.name/air-datepicker/docs/index-ru.html
print "<tr><td class='SiteFCapt'><span class='Mustred'>$l_parts[87]</span></td><td><input name='date' id='minMaxExample'  data-date-format='dd-mm-yyyy'  date-autoClose='true'  value='$date' type='text' size ='20'>";     
print "<script>
var startDate = new Date($res_y,  $res_m, $res_d);
var dp = $('#minMaxExample').datepicker({startDate: startDate}).data('datepicker');
dp.selectDate(startDate)
$('#minMaxExample').datepicker({
 autoClose: true  
})
</script>";

  //print "<script language='JavaScript'>new tcal ({'formname': 'edit_form', 'controlname': 'date'});</script></td></tr>";

  //Ссылка на книгу в интернет магазине кбк
  print work_template($form_lineobl_tpl,    array("{caption}" => "Ссылка на книгу в интернет магазине kbk.ru",
                                                    "{field}" => form_create_input("bookstorelink", $css = 'SiteFInputM', $size ='20')));

  //Ссылка на картинку книги в интернет магазине кбк
  print work_template($form_lineobl_tpl,    array("{caption}" => "Картинка книги в интернет магазине kbk.ru",
                                                    "{field}" => form_create_input("img_book_store", $css = 'SiteFInputM', $size ='20')));

  //позиция
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_parts[55],
                                                  "{field}" => form_create_input("pos", $css = '', $size ='5')));

  //описание
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[56],
                                                  "{field}" => form_create_textarea('descr', $rows = '5', $css = 'SiteFTextareaM')));

  //ключевые слова
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[57],
                                                  "{field}" => form_create_textarea('keywords', $rows = '5', $css = 'SiteFTextareaM')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'button')));

  //скрытые поля
  //print form_create_hidden('blague', session_id());
  print form_create_hidden('id_part_prec', $id_spo);
  print form_create_hidden('id_item', $id_item);
  print form_create_hidden('old_pos', $old_pos);

  //конец формы
  print form_end();


?>