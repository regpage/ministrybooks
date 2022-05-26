  <?php
  ////////////////////////////////////////////////////////////////////
  //Модуль соединяет редактор EditArea с CMS
  ////////////////////////////////////////////////////////////////////
  ?>

  <?php if($gl_adm == 'tpl_text' || $gl_adm == 'stpl_edit' || $gl_adm == 'css_text' || $gl_adm == 'codesfragms_text') { ?>
			  <script language="javascript" type="text/javascript" src="<? echo $gl_admin_url  ?>mods/editarea/edit_area/edit_area_full.js"></script>
			  <script language="javascript" type="text/javascript">
  <?php } ?>

  <?php if($gl_adm == 'css_text') { ?>
					editAreaLoader.init({
						id : "css"		// textarea id
						,syntax: "css"			// syntax to be uses for highgliting
						,start_highlight: true		// to display with highlight mode on start-up
					});
  <?php } ?>

  <?php if($gl_adm == 'tpl_text') { ?>
					editAreaLoader.init({
						id : "tpl"		// textarea id
						,syntax: "html"			// syntax to be uses for highgliting
						,start_highlight: true		// to display with highlight mode on start-up
					});
  <?php } ?>

  <?php if($gl_adm == 'stpl_edit') { ?>
					editAreaLoader.init({
						id : "stpl"		// textarea id
						,syntax: "html"			// syntax to be uses for highgliting
						,start_highlight: true		// to display with highlight mode on start-up
					});
  <?php } ?>

  <?php if($gl_adm == 'codesfragms_text') { ?>
  	editAreaLoader.init({
						id : "codesfragms"		// textarea id
						,syntax: "html"			// syntax to be uses for highgliting
						,start_highlight: true		// to display with highlight mode on start-up
					});
   <?php } ?>

			<?php if($gl_adm == 'tpl_text' || $gl_adm == 'stpl_edit' || $gl_adm == 'css_text' || $gl_adm == 'codesfragms_text') { ?>
			</script>
   <?php } ?>