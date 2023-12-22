<?php
if(empty($tpl)) {
    echo "<script>
           document.getElementById('resultalert').innerHTML = '<strong>Введите, пожалуйста, ключевые слова.</strong>';
              setTimeout(function() { document.getElementById('resultalert').style.display = 'none'; }, 8000); </script>";
    return;
} else {
    if (mb_strlen(trim($tpl), 'utf-8') < 3) {
        echo "<script>document.getElementById('resultalert').innerHTML = '<strong>Слишком короткий поисковый запрос, меньше 3 символов.</strong>';
        setTimeout(function() { document.getElementById('resultalert').style.display = 'none';}, 8000);</script>";

        unset($_SESSION['template']);
        return;
    } else if (mb_strlen(trim($tpl), 'utf-8') > 128) {
        echo "<script>document.getElementById('resultalert').innerHTML = '<strong>Слишком длинный поисковый запрос, больше 128 символов.</strong>';
                    setTimeout(function() { document.getElementById('resultalert').style.display = 'none';}, 8000);</script>";
        unset($_SESSION['template']);
        return;
      } else if (in_array(mb_strtolower($tpl, 'utf-8'), $noise_words)) {
        echo "<script>document.getElementById('resultalert').innerHTML = '<strong>Слово относится к Стоп-словам</strong>';
                   setTimeout(function() { document.getElementById('resultalert').style.display = 'none';}, 8000);</script>";
        unset($_SESSION['template']);
        return;
    }
}