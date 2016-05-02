<?php

  //$_SESSION['id'] = '';
  setCookie("id", '', 0);
  setCookie("hash", '', 0);

  Header('WWW-Authenticate: Basic realm="protected area"');
  Header('HTTP/1.0 401 Unauthorized');

  $_SERVER['PHP_AUTH_USER'] = "";
  $_SERVER['PHP_AUTH_PW'] = "";

  header("Location: index.html");  
  exit;

?>
