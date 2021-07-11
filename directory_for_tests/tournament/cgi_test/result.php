#!/usr/bin/php

<html>
 <head>
  <title>CGI test</title>
</head>
<body>
<h2>Dynamically generated page.</h2>

<?php
parse_str(getenv("QUERY_STRING"), $_GET);
echo "<Your emain is: " . $_GET['email'] . "</h2>";
?>

</body>
</html>
