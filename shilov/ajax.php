<?php
header("Content-Type: text/plain; charset=utf-8");
$filename = 'location.txt';
if (isset($_GET['set']))
{
    file_put_contents ($filename, $_GET['set']);
	file_get_contents('https://shilov.org/reading/ajax.php?set='.urlencode($_GET['set']));
}
else
    echo file_get_contents ($filename);