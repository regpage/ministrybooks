<?php
//print "<div id='rounded-box-3'>
		//<b class='r3'></b><b class='r1'></b><b class='r1'></b>
		//<div class='inner-box'>";
  //////////////////////////////////////////////////////////////////////////////
print "<table width='100%' cellspacing='0' cellpadding='0' border='0' class='bt1'>";

    print "<tr>";
      //print "<td><h1>{$l_leftcol[23]}</h1></td>";
      print "<td><img src='css/admin/images/menu.gif'></td>";
    print "</tr>";
 
    print "<tr>";
      print "<td><a href='index.cfm'>{$l_leftcol[1]}</a></td>";
    print "</tr>";
    print "<tr>";
      if(strpos($gl_adm, 'main') !== false)
        print "<td>{$l_leftcol[22]}</td>";
      else
        print "<td><a href='?adm=main'>{$l_leftcol[22]}</a></td>";
     print "</tr>";

    print "<tr>";
      if(strpos($gl_adm, 'parts_') !== false && $gl_adm != 'parts_pages_search')
        print "<td>{$l_leftcol[2]}</td>";
      else
        print "<td><a href='?adm=parts_list'>{$l_leftcol[2]}</a></td>";
    print "</tr>";
 if($_SESSION["{$gl_site_name}_gl_id_user"]== 2){
    print "<tr>";
      if($gl_adm == 'parts_pages_search')
        print "<td>{$l_leftcol[3]}</td>";
      else
        print "<td><a href='?adm=parts_pages_search'>{$l_leftcol[3]}</a></td>";
    print "</tr>";
   
    print "<tr>";
      if(strpos($gl_adm, 'tpl_') !== false && strpos($gl_adm, 'stpl_') === false)
        print "<td>{$l_leftcol[4]}</td>";
      else
        print "<td><a href='?adm=tpl_list'>{$l_leftcol[4]}</a></td>";
    print "</tr>";
  
    print "<tr>";
      if(strpos($gl_adm, 'menu_') !== false)
        print "<td>{$l_leftcol[5]}</td>";
      else
        print "<td><a href='?adm=menu_list'>{$l_leftcol[5]}</a></td>";
    print "</tr>";

    print "<tr>";
      if(strpos($gl_adm, 'users_') !== false)
        print "<td>{$l_leftcol[6]}</td>";
      else
        print "<td><a href='?adm=users_list'>{$l_leftcol[6]}</a></td>";
    print "</tr>";
     

    print "<tr>";
      if(strpos($gl_adm, 'stpl_') !== false)
        print "<td>{$l_leftcol[8]}</td>";
      else
        print "<td><a href='?adm=stpl_edit'>{$l_leftcol[8]}</a></td>";
    print "</tr>";

    print "<tr>";
      if(strpos($gl_adm, 'css_') !== false)
        print "<td>{$l_leftcol[9]}</td>";
      else
        print "<td><a href='?adm=css_list'>{$l_leftcol[9]}</a></td>";
    print "</tr>";

    print "<tr>";
      if(strpos($gl_adm, 'settings') !== false)
        print "<td>{$l_leftcol[10]}</td>";
      else
        print "<td><a href='?adm=settings'>{$l_leftcol[10]}</a></td>";
    print "</tr>";
  
    print "<tr>";
      if(strpos($gl_adm, 'codesfragms_') !== false)
        print "<td>{$l_leftcol[12]}</td>";
      else
        print "<td><a href='?adm=codesfragms_list'>{$l_leftcol[12]}</a></td>";
    print "</tr>";
  
    print "<tr>";
      if(strpos($gl_adm, 'distrib')!== false)
        print "<td>{$l_leftcol[19]}</td>";
      else
        print "<td><a href='?adm=distrib'>{$l_leftcol[19]}</a></td>";
    print "</tr>";

    print "<tr>";
      if(strpos($gl_adm, 'regform_fields') !== false)
        print "<td>{$l_leftcol[21]}</td>";
      else
        print "<td><a href='?adm=regform_fields_list'>{$l_leftcol[21]}</a></td>";
    print "</tr>";
    //
		  //if($gl_is_main_site == 'yes')
    {
		    print "<tr>";
		      if(strpos($gl_adm, 'mods_') !== false)
		        print "<td>{$l_leftcol[13]}</td>";
		      else
		        print "<td><a href='?adm=mods_list'>{$l_leftcol[13]}</a></td>";
		    print "</tr>";
    }

    print "<tr>";
      if(strpos($gl_adm, 'letters_') !== false)
        print "<td>{$l_leftcol[20]}</td>";
      else
        print "<td><a href='?adm=letters_edit'>{$l_leftcol[20]}</a></td>";
    print "</tr>";

    print "<tr>";
      if(strpos($gl_adm, 'url_') !== false)
        print "<td>{$l_leftcol[14]}</td>";
      else
        print "<td><a href='?adm=url_list'>{$l_leftcol[14]}</a></td>";
    print "</tr>";
}
else
{
print "";
}

    if(file_exists("{$gl_path_to_root}config/site_is_locked.inc"))
      print "<td><a href='?act=open_site' title='{$l_leftcol[17]}'><span class='Mustred'><b>{$l_leftcol[15]}</b></span></a></td>";
    else
      print "<td><a href='?act=lock_site' title='{$l_leftcol[18]}'>{$l_leftcol[16]}</a></td>";
  
print "<tr>";
      if(strpos($gl_adm, 'auth_exit') !== false)
        print "<td>{$l_admmain[27]}</td>";
      else
        print "<td><a href='?act=auth_exit'  title='{$l_leftcol[27]}'>{$l_admmain[27]}</a></td>";
    print "</tr>";
  print "</table>";
 // print "</div>
		//<b class='r1'></b><b class='r1'></b><b class='r3'></b>
	//</div>";
?>
