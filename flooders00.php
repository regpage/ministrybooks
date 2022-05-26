<?
include "flooders.inc.php";

$f=new Flooders("tmp/ban.txt");

$f->SetLogFileName("tmp/ban.log");
$f->Ban();
?>
