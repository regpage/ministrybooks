<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ������������������� ������������ �������� ���� �������
  //////////////////////////////////////////////////////////////////////////////


  //���� ������������ �� ���������������, ��������� ������ ������
  if(empty($gl_id_user))
   { print $l_users[23]; return; }


  //////////////////////////////////////////////////////////////////////////////
  //������� �������� ������� �� ���� ������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}users
               WHERE id_user = {$gl_id_user}";
    $results = db_select($query);
    if(is_array($results))
    {
      $us_name =  stripslashes($results[0]['name']);
      //$tel =  stripslashes($results[0]['tel']);
      $email =  stripslashes($results[0]['email']);
      //$www =  stripslashes($results[0]['www']);
      //$icq =  stripslashes($results[0]['icq']);
      //$city =  stripslashes($results[0]['city']);
      //$firm =  stripslashes($results[0]['firm']);
      $info =  stripslashes($results[0]['info']);
      $subscribe =  stripslashes($results[0]['subscribe']);
    }

    $query = "SELECT *
              FROM {$gl_db_prefix}regform_fields
             ORDER BY pos";
		  $results_fld = db_select($query);

		  if(is_array($results_fld))
		  {
		    $cnt = count($results_fld);
		    for($i = 0; $i < $cnt; $i++)
		    {
		      $field_name = $results_fld[$i]['field_name'];
  			   $type       = $results_fld[$i]['type'];
					   $params     = unserialize(stripslashes($results_fld[$i]['params']));



		      $$field_name = $results[0][$field_name];
		      $$field_name;

		      if($type == 'select' && $params['multiple'] == 'yes')
					   {
            $$field_name= explode(", ", $$field_name);

					   }

		    }
		  }
  }


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //���������� ������
    $us_name = strip_tags(correct_input($_POST['us_name']));
    //$tel = strip_tags(correct_input($_POST['tel']));
    $email = strip_tags(correct_input($_POST['email']));

    //$icq = strip_tags(correct_input($_POST['icq']));
    //$www = strip_tags(correct_input($_POST['www']));

    $info = strip_tags(correct_input($_POST['info']));
    //$firm = strip_tags(correct_input($_POST['firm']));
    //$city = strip_tags(correct_input($_POST['city']));

    $subscribe = $_POST['subscribe']; if($subscribe != 'yes') $subscribe = 'no';

    if(empty($us_name))
      $errors[] = $l_users[14];
    if(empty($email))
      $errors[] = $l_users[40];

    //��������� �������� ������������ �����
    $query_part = '';
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
          $query_part .= "`{$field_name}` = '{$$field_name}',";
        }
        elseif($type == 'select')
        {
          $multiple = $params['multiple'];
          if($multiple == 'yes')
          {
            $options = $_POST[$field_name];
            if(is_array($options))
            {
              $$field_name = correct_input(implode(", ", $options));
            }
            else
            {
            	 if($oblig == 'yes')
				          {
 	              $errors[] = "{$l_users[58]} <b>{$caption}</b>.";
				          }

            	 $$field_name = $l_users[57];
            }
          }
          else
          {
            $$field_name = correct_input($_POST[$field_name]);
            //if(false)
            //  $$field_name  = stripslashes($$field_name);
          }


          $query_part .= "`{$field_name}` = '{$$field_name}',";
        }
        //��� ����� radio, checkbox, textarea
        else
        {
          $$field_name = $_POST[$field_name];

          if($oblig == 'yes')
          {
            if(empty($$field_name))
            {
              $errors[] = "{$l_users[58]} <b>{$caption}</b>.";
            }
          }

          if(!empty($$field_name))
          {
            $$field_name  = correct_input($$field_name);
          } else $$field_name = $l_users[57];

          $query_part .= "`{$field_name}` = '{$$field_name}',";
        }



      }
    }

    //��������� ��� ������������ �� ������������
    $query = "SELECT id_user
                FROM {$gl_db_prefix}users
               WHERE name = '{$us_name}'
                 AND id_user != {$gl_id_user}";
    $result = db_select_one($query);
    if(!empty($result))
    {
      //$errors[] = "��� <b>{$us_name}</b> ��� ������������, ������� ������.";
      $tmp = $l_users[18];
      $tmp = str_replace("{us_name}", $us_name, $tmp);
      $errors[] = $tmp;
    }

    if(empty($errors))
    {
      //���������� ����������
      if(!empty($www))
      {
      	 if(strpos($www, 'http://') === false)
	         $www_tmp = 'http://'.$www;
	       else
	         $www_tmp = $www;
      }

      //������ ���������������� ������� � ������� users
      $query = "UPDATE {$gl_db_prefix}users
                   SET `name`  = '{$us_name}',

                       `info` = '{$info}',
                       {$query_part}
                       `email` = '{$email}',
                       `subscribe` = '{$subscribe}'
                WHERE id_user = {$gl_id_user} ";
      db_insert($query);

      //��������� � ������ ������������� � ���������������� �����
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.php?mod=users_edit_pub'></HEAD></HTML>";
      exit;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  //����� ����������� / ����� �������
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_users[38]}</h1>";

  //���������� �����
  include("{$gl_path_to_engine}/users/_users_edit.inc");
?>