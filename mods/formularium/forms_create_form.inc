<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� �������� ����� �� �����
  //////////////////////////////////////////////////////////////////////////////


  //������� ����� $id_form
  //���������, ����������, ��������� � ���� ���������
  function forms_create_form($id_form)
  {
    global $l_forms, $gl_site, $gl_path_to_templates, $site_img_antiflood, $gl_db_prefix;

    //������� �������� �����
    $f_page = intval($_POST['f_page']);

    //�������� ��������� �����
    $query = "SELECT email_from, encoding, subject, sended_mess, sended_den FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
    $results = db_select($query);
    if(is_array($results))
    {
      //����� �����������
      $form_email_from = $results[0]['email_from'];
      //���������
      $form_encoding = $results[0]['encoding'];
      //���� ���������
      $form_subject = stripslashes($results[0]['subject']);
      //���������, � ��� ��� �������� ������ �������� ������
      $form_sended_den = stripslashes($results[0]['sended_den']);
      //��������� � ���, ��� ������ ����� ������� ����������
      $form_sended_mess = stripslashes($results[0]['sended_mess']);
    }

    //������ �� ���������� ���������� �����
    $forms_sended = unserialize(stripslashes($_SESSION['forms_sended']));
    if(@in_array($id_form, $forms_sended))
    {
      print $form_sended_den;
      return;
    }

    //���������� ������ ��� �������� �� ������ ��������, ��������
    if(!empty($_POST['go_to_next_page']) || !empty($_POST['send']))
    {
      $query = "SELECT *
                FROM {$gl_db_prefix}forms_fields
               WHERE id_form = {$id_form}
                 AND page = {$f_page}
               ORDER BY pos";
      $results = db_select($query);
      if(is_array($results))
      {
        $cnt = count($results);
        for($i = 0; $i < $cnt; $i++)
        {
          $field_name = $results[$i]['field_name'];
     	    $caption    = stripslashes($results[$i]['caption']);
	         $type       = $results[$i]['type'];
	         $oblig      = $results[$i]['oblig'];

          $$field_name = $_POST[$field_name];

          if($type == 'checkbox')
          {
            if($$field_name != 'yes') $$field_name = 'no';
          }
          else
          {
            if($oblig == 'yes')
            {
              if(empty($$field_name))
              {
                $errors[] = "{$l_forms[122]} <b>{$caption}</b>.";
              }
            }
          }
        }
      }
    }

    //��������� ������������ ����� ���� (������ ��������� � ����� �� ��������)
    if(!empty($_POST['send']))
    {
      if($site_img_antiflood == 'yes')
      {
        $corr_img_code = $_SESSION['corr_img_code'];
      	 $img_code = correct_input($_POST['img_code']);
	       //print "$corr_img_code - $users_img_code";
	       if($corr_img_code != $img_code)
	         $errors[] = $l_forms[123];
      }
    }


    ////////////////////////////////////////////////////////////////////////////
    //�������� ��������� / ���������� � ���� ������ �����
    ////////////////////////////////////////////////////////////////////////////

    if(!empty($_POST['send']))
    {
      if(empty($errors))
      {
        //�������� ������ ���������
        $query = "SELECT `tpl` FROM {$gl_db_prefix}forms_messtpl WHERE id_form = {$id_form}";
        $message = stripslashes(db_select_one($query));

        //��������� �������� �����, ��������� ���������
        $query = "SELECT *
       	          FROM {$gl_db_prefix}forms_fields
	                WHERE id_form = {$id_form}
	                ORDER BY pos";
	       $results = db_select($query);
	       if(is_array($results))
	       {
	         $cnt = count($results);
	         for($i = 0; $i < $cnt; $i++)
	         {
	           $field_name = $results[$i]['field_name'];
	           $caption    = stripslashes($results[$i]['caption']);
	           $type       = $results[$i]['type'];
	           $oblig      = $results[$i]['oblig'];
            $params     = unserialize(stripslashes($results[$i]['params']));
	           //$id_field   = $results[$i]['id_field'];

	           if($type == 'checkbox')
	           {
              $$field_name = $_POST[$field_name];
              $yes_rep = $params['yes_rep'];
              $no_rep  = $params['no_rep'];
              if($$field_name == 'yes')
                $$field_name = $yes_rep;
              else
                $$field_name = $no_rep;
	           }
	           elseif($type == 'select')
	           {
              $multiple = $params['multiple'];
              if($multiple == 'yes')
              {
                $options = $_POST[$field_name];
                if(is_array($options))
                {
                  $$field_name = implode(", ", $options);
                } else $$field_name = $l_forms[124];
              }
              else
              {
                $$field_name = $_POST[$field_name];
                if(false)
                  $$field_name  = stripslashes($$field_name);
              }
	           }
            //��� ����� radio, checkbox, textarea
            else
            {
              $$field_name = $_POST[$field_name];
              if(!empty($$field_name))
              {
              	 if(false)
	                 $$field_name  = stripslashes($$field_name);
              } else $$field_name = $l_forms[124];
            }

            //������ ����������� ���� �� ��������
            $message = str_replace("{{$field_name}}", $$field_name, $message);

	         }
	       }

        //�������� ��� ����
        $cur_date     = date('j M Y G:i:s');
        $cur_date     = translate_data($cur_date, $gl_months);
        $message = str_replace('{date}', $cur_date, $message);

        //�������� �������� �����
        $message = str_replace('{your_site}', $gl_site, $message);

        //print "<pre>"; var_dump($_POST); print "</pre>";
        //print $message; return;
        //��������� ��������� � ���� ������
        $message_for_db = mysqli_real_escape_string(DBBYMYSQLI::$link, $message);
        $query = "INSERT INTO {$gl_db_prefix}forms_messages SET id_mess = NULL, message = '{$message_for_db}', date=NOW(), id_form = {$id_form}";
        db_insert($query);

        //������������ ���������
        if($form_encoding != 'utf-8')
		      {
				      if(in_array('iconv', get_loaded_extensions()))
				      {
				        $form_subject = iconv('utf-8', $form_encoding, $form_subject);
				        $message      = iconv('utf-8', $form_encoding, $message);
		        }
		      }

        //��������� ��������� ��� �������� �����
        $headers  = "Content-type: text/plain; charset={$form_encoding} \r\n";
        $headers .= "From: ".$_SERVER['SERVER_ADMIN']."\r\n";
        $headers .= "Reply-To: {$form_email_from}\r\n";

        //�������� e-mail ������ ��� ���� �����
        //�������� ��������� �� ��������� �������
        $query = "SELECT email FROM {$gl_db_prefix}forms_emails_to WHERE id_form = {$id_form}";
        $results = db_select($query);
        if(is_array($results))
        {
          $cnt = count($results);
          for($i = 0; $i < $cnt; $i++)
          {
            $email_to = $results[$i]['email'];
            @mail($email_to, $form_subject, $message, $headers);
          }
        }

        //��������� ������ � ������� $forms_sended ��� ��������� ��������� �������� ������
        $forms_sended[] = $id_form;
        $forms_sended = serialize($forms_sended);
        $_SESSION['forms_sended'] = $forms_sended;

        //������� �������� � �������������
        print $form_sended_mess;
        return;
      }
    }


    //��������� �� ��������� �������� �����
    if(!empty($_POST['go_to_next_page']))
    {
      if(empty($errors))
        $f_page = intval($_POST['next_page']);
    }
    if(empty($f_page)) $f_page = 1;

    //��������� �� ���������� �������� �����
    if(!empty($_POST['go_to_prev_page']))
    {

      $query = "SELECT page FROM {$gl_db_prefix}forms_fields WHERE id_form = {$id_form} AND page < {$f_page} ORDER BY page DESC LIMIT 1";
      $prev_page = db_select_one($query);
      if(!empty($prev_page))
       $f_page = $prev_page;
    }

    //������� �����, ������� ���� ������� ��������
    $query = "SELECT *
                FROM {$gl_db_prefix}forms_fields
               WHERE id_form = {$id_form}
                 AND page = {$f_page}
               ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
      //�������� ��������� ��������
      $query = "SELECT page FROM {$gl_db_prefix}forms_fields WHERE id_form = {$id_form} AND page > {$f_page} LIMIT 1";
      $next_page = db_select_one($query);

      //������
  	   if(!empty($errors))
	       print form_print_errors($errors);

	     //������ �����
	     print form_begin("form{$id_form}", '');

      //��������� �������
      $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
      $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
      $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");

      $cnt = count($results);

      for($i = 0; $i < $cnt; $i++)
      {
        $field_name = $results[$i]['field_name'];
        $caption    = stripslashes($results[$i]['caption']);
        $type       = $results[$i]['type'];
        $oblig      = $results[$i]['oblig'];
        $id_field   = $results[$i]['id_field'];
        $params     = unserialize(stripslashes($results[$i]['params']));

        if($oblig == 'yes')
          $field_tpl = $form_lineobl_tpl;
        else $field_tpl = $form_line_tpl;

        if($type == 'text')
        {
           //�������� �����
           print work_template($field_tpl,    array("{caption}" => $caption,
                                                    "{field}"   => forms_form_create_input($field_name, $css = 'SiteFInputM', $size ='', $params['default_value'])));
        }
        if($type == 'textarea')
        {

           //�������� �����
           $num_rows = $params['num_rows'];
           print work_template($field_tpl,    array("{caption}" => $caption,
                                                    "{field}"   => forms_form_create_textarea($field_name, $num_rows, $css = 'SiteFTextareaM', $params['default_value'])));
        }
        if($type == 'select')
        {
          $size = $params['height'];
          $multiple = $params['multiple'];
          $options = $params['options'];

          $options_arr = explode(';', $options);
          $cnt2 = count($options_arr);
          $options = '';
          if($multiple != 'yes')
          {
          	 for($b = 0; $b < $cnt2; $b++)
            {
              $options .= "<option value='{$options_arr[$b]}'";
              if($_POST[$field_name] == $options_arr[$b])
                $options .= " selected";
              $options .= ">{$options_arr[$b]}</option>";
            }
          }
          else
          {
            $items_arr = $_POST[$field_name];
           // var_dump($items_arr);
            for($b = 0; $b < $cnt2; $b++)
            {
              $options .= "<option value='{$options_arr[$b]}'";
              if(is_array($items_arr))
                if(in_array($options_arr[$b], $items_arr))
                  $options .= " selected";
              $options .= ">{$options_arr[$b]}</option>";
            }
          }
          $field = "<select name='{$field_name}";
          if($multiple == 'yes')
            $field .= "[]";
          $field .= "' class='FormulariumInputM' size='{$size}' ";
          if($multiple == 'yes')
            $field .= "multiple";
          $field .= ">";
          $field .= $options;
          $field .= "</select>";

          print work_template($field_tpl,    array("{caption}" => $caption,
                                                    "{field}"   => $field));
          $field = '';
        }
        if($type == 'checkbox')
        {
          if(!empty($_POST))
          {
            if($_POST[$field_name] == 'yes')
              $checked = 'checked';
            else
              $checked = '';
          }
          else
          {
            $checked = $params['checked'];
            if($checked == 'yes')
	             $checked = 'checked';
          }
          $field = "<input class='FormsCheckbox' type='checkbox' name='{$field_name}' value='yes' {$checked}>";

          print work_template($field_tpl,    array("{caption}" => $caption,
                                                    "{field}"   => $field));
        }
        if($type == 'radio')
        {
          $options = $params['options'];
          $options = explode(';', $options);
          $cnt2 = count($options);
          if(empty($_POST))
            $checked = 'checked';
          else
          {
            $value = $_POST[$field_name];
            if(false)
              $value = stripslashes($value);
          }
          $field = '';
          for($b = 0; $b < $cnt2; $b++)
          {
            if($options[$b] == $value)
              $checked = 'checked';

            $field .= "<input type='radio' name='{$field_name}' value='{$options[$b]}' {$checked}><span class='Text'>{$options[$b]}</span><br>";
            //if(empty($_POST))
              $checked = '';
          }

          print work_template($field_tpl,    array("{caption}" => $caption,
                                                    "{field}"   => $field));
          $options = '';
        }
        if($type == 'groupe_title')
        {
           print work_template($tbl_section_tpl,    array("{caption}" => $caption));
        }
      }

      //��������
      if(empty($next_page))
      {
      	 if($site_img_antiflood == 'yes')
	       {
	         //����: ������� ���
	         print work_template($form_lineobl_tpl, array("{caption}" => $l_forms[125],
	                                                   "{field}" => form_create_input("img_code", 'SiteFInputM', $size ='')));

	         //�������� � �����
	         print work_template($form_line_tpl,    array("{caption}" => $l_forms[126],
	                                                       "{field}" => "<img src='antispam.php'>"));
	       }
      }

      //������
      $buttons = '';
      if($f_page > 1)
        $buttons .= form_create_submit('go_to_prev_page', $value=$l_forms[129], $css = 'SiteFButton');
      if(empty($next_page))
        $buttons .= form_create_submit('send', $value=$l_forms[127], $css = 'SiteFButton');
      else
      {
        $buttons .= form_create_submit('go_to_next_page', $value=$l_forms[128], $css = 'SiteFButton');
      }

      print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                                 "{field}" => $buttons));

      //������� ����
  	   print form_create_hidden('blague',  session_id());
	     print form_create_hidden('id_form',  $id_form);
	     print form_create_hidden('old_pos', $old_pos);
      print form_create_hidden('next_page', $next_page);
      print form_create_hidden('prev_page', $f_page);
      print form_create_hidden('f_page', $f_page);

      //������� ���� � ������� ������ �������
      $query = "SELECT *
                FROM {$gl_db_prefix}forms_fields
               WHERE id_form = {$id_form}
                 AND page != {$f_page}
               ORDER BY pos";
      $results = db_select($query);
      if(is_array($results))
      {
        $cnt = count($results);
        for($i = 0; $i < $cnt; $i++)
        {
          $field_name = $results[$i]['field_name'];
          $type = $results[$i]['type'];
          $params = $results[$i]['params'];
          $params = unserialize(stripslashes($params));
          //print $_POST['field_name'];
          if(!empty($_POST[$field_name]))
          {
            $items = $_POST[$field_name];
            if($type == 'select' && $params['multiple'] == 'yes')
            {
              if(is_array($items))
              {
              	 $cnt2 = count($items);
                for($b = 0; $b < $cnt2; $b++)
                {
                  if(false)
                    $items[$b] = stripslashes($items[$b]);
                  print form_create_hidden("{$field_name}[{$b}]", $items[$b]);
                }
              }
            } else
            {
              $$field_name = $_POST[$field_name];
              if(false)
                $$field_name = stripslashes($$field_name);
              print form_create_hidden($field_name, $$field_name);
            }
          }

        }
      }

      //����� �����
      print form_end();

    }
  }

  //������ ������� ��������� ���� �����
  //$name - ��� ����
  //$css  - CSS �����
  //$size - ������ ����
  function forms_form_create_input($name, $css = '', $size ='', $default_value)
  {
    //global $$name;
    if(!empty($_POST[$name]))
    {
    	 $value = $_POST[$name];
	     if(false)
	       $value = stripslashes($value);
    }
    else
      $value = $default_value;
    $input = "<input type='text' name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}'";
    if(!empty($size))
      $input .= " size='{$size}'";
    $input .= " value=\"".$value."\">";
    return $input;
  }

  //������ ������� ���� textarea
  //$name - ��� ����
  //$size - ���������� �����
  //$css  - CSS �����
  function forms_form_create_textarea($name, $rows = '5', $css = '', $default_value = '')
  {
    if(!empty($_POST[$name]))
    {
    	 $value = $_POST[$name];
	     if(false)
	       $value = stripslashes($value);
    }
    else
      $value = $default_value;

    $input = "<textarea name='{$name}'";
    if(!empty($css))
      $input .= " class='{$css}'";
    if(!empty($rows))
      $input .= " rows='{$rows}'";
    $input .= " >".$value."</textarea>";
    return $input;
  }
?>