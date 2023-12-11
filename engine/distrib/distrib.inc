<?php
  print "<h1>{$l_distrib[1]}</h1>";


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����, �������� ���������
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
  	 $message = $_POST['message'];
  	 $subject = $_POST['subject'];
  	 $method = $_POST['method'];

  	 if(false)
  	   $message = stripslashes($message);
  	 if(false)
  	   $subject = stripslashes($subject);

  	 if(empty($message))
  	   $errors[] =  $l_distrib[2];
  	 if(empty($subject))
  	   $errors[] =  $l_distrib[3];

    if(empty($errors))
  	 {
      $query = "SELECT email, login FROM {$gl_db_prefix}users WHERE subscribe = 'yes'";
      //print $query;
      $results = db_select($query);

      //���������
	     $headers  = "Content-type: text/plain; charset={$site_email_encoding}\r\n";
	     $headers .= "From: ".$_SERVER['SERVER_NAME']." <".$_SERVER['SERVER_ADMIN'].">\r\n";

      //������ ����������
	     $remove_link = "{$gl_site}?mod=users_edit_pub";
	     $message = str_replace("{remove_link}", $remove_link, $message);

      if($method == 'mail')
      {
		      if(is_array($results))
		      {
		        $cnt = count($results);
		        $count = 0;
		        for($i = 0; $i < $cnt; $i++)
		        {
		          $email   = stripslashes($results[$i]['email']);

		          send_email($email,
								               $site_title.' :: '.$subject,
								               $message,
								               $headers);
								     $count++;
		        }

          //echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$gl_site}?adm=distrib&amp;count={$count}&amp;mess=1'></HEAD></HTML>";
		        exit;

		      } else $errors[] = $l_distrib[4];
  	   }

      if($method == 'bcc')
      {
		      if(is_array($results))
		      {
		        $cnt = count($results);
		        $count = 0;
		        for($i = 0; $i < $cnt; $i++)
		        {
		          $email   = stripslashes($results[$i]['email']);
		          $headers.="Bcc: {$email}\r\n";
		          $count++;
		        }
		      } else $errors[] = $l_distrib[4];



			     //���������� ������, ��������� �� �������� � ������, ��� ��������� ��������� �� �������� ��������
					   if(empty($errors))
					   {
					     if(send_email($email,
								                $site_title.' :: '.$subject,
								                $message,
								                $headers))
								  {
		          echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$gl_site}?adm=distrib&amp;count={$count}&amp;mess=1'></HEAD></HTML>";
		          exit;
								  }
								  else
								  {
		          echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$gl_site}?adm=distrib&amp;mess=2'></HEAD></HTML>";
		          exit;
								  }
		  	   }
  	   }
  	 }
  }

  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //������� ���������
  $mess = intval($_GET['mess']);
  if(!empty($mess))
  {
  	 print "<br /><p class='Mustred'>";
  	 switch ($mess) {
      case 1: $count = intval($_GET['count']); print "{$l_distrib[5]} {$count}"; break;
      case 2: print $l_distrib[6]; break;

    }
  	 print "</p><br />";
  }

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('realty_homes_form', '', 'post', 'multipart');

  if(empty($message)) $message = $l_distrib[12];

  //���� ���������
		print work_template($form_lineobl_tpl, array("{caption}" => $l_distrib[7],
                                                 "{field}" => form_create_input("subject", 'SiteFInputM', $size ='') ));
  //���� ���������&trade;
  print work_template($form_lineobl_tpl, array("{caption}" => $l_distrib[8],
                                                 "{field}" => form_create_textarea("message", $rows = '25', $css = 'SiteFTextareaM')));

  //����� ��������
		print work_template($form_lineobl_tpl, array("{caption}" => $l_distrib[9],
                                                 "{field}" => form_create_select("method", "<option value='mail'>{$l_distrib[10]}</option><option value='bcc'>{$l_distrib[11]}</option>", 'SiteFInputM', $size ='') ));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));
  //������� ����
  //print form_create_hidden('id_tpl', $id_tpl);

  //����� �����
  print form_end();

  print "<h2>{$l_distrib[13]}</h2>";
  print "<p>{$l_distrib[14]}</p>";

?>