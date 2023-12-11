<?php
  //////////////////////////////////////////////////////////////////////////////
  //CMS Ortus
  //������ ��������� �����-��������, �� ����� ��� ����
  //////////////////////////////////////////////////////////////////////////////
?>
<?php
session_start();

$img_x          = 80;   //������ �����������, �� ���������-100
$img_y          = 26;   //������ �����������, �� ���������-30
$num_n          = 5;    //����� ����, default-4
$font_min_size  = 12;   //����������� ������ ������, �� ���������-12
$lines_n_max    = 4;    //������������ ����� ������� �����, �� ���������-2
$nois_percent   = 8;    //������������� ������� ���� � ������, � ���������, �� ���������-3
$angle_max      = 18;   //������������ ���� ���������� �� ����������� �� ������� ������� � ������, �� ���������-20

//$font_arr=glob(dirname(__FILE__)."/fonts/*.ttf");

$im=imagecreate($img_x, $img_y);
//������� ����������� �����
$text_color = imagecolorallocate($im, 0, 0, 0);       //���� ������
$nois_color = imagecolorallocate($im, 0, 0, 0);       //���� ����������� ����� � �����
$img_color  = imagecolorallocate($im, 255, 255, 255); //���� ����
//�������� ����������� ������� ������
imagefill($im, 0, 0, $img_color);
//� ���������� $number ����� ��������� �����, ���������� �� �����������
$number='';

for ($n=0; $n<$num_n; $n++){
    $num=rand(0,9);
    $number.=$num;
    $font_size=rand($font_min_size, $img_y/2);
    $angle=rand(360-$angle_max,360+$angle_max);

    $font_cur="ttf/verdana.ttf";
    //s$font_cur=$font_arr[$font_cur];
    //���������� ��������� ��� ������ �����, ������� ������������ ���������� �����������
    //��� ����� ��������� �������� ����� � �����������
    $y=rand(($img_y-$font_size)/4+$font_size, ($img_y-$font_size)/2+$font_size);

    $x=rand(($img_x/$num_n-$font_size)/2, $img_x/$num_n-$font_size)+$n*$img_x/$num_n;

    imagettftext($im, $font_size, $angle, $x, $y, $text_color, $font_cur, $num);
};



//��������� ����� "�����������" ��������
$nois_n_pix=round($img_x*$img_y*$nois_percent/100);
//��������� ����������� ��������� ����� ������
for ($n=0; $n<$nois_n_pix; $n++){
    $x=rand(0, $img_x);
    $y=rand(0, $img_y);
    imagesetpixel($im, $x, $y, $nois_color);
};
//��������� ����������� ��������� �������� �����
for ($n=0; $n<$nois_n_pix; $n++){
    $x=rand(0, $img_x);
    $y=rand(0, $img_y);
    imagesetpixel($im, $x, $y, $img_color);
};

$lines_n=rand(0,$lines_n_max);
//�������� "�����������" ����� ����� ������
for ($n=0; $n<$lines_n; $n++){
    $x1=rand(0, $img_x);
    $y1=rand(0, $img_y);
    $x2=rand(0, $img_x);
    $y2=rand(0, $img_y);
    imageline($im, $x1, $y1, $x2, $y2, $nois_color);
};

Header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
Header("Last-Modified: ".gmdate("D, d M Y H:i:s")."GMT");
Header("Cache-Control: no-cache, must-revalidate");
Header("Pragma: no-cache");

header("Content-type: image/png");
imagepng($im);
imagedestroy($im);

//� ���������� $number �������� �����, ���������� �� �����������
$_SESSION['corr_img_code'] = $number;
?>