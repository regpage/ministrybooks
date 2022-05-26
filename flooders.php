<?
include "flooders.inc.php";

$f=new Flooders("tmp/ban.txt");
$f->AddAlowAgent("StackRambler");
$f->AddAlowAgent("Googlebot");
$f->AddAlowAgent("YandexBot");
$f->AddAlowAgent("YandexMedia");
$f->AddAlowAgent("YandexImages");
$f->AddAlowAgent("YandexCatalog");
$f->AddAlowAgent("YandexDirect");
$f->AddAlowAgent("YandexBlogs");
$f->AddAlowAgent("YandexDirect");
$f->AddAlowAgent("YandexNews");
$f->AddAlowAgent("YandexPagechecker");
$f->AddAlowAgent("Yandex");
$f->AddAlowAgent("Aport");
$f->AddAlowAgent("msnbot");
$f->AddAlowAgent("FAST-WebCrawler");
$f->AddAlowAgent("Slurp/cat");
$f->AddAlowAgent("ASPseek/1.2.10");
$f->AddAlowAgent("CNSearch");
$f->SetLogFileName("bbd_tmpr/ban.log");
$f->Ban();
?>
