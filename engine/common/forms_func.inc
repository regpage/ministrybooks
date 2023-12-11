<?php
  //////////////////////////////////////////////////////////////////////////////
  // Основные узлы системы
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Функции построения и обработки форм
  //////////////////////////////////////////////////////////////////////////////


  //функция выводит начальные теги формы, параметры соответствуют атрибутам тега form
  function form_begin($name, $action, $method = 'post', $enctype = '', $tbl_width = 440)
  {
    $str = "<form method='{$method}' name='{$name}' action='{$action}' ";
    if($enctype == 'multipart')
      $str .= " enctype='multipart/form-data'";
    $str .= "><table class='SiteFTbl' style='margin-left:0px' cellspacing='0' cellpadding='0' border='0' width='{$tbl_width}'>";
    return $str;
  }

  //выводит закрывающие теги формы, заканчивает фомру
  function form_end()
  {
    return "</table></form>";
  }

  //создает поле типа text с именем $name, значением $$name
  //$css - css-класс поля
  //$size - размер поля в символах
  function form_create_input($name, $css = '', $size ='')
  {
    global $$name;
    $input = "<input type='text' name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}'";
    if(!empty($size))
      $input .= " size='{$size}'";
    $input .= " value=\"".$$name."\" />";
    return $input;
  }

  //создает поле типа select с именем $name и опциями $options
  //$css - css-класс поля
  //$size - размер поля в символах
  //$onClick - код js события onClick
  function form_create_select($name, $options, $css = '', $size ='', $onClick = '')
  {
    $input = "<select name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}'";
    if(!empty($size))
      $input .= " size='{$size}'";
    if(!empty($onClick))
      $input .= " onClick=\"{$onClick}\"";
    $input .= ">{$options}</select>";
    return $input;
  }

  //создает поле типа checbox с именем $name
  //если значение $value = 'yes' checkbox отмечен
  function form_create_checkbox($name, $value)
  {
    $input .= "<input type='checkbox' name='$name' value='yes'";
    if($value == 'yes')
      $input .= " checked";
    $input .=  " />";
    return $input;
  }

  //создает поле типа radio с именем $name
  //если значение $value = 'yes' checkbox отмечен
  function form_create_radio($name, $check, $value)
  {
    $input .= "<input type='radio' name='$name' id='$name'  value='$value'";
    if($check == 'yes')
      $input .= "  checked='checked'";
    $input .=  " />";
    return $input;
  }


  //создает поле поле для загрузки файла с именем $name
  //$css - css-класс поля
  //$size - размер поля в символах
  function form_create_file($name, $css = '', $size ='')
  {
    $input = "<input type='file' name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}' ";
    if(!empty($size))
      $input .= " size='{$size}'";
    $input .= " />";
    return $input;
  }

  //создает поле поле типа password с именем $name
  //$css - css-класс поля
  //$size - размер поля в символах
  function form_create_password($name, $css = '', $size ='')
  {
    $input = "<input type='password' name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}' ";
    if(!empty($size))
      $input .= " size='{$size}'";
    $input .= " />";
    return $input;
  }


  //создает поле поле типа password с именем $name
  //$rows - кол-во рядов
  //$css - css-класс поля
  function form_create_textarea($name, $rows = '5', $css = '')
  {
    global $$name;

    $input = "<textarea name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}'";
    if(!empty($rows))
      $input .= " rows='{$rows}'";
    $input .= " >".$$name."</textarea>";
    return $input;
  }

  //создает поле кнопку типа submit с именем $name
  //$value - надпись на кнопке
  //$css - css-класс кнопки
  function form_create_submit($name, $value='', $css = '')
  {
    $input = "<div class='submit'><div><input type='submit' name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}'";
    if(!empty($css))
      $input .= " value='{$value}'";
    $input .= " /></div></div>";
    return $input;
  }

  //создает поле кнопку типа button с именем $name
  //$value - надпись на кнопке
  //$css - css-класс кнопки
  //$onClick - код события onClick
  function form_create_button($name, $value='', $css = '', $on_click)
  {
    $input = "<input type='button' name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}'";
    if(!empty($css))
      $input .= " value='{$value}'";
    $input .= " onClick=\"{$on_click}\" />";
    return $input;
  }

  //создает скрытое поле с именем $name и значением $value
  function form_create_hidden($name, $value)
  {
    $input = "<input type='hidden' name='{$name}' value=\"{$value}\" />";
    return $input;
  }


  //создает bbocodeeditor с именем $name и значением $text
  //$gl_path_to_bbcodeeditor - путь к редактору bbcodeeditor
  //$mode - small (без тегов форматирования абзацев) / или пустая строка (полная версия редактора)
  //$css - css-класс поля
  //$rows - кол-во рядов
  //;url_for_images - url адрес директории с изображениями кнопок
  function form_create_bbcodeeditor($gl_path_to_bbcodeeditor, $mode, $name, $text, $css, $rows, $url_for_images)
  {

    $editor = file_get_contents("{$gl_path_to_bbcodeeditor}bbcodeeditor_{$mode}.htm");

    $editor = str_replace("{url_for_images}", $url_for_images, $editor);
    //$editor = str_replace("{value}", $value, $editor);
    $editor = str_replace("{name}", $name, $editor);
    $editor = str_replace("{text}", $text, $editor);
    $editor = str_replace("{css}", $css, $editor);
    $editor = str_replace("{rows}", $rows, $editor);
    return $editor;
  }

  //выводит ошибки массива $errors
  function form_print_errors($errors)
  {
    print "<div class='message'>";
    print implode("<br/><br/>", $errors);

    print "</div>";
  }

  //копирует файл, загруженный через поле $field_name в директорию $dir
  //удаляет из директории $dir старый файл $old_file_name
  //размер копируемого файла не должне превышать $file_max_size (по умолчанию 3мб)
  function form_file_copy($dir, $field_name, $old_file_name = '', $file_max_size = 1560971520)
  {
    global $l_gen;
    $new_file_name = $_FILES[$field_name]['name'];
    $new_file_path = "{$dir}$new_file_name";
    if(!empty($old_file_name))
      $old_file_path = "{$dir}$old_file_name";
    else
      $old_file_path = '';
    if($_FILES[$field_name]['name'] != '-')
    {

      if(file_exists($new_file_path))
      {
        if($old_file_path != $new_file_path)
        {
          $tmp = $l_gen[3];
          $tmp = str_replace("{new_file_name}", $new_file_name, $tmp);
          $tmp = str_replace("{dir}", $dir, $tmp);
          $error = $tmp;

        }
      }
      if(empty($error))
      {
        $file_tmp  = $_FILES[$field_name]['tmp_name'];
        $file_size = $_FILES[$field_name]['size'];
        $file_type = $_FILES[$field_name]['type'];
        //запрещаем загружать скрипты
        $extentions = array("#\.php#i","#\.phtml#i","#\.php3#i","#\.tml#i","#\.tm#i","#\.pl#i","#\.xml#i","#\.js#i","#\.inc#i");
        $ext = strrchr($_FILES[$field_name]['name'], '.');
        foreach($extentions as $exten)
        {
          if(preg_match($exten, $ext))
          {
            $new_file_path = "{$new_file_path}.txt";
            $new_file_name = "{$new_file_name}.txt";
          }
        }
        //проверяем файл на размер
        ///var_dump($_FILES[$field_name]);
        if($file_size > $file_max_size)
          $error = "{$l_gen[4]} ".($file_max_size / 1024)." kb";
        else
        {
          if(!empty($old_file_name))
          {
            if(file_exists($old_file_path) && !is_dir($old_file_path))
              unlink($old_file_path);
          }
          if(!copy($file_tmp, $new_file_path))
            $error = "{$l_gen[5]} {$new_file_name} {$l_gen[6]} {$dir}.";
          else
            chmod($new_file_path, 0777);
        } //else
      }
    }
    else
    {
      $new_file_name = '';
      if(!empty($old_file_name))
        if(file_exists($old_file_path))
          unlink($old_file_path);
    }
    if(!empty($error))
      $result['error'] = $error;
    else
      $result['new_file_name'] = $new_file_name;
    return($result);
  }

  //копирует изображение, загруженное через поле $field_name в директорию $dir
  //удаляет из директории $dir старое изображение $old_img_name
  //размер копируемого изображения не должен превышать $img_max_size (по умолчанию 100кб)
  function form_image_copy($dir, $field_name, $old_img_name = '', $img_max_size = 1002400)
  {
    global $l_gen;
    $new_img_name = $_FILES[$field_name]['name'];
    $new_img_path = "{$dir}$new_img_name";
    if(!empty($old_img_name))
      $old_img_path = "{$dir}$old_img_name";
    else
      $old_img_path = '';
    if($_FILES[$field_name]['name'] != '-')
    {

      if(file_exists($new_img_path))
      {
        if($old_img_path != $new_img_path)
        {
          $tmp = $l_gen[7];
          $tmp = str_replace("{new_img_name}", $new_img_name, $tmp);
          $tmp = str_replace("{dir}", $dir, $tmp);
          $error = $tmp;
        }
          //$error = "Файл {$new_img_name} уже существует в директории {$dir}.";

      }
      if(empty($error))
      {
        $img_tmp  = $_FILES[$field_name]['tmp_name'];
        $img_size = $_FILES[$field_name]['size'];
        $img_type = $_FILES[$field_name]['type'];

        //копируем изображение
        if(!preg_match("/gif|jpg|png|jpeg/", $img_type))
        {
          $error = $l_gen[8];

        }
        elseif($img_size > $img_max_size)
          $error = "{$l_gen[9]} ".($img_max_size / 1024)." {$l_gen[11]}";
        else
        {
          if(!empty($old_img_name))
          {
            if(file_exists($old_img_path) && !is_dir($old_img_path))
              unlink($old_img_path);
          }
          if(!copy($img_tmp, $new_img_path))
            $error = "{$l_gen[11]} {$new_img_name} {$l_gen[12]} {$dir}.";
          else
            chmod($new_img_path, 0777);
        } //else
      }
    }
    else
    {
      $new_img_name = '';
      if(!empty($old_img_name))
        if(file_exists($old_img_path))
          unlink($old_img_path);
    }
    if(!empty($error))
      $result['error'] = $error;
    else
    {
      $result['new_img_name'] = $new_img_name;
      //определяем размер
      $arr = getimagesize($new_img_path);

      $result['width']  = $arr[0];
      $result['height'] = $arr[1];
    }
    return($result);
  }

  //формирует список опций select'а <option value='{$f_id}'>{$f_caption}</option> из данных таблицы $tbl_name
  //$f_id - название столбца первичного ключа
  //$f_caption - имя столбца с наименованием опции
  //$cur_id - текущее значение первичного ключа
  //$where - часть sql-запроса, условие  WHERE ...
  //$order_by - часть sql-запроса, условие  ORDER BY ...
  function form_get_options_from_db($tbl_name, $f_id, $f_caption, $cur_id, $where = '', $order_by = '')
  {
    global $gl_db_prefix;

    $options = '';

    $query = "SELECT {$f_id}, {$f_caption}
                FROM {$gl_db_prefix}{$tbl_name} ";
    if(!empty($where))
      $query .= $where;
    if(!empty($order_by))
      $query .= $order_by;
    $results = db_select($query);

    if(is_array($results))
    {

      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $id = $results[$i][$f_id];
        $caption = stripslashes($results[$i][$f_caption]);

        $options .= "<option value='{$id}'";
        if($id == $cur_id)
          $options .= " selected";
        $options .= ">{$caption}</option>";
      }
    }

    return $options;
  }
?>