#!/usr/bin/php

<html>
 <head>
  <title>CGI test</title>
</head>
<body>
<h2>Dynamically generated page.</h2>

<?php
echo "<h2>Your email is: ". $_POST['email'] . "</h2>";
?>

</body>
</html>

<!-- parse_str(getenv("QUERY_STRING"), $_GET);
echo "<h2><p>Now we know your emain is: </p><p>" . $_GET['email'] . "</p></h2>; -->
