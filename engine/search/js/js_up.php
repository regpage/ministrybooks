<script>
jQuery(document).ready(function ($) {
    $(window).load(function () {
        setTimeout(function(){
            $('#preloader').fadeOut('slow', function () {
            });
        },0);
    });
    // включить Логику И ИЛИ если более одного слова в запросе    
    $("input[name='template']").on("input", function () {
      search_logic_control();
    });
    // проверка при старте страницы
    search_logic_control();

    $("input[name='template']").attr("max", 128);

    function search_logic_control() {
      let template_check = $("input[name='template']").val().trim();
      template_check = template_check.split(" ");
      if (template_check.length > 1) {
        $("select[name='logic']").attr("disabled", false);
      } else {
        $("select[name='logic']").attr("disabled", true);
      }
    }
});
</script>