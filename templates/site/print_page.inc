<html>
<head>
  <title><?php print $site_title; ?></title>
  <link rel="stylesheet" href="css/main.css"   type="text/css" />
  <link rel="stylesheet" href="css/format.css" type="text/css" />
  <?php setmeta($gl_page, $site_keywords, $site_descr) ?>
</head>
<body>
  <?php include("{$gl_path_to_engine}public/content.inc"); ?>
</body>
</html>