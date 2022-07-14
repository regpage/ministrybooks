<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //����� ����������� ������ ������������ (������������ ����� ������� ����� �������)
  //////////////////////////////////////////////////////////////////////////////

  //������������� ��������� �������� ����������
  if(empty($subscribe)) $subscribe = 'yes';

  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('users_edit_form', '');

  //���� ���
  print work_template($form_lineobl_tpl, array("{caption}" => $l_usregform[1],
                                               "{field}" => form_create_input("us_name", 'SiteFInputM', $size ='') ));

  if($gl_adm == 'users_add')
  {
  	 //���� �����
	   print work_template($form_lineobl_tpl, array("{caption}" => $l_usregform[2],
	                                                "{field}" => form_create_input("login", 'SiteFInputM', $size ='') ));

	   //���� ������
	   print work_template($form_lineobl_tpl, array("{caption}" => $l_usregform[3],
	                                                "{field}" => form_create_password('psw', $css = 'SiteFInputM', $size ='') ));

	   //����������� ������
	   print work_template($form_lineobl_tpl, array("{caption}" => $l_usregform[4],
	                                                "{field}" => form_create_password('psw_conf', $css = 'SiteFInputM', $size ='') ));
  }
  //email
  print work_template($form_lineobl_tpl, array("{caption}" => $l_usregform[5],
                                               "{field}" => form_create_input("email", 'SiteFInputM', $size ='') ));



  //������� �����, ������� ���� ������� ��������
  $query = "SELECT *
              FROM {$gl_db_prefix}regform_fields
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
      $id_field   = $results[$i]['id_field'];
      $params     = unserialize(stripslashes($results[$i]['params']));

      if($oblig == 'yes')
        $field_tpl = $form_lineobl_tpl;
      else $field_tpl = $form_line_tpl;
      if($type == 'text')
      {
         //�������� �����
         print work_template($field_tpl,    array("{caption}" => $caption,
                                                  "{field}"   => form_create_input($field_name, $css = 'SiteFInputM', $size ='', $params['default_value'])));
      }
      if($type == 'textarea')
      {

         //�������� �����
         $num_rows = $params['num_rows'];
         print work_template($field_tpl,    array("{caption}" => $caption,
                                                  "{field}"   => form_create_textarea($field_name, $num_rows, $css = 'SiteFTextareaM', $params['default_value'])));
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
            if($$field_name == $options_arr[$b])
              $options .= " selected";
            $options .= ">{$options_arr[$b]}</option>";
          }
        }
        else
        {
          $items_arr = $$field_name;
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

        if($$field_name)
        {
          if($$field_name == $params['yes_rep'])
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
        if(empty($$field_name))
          $checked = 'checked';
        else
        {
          $value = $$field_name;
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
  }

  //����
  print work_template($form_line_tpl,    array("{caption}" => $l_usregform[11],
                                                  "{field}" => form_create_textarea('info', $rows = '5', $css = 'SiteFTextareaM')));

  //����������� �� ��������
  print work_template($form_line_tpl, array("{caption}" => $l_usregform[14],
                                               "{field}" => form_create_checkbox("subscribe", $subscribe)));

  if($site_img_antiflood == 'yes' && $gl_mod = 'users_add')
  {
    //����: ������� ���
    print work_template($form_lineobl_tpl, array("{caption}" => $l_usregform[12],
                                              "{field}" => "<input class='SiteFInputM' name='img_code' type='text'>"));

    //�������� � �����
    print work_template($form_line_tpl,    array("{caption}" => $l_usregform[13],
                                                  "{field}" => "<img src='antispam.php'>"));
  }

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'button')));

  //������� ����
  print form_create_hidden('blague', session_id());
  print form_create_hidden('id_user', $id_user);
  print form_create_hidden('sort', $sort);
  print form_create_hidden('mode', $mode);
  print form_create_hidden('part', $part);

  //����� �����
  print form_end();


?>