<?php
  //////////////////////////////////////////////////////////////////////////////
  //�������� ������ ��������� ����� $id_form
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


  //////////////////////////////////////////////////////////////////////////////
  //��������� ��������� � ����������/���������/�������� ���� �� �������
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_GET['field_name']))
  {
    $context = preg_replace("/[^0-9a-z_]*/i", '', $_GET['context']);
    $field_name = preg_replace("/[^0-9a-z_]*/i", '', $_GET['field_name']);

    if($context == 'add')
    {
      //$message = "<br><br><p><span class='Mustred'><b>�������� ����������� {{$field_name}} � ������.</b></span></p><br><br>";
      $tmp = $l_forms[107];
      $tmp = str_replace("{field_name}", $field_name, $tmp);
      $message = $tmp;
    }
    if($context == 'edit')
    {
      $old_field_name = preg_replace("/[^0-9a-z_]*/i", '', $_GET['old_field_name']);
      $tmp = $l_forms[108];
      $tmp = str_replace("{field_name}", $field_name, $tmp);
      $tmp = str_replace("{old_field_name}", $old_field_name, $tmp);
      $message = $tmp;
    }
    if($context == 'del')
    {
      $tmp = $l_forms[109];
      $tmp = str_replace("{field_name}", $field_name, $tmp);
      $message = $tmp;
    }
    unset($field_name);

    //������ �����.
    $back_href = "<a class='Mustgreen' href='index.cfm?mod=forms_fields_list&id_form={$id_form}&page={$page}'>{$l_forms[110]}</a><br>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����, ��������� ������ � ����� $item_tpl_path
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $tpl = correct_input($_POST['tpl']);
    $query = "UPDATE {$gl_db_prefix}forms_messtpl SET tpl = '{$tpl}' WHERE id_form = {$id_form}";
    db_update($query);
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //�������� ���� ����� � ������ fields
  $fields = array("date"  => $l_forms[111],
                  "your_site"  => $l_forms[112],);

  //��������� ������ fields ��� �������� ������� �� ���. �����.
  $query = "SELECT field_name, caption, type
	                 FROM {$gl_db_prefix}forms_fields
                WHERE id_form = {$id_form}
	                ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $type         = $results[$i]['type'];
      if($type != 'groupe_title')
      {
      	 $field_name   = $results[$i]['field_name'];
	       $field_name   = "{$field_name}";
	       $field_title  = stripslashes($results[$i]['caption']);
	       $fields[$field_name] = $field_title;
      }
    }
  }

  //������� ������� ��������� ��� ����� id_form
  $query = "SELECT tpl  FROM {$gl_db_prefix}forms_messtpl WHERE id_form = {$id_form}";
  $tpl   = stripslashes(db_select_one($query));

  //���������
  $query = "SELECT title FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
  $form_title = stripslashes(db_select_one($query));
  print "<h1>{$l_forms[113] } :: {$form_title}</h1>";

  //������� ���������
  if(!empty($message))
    print $message;

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������ �����
  print form_begin('edit_form', '');

  //������ �������� �������
  print work_template($form_line_tpl,    array("{caption}" => $l_forms[114],
                                                   "{field}" => form_create_textarea('tpl', $rows = '15', $css = 'SiteFTextareaL')));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague', session_id());
  print form_create_hidden('old_field_name',  $old_field_name);
  print form_create_hidden('id_field', $id_field);
  print form_create_hidden('id_form', $id_form);
  print form_create_hidden('page', $page);

  //����� �����
  print form_end();

  //������� �� �����
  print "<h2>{$l_forms[115]}</h2>";
  print "<p>{$l_forms[116]}</p>";
  print "<p>";
  foreach($fields as $key => $value)
    print "{".$key."} - {$value}<br>";
  print "</p>";

  //������ �����
  print "<br /><br /><p>{$back_href}<a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[117]}</a></p>";
?>