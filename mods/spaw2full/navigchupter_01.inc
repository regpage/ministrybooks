<?php
$url = "{ed_page_preview_href}";
$ch=array({Arr});
$var_name="part";
print "{$l_menu[8]}";
print "<a {$l_menu[7]} href='{$url}&{$var_name}=1'>$l_menu[5]</a><br/>";
print "</div>";
print "{$l_menu[9]}";
print "<b>$l_menu[4]</b><br/><br/>

&nbsp; ";
$count=0;
$j = 1;
for($i=0; $i<count($ch); $i++)
 {
$part = $i + 1;
$text_r = "<a {$l_menu[7]} href='{$url}&{$var_name}={$ch[$i]}'>$part</a>&nbsp;|&nbsp; "; 
$text = "{$text}{$text_r}";
$len = strlen($text);
$count++;
}   
print "{$text}";
print "</div>";
print "{$l_menu[6]}";
?>