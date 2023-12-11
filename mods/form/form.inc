<?php

  //////////////////////////////////////////////////////////////////////////////
  //Модуль выводит форму запроса, а также обрабатывает ее данные
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы, отправка данных
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['send']))
  {
    //фильтрация данных формы
    $us_name      = htmlspecialchars($_POST['us_name']);
    $organisation = htmlspecialchars($_POST['organisation']);
    $email        = htmlspecialchars($_POST['email']);
    $www          = htmlspecialchars($_POST['www']);
    $message      = htmlspecialchars($_POST['message']);

    if(empty($us_name))
      $errors[] = $l_form[1];
    if(empty($email))
      $errors[] = $l_form[2];
    if(empty($message))
      $errors[] = $l_form[3];

    //проверка правильности кода (на картинке)
    if($site_img_antiflood == 'yes')
    {
      $corr_img_code = $_SESSION['corr_img_code'];
      $img_code = correct_input($_POST['img_code']);

      if($corr_img_code != $img_code)
        $errors[] = $l_form[4];
    }

    //формируем и отрправляем сообщение
    if(empty($errors))
    {
    	 //формируем текст письма
    	 $s_message  = "{$l_form[5]}: {$us_name}\r\n";
	     $s_message .= "{$l_form[6]}: {$organisation}\r\n";
	     $s_message .= "{$l_form[7]}: {$email}\r\n";
	     $s_message .= "{$l_form[8]}: {$www}\r\n\r\n";
	     $s_message .= "{$message}";

      //конф. файл
	     if(file_exists("config/query_form.inc"))
	       include("config/query_form.inc");

      //тема сообщения
      $subject  = "{$l_form[17]} ".$_SERVER['SERVER_NAME'];

      //перекодируем сообщение
      if($email_encoding != 'utf-8')
      {
		      if(in_array('iconv', get_loaded_extensions()))
		      {
		        $subject = iconv('utf-8', $email_encoding, $subject);
		        $s_message = iconv('utf-8', $email_encoding, $s_message);
        }
      }

      //заголовки
      $headers = "Content-Type: text/plain; charset={$email_encoding}\r\n".
                 "From: ".$_SERVER['SERVER_ADMIN']."\r\n" .
                 "Reply-To: {$email}\r\n";

      //отправляем данные, переходим на страницу с формой, где выводится сообщение об успешной отправке данных
      if(!@mail($to_email, $subject, $s_message, $headers))
        $errors[] = $l_form[16];
      else
      {
	       echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=form&mess=1'></HEAD></HTML>";
	       exit;
	     }
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //заголовок
  print "<h1>{$l_form[15]}</h1>";

  //сообщение об успешном отправлении данных
  $mess = intval($_GET['mess']);
  if($mess == 1)
    print "<p>{$l_form[14]}</p>";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('query_form', '');

  //поле фио
  print work_template($form_lineobl_tpl, array("{caption}" => $l_form[5],
                                               "{field}" => form_create_input("us_name", $css = 'SiteFInputM', $size ='') ));

  //поле организация
  print work_template($form_line_tpl,    array("{caption}" => $l_form[6],
                                               "{field}" => form_create_input("organisation", $css = 'SiteFInputM', $size ='') ));

  //поле e-mail
  print work_template($form_lineobl_tpl, array("{caption}" => $l_form[7],
                                               "{field}" => form_create_input("email", $css = 'SiteFInputM', $size ='') ));

  //поле www
  print work_template($form_line_tpl, array("{caption}" => $l_form[8],
                                            "{field}" => form_create_input("www", $css = 'SiteFInputM', $size ='') ));

  //поле текст сообщения
  print work_template($form_lineobl_tpl, array("{caption}" => $l_form[9],
                                               "{field}" => form_create_textarea('message', $rows = '10', $css = 'SiteFTextareaM')));

  //antiflood
  if($site_img_antiflood == 'yes')
  {
    //поле: введите код
    print work_template($form_lineobl_tpl, array("{caption}" => $l_form[10],
                                              "{field}" => "<input class='SiteFInputM' name='img_code' type='text'>"));

    //картинка с кодом
    print work_template($form_line_tpl,    array("{caption}" => $l_form[11],
                                                  "{field}" => "<img src='antispam.php'>"));
  }

  //кнопки
  print work_template($form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('send', $value=$l_form[13], $css = 'SiteFButton')));
  //скрытые поля
  //print form_create_hidden('blague', session_id());

  //конец формы
  print form_end();

  //ссылка в настройки
  if($gl_group == 'admin')
    print "<p><a class='Mustgreen' href='{$gl_site}index.php?mod=form_settings'>{$l_form[12]}</a></p>";
?>