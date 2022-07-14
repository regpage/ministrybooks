<?php
  //////////////////////////////////////////////////////////////////////////////
  // ��������� ���� � ����� id_form �� �������� $page
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $type = correct_input($_GET['type']);
  if(empty($type))
    $type = correct_input($_POST['type']);

  $id_field = correct_input($_GET['id_field']);
  if(empty($id_field))
    $id_field = correct_input($_POST['id_field']);


  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� �������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT * FROM {$gl_db_prefix}regform_fields WHERE id_field = {$id_field}";
    $results = db_select($query);
    if(is_array($results))
    {
      $type = $results[0]['type'];
      $pos  = $results[0]['pos'];
      $oblig  = $results[0]['oblig'];
      $in_users_list  = $results[0]['in_users_list'];
      $field_name  = $results[0]['field_name'];
      $caption = stripslashes($results[0]['caption']);
      $params = unserialize(stripslashes($results[0]['params']));
      $old_pos  = $pos;
      $old_field_name  = $field_name;

      if($type == 'checkbox')
      {
        $yes_rep  = $params['yes_rep'];
        $no_rep   = $params['no_rep'];
        $checked  = $params['checked'];
      }
      if($type == 'textarea')
      {
        $num_rows  = $params['num_rows'];
        $default_value  = $params['default_value'];
      }
      if($type == 'text')
      {
        $default_value  = $params['default_value'];
      }
      if($type == 'radio')
      {
        $options  = $params['options'];
      }
      if($type == 'select')
      {
        $options   = $params['options'];
        $multiple  = $params['multiple'];
        $height    = $params['height'];
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //���������� ������ �����
    $caption       = correct_input($_POST['caption']);
	   $pos           = intval($_POST['pos']);
	   $old_pos           = intval($_POST['old_pos']);
    //$field_name    = correct_input($_POST['field_name']);
    $oblig         = $_POST['oblig'];
    if($oblig != 'yes') $oblig = 'no';
    $in_users_list         = $_POST['in_users_list'];
    if($in_users_list != 'yes') $in_users_list = 'no';

    if($pos < 1)
      $errors[] = $l_regform_fields[35];
    if(empty($caption))
      $errors[] = $l_regform_fields[34];

    if($type != 'groupe_title')
    {
    	 //if(preg_match("/[^a-z0-9_]/i", $field_name) || empty($field_name))
	     //  $errors[] = $l_regform_fields[36];

      if(empty($errors))
      {
      	 $denied_fields_names = array('message', 'cur_date', 'your_site', 'type', 'caption', 'params', 'query', 'results', 'oblig', 'field_name', 'errors', 'options', 'cnt', 'multiple');
	       if(in_array($field_name, $denied_fields_names))
	         $errors[] = "{$l_regform_fields[37]}: <b>{$field_name}</b>";

	       //��������� ���� �� ������������
	       $query = "SELECT id_field FROM {$gl_db_prefix}regform_fields WHERE field_name = '{$field_name}' AND type != 'groupe_title'";
	       $exists = db_select_one($query);
	       if($exists)
	       {
	         $tmp = $l_regform_fields[38];

	         $tmp = str_replace("{field_name}", $field_name, $tmp);
	         $errors[] = $tmp;
	       }
      }
    }

    if($type == 'text')
    {
      $default_value = ($_POST['default_value']);
      if(false)
        $default_value = stripslashes($default_value);

      $params['default_value'] = $default_value;
      $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));
    }

    if($type == 'textarea')
    {
      $num_rows = intval($_POST['num_rows']);
      if($num_rows < 1)
        $errors[] = $l_regform_fields[39];

      $default_value = ($_POST['default_value']);
      if(false)
        $default_value = stripslashes($default_value);

      $params['num_rows'] = $num_rows;
      $params['default_value'] = $default_value;
      $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));
    }

    if($type == 'checkbox')
    {
      $yes_rep       = correct_input($_POST['yes_rep']);
      $no_rep        = correct_input($_POST['no_rep']);
      if(empty($yes_rep))
        $errors[] = $l_regform_fields[40];
      if(empty($no_rep))
        $errors[] = $l_regform_fields[41];
      $checked       = $_POST['checked'];
      if($checked != 'yes') $checked = 'no';

      $params['yes_rep'] = $yes_rep;
      $params['no_rep']  = $no_rep;
      $params['checked'] = $checked;
      $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));
    }

    if($type == 'select')
    {
      //������ ������
      $height = intval($_POST['height']);
      if($height < 1)
        $errors[] = $l_regform_fields[42];
      //������������� �����
      $multiple       = $_POST['multiple'];
      if($multiple != 'yes') $multiple = 'no';
      //�����
      $options        = correct_input($_POST['options']);
      if(empty($options))
        $errors[] = $l_regform_fields[43];

      $params['height'] = $height;
      $params['multiple']  = $multiple;
      $params['options'] = $options;
      $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));
    }

    if($type == 'radio')
    {
      //�����
      $options        = correct_input($_POST['options']);
      if(empty($options))
        $errors[] = $l_regform_fields[44];

      $params['options'] = $options;
      $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));
    }

    //��������� �������
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}regform_fields
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}regform_fields
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    //��������� ���� ������
    if(empty($errors))
    {
      $query = "UPDATE {$gl_db_prefix}regform_fields
                    SET type     = '{$type}',
                        caption   = '{$caption}',
                        oblig     = '{$oblig}',
                        in_users_list = '{$in_users_list}',
                        params    = '{$params}',
                        pos = {$pos}
                  WHERE id_field = {$id_field} ";
      db_insert($query);



      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=regform_fields_list'></HEAD></HTML>";
      exit;

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_regform_fields[54]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}regform_fields/_fields_edit.inc");

  //������ �����
  print "<p><a class='Mustgreen' href='?adm=regform_fields_list'>{$l_regform_fields[1000]}</a></p>";
?>