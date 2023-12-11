<?php $query = "SELECT `site_title` FROM {$gl_db_prefix}settings WHERE id = 1"; $site_title = stripslashes(db_select_one($query)); ?>
<h1><?php echo $l_admmain[1]; ?></h1>
<h2><a href="<? echo $gl_site ?>?adm=parts_list"><a href="http://ministrybooks.ru/index.cfm"><?php echo $l_admmain[2]; ?> : <?php echo $site_title ?></a></a></h2>
<h2><a href="<? echo $gl_site ?>?adm=parts_list"><?php echo $l_admmain[3]; ?></a></h2>
<p><?php echo $l_admmain[4]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=tpl_list' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[5]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[6]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=menu_list' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[7]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[8]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=users_list' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[9]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[10]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=stpl_edit' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[13]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[14]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=css_list' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[15]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[16]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=settings' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[17]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[18]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=codesfragms_list' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[21]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[22]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=mods_list' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[23]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[24]; ?></p>
<h2><a href="<? if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $gl_site.'?adm=url_list' ?>"><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[25]; ?></a></h2>
<p><?php if($_SESSION["{$gl_site_name}_gl_id_user"]== 2)echo $l_admmain[26]; ?></p>
