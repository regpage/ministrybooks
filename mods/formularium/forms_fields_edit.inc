<?php

  //////////////////////////////////////////////////////////////////////////////
  // �������� ��������� ���� $id_field ����� $id_form
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_form = intval($_GET['id_form']);
  if(empty($id_form))
    $id_form = intval($_POST['id_form']);

  $page = intval($_GET['page']);
  if(empty($page))
    $page = intval($_POST['page']);

  $id_field = correct_input($_GET['id_field']);
  if(empty($id_field))
    $id_field = correct_input($_POST['id_field']);


  //////////////////////////////////////////////////////////////////////////////
  //�������� ���������� �������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT * FROM {$gl_db_prefix}forms_fields WHERE id_field = {$id_field}";
    $results = db_select($query);
    if(is_array($results))
    {
      $type = $results[0]['type'];
      $pos  = $results[0]['pos'];
      $oblig  = $results[0]['oblig'];
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

  //���������� �����
  if(!empty($_POST['save']))
  {
    //���������� ������
    $caption       = correct_input($_POST['caption']);
	   $pos         = intval($_POST['pos']);
    $type         = correct_input($_POST['type']);
    $old_pos         = intval($_POST['old_pos']);
    $field_name    = correct_input($_POST['field_name']);
    $old_field_name    = correct_input($_POST['old_field_name']);
    $oblig       = $_POST['oblig'];
    if($oblig != 'yes') $oblig = 'no';

    if($pos < 1)
      $errors[] = $l_forms[28];
    if(empty($caption))
      $errors[] = $l_forms[29];
    if($type != 'groupe_title')
    {
    	 if(preg_match("/[^a-z0-9_]/i", $field_name) || empty($field_name))
	       $errors[] = $l_forms[30];

      if(empty($errors))
      {
      	 $denied_fields_names = array('message', 'cur_date', 'your_site', 'type', 'caption', 'params', 'query', 'results', 'oblig', 'field_name', 'errors', 'options', 'cnt', 'multiple');
	       if(in_array($field_name, $denied_fields_names))
	         $errors[] = "{$l_forms[130]}: <b>{$field_name}</b>";

	       //�������� ������ ����� ���� �� ������������
	       $query = "SELECT id_field FROM {$gl_db_prefix}forms_fields WHERE field_name = '{$field_name}' AND id_field != {$id_field}  AND type != 'groupe_title'  AND id_form = {$id_form}";
	       $exists = db_select_one($query);
	       if($exists)
	       {
	         $tmp = $l_forms[37];
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
        $errors[] = $l_forms[31];

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
        $errors[] = $l_forms[32];
      if(empty($no_rep))
        $errors[] = $l_forms[33];
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
        $errors[] = $l_forms[34];
      //������������� �����
      $multiple       = $_POST['multiple'];
      if($multiple != 'yes') $multiple = 'no';
      //�����
      $options        = correct_input($_POST['options']);
      if(empty($options))
        $errors[] = $l_forms[35];

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
        $errors[] = $l_forms[36];

      $params['options'] = $options;
      $params = mysqli_real_escape_string(DBBYMYSQLI::$link, serialize($params));
    }

    //��������� �������
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}forms_fields
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}
                         AND id_form = {$id_form}
                         AND page = {$page}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}forms_fields
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}
                         AND id_form = {$id_form}
                         AND page = {$page}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }

    //��������� ���� ������
    if(empty($errors))
    {
      $query = "UPDATE {$gl_db_prefix}forms_fields
                   SET field_name = '{$field_name}',
                       type       = '{$type}',
                       caption    = '{$caption}',
                       oblig      = '{$oblig}',
                       params     = '{$params}',
                       pos = {$pos}
                  WHERE id_field = {$id_field} ";
      db_update($query);

      //��������� � �������������� ������� ���������
      if($old_field_name != $field_name)
      {
        echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_messtpl&field_name={$field_name}&old_field_name={$old_field_name}&context=edit&id_form={$id_form}&page={$page}'></HEAD></HTML>";
      }
      //��������� � ������ ����� ������� �����
      else
        echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_fields_list&id_form={$id_form}&page={$page}'></HEAD></HTML>";
      exit;

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_forms[39]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine_root}mods/formularium/_fields_edit.inc");

  //������ �����
  print "<p><a class='Mustgreen' href='index.cfm?mod=forms_fields_list&id_form={$id_form}&page={$page}'>{$l_forms[40]}</a></p>";
?>