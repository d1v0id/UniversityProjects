<!DOCTYPE html>
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf8">
<link rel="stylesheet" href="style.css">
<title>Dmitry's home page</title>
</head>

<body bgcolor="#f8f8f8" text="black" link="blue" alink="red" vlink="green" style="margin: 0px; padding: 0px;">
	<!--<img src="images/logo.jpg" alt="logo" style="float: left; margin: 0px">
	<div id=>
		<a href="#"><img id="buttons" src="images/silver_img_about_me.jpg"></a>
		<a href="#"><img id="buttons" src="images/silver_img_blog.jpg"></a>
		<a href="#"><img id="buttons" src="images/silver_img_github.jpg"></a>
		<a href="#"><img id="buttons" src="images/silver_img_portfolio.jpg"></a>
	</div>-->

<div id="head_wrapper">
  <div id="head">
    <div class="head_container">
      <img src="images/logo.jpg" alt="logo" class="leftimg">
      <div id="my_logo">TOOULSG</div>
      <div id="my_logo_small">
        Коннов Дмитрий <font id="term_carret">||</font>
      </div>
    </div>
  </div>
  <div id="sticky_navigation_wrapper">
    <div id="sticky_navigation">
      <div class="head_container">
        <ul>
          <li><a href="main.php" target="main">БЛОГ</a></li>
          <li><a href="#">АРХИВ</a></li>
          <li><a href="http://server.com/git" target="_blank">GIT</a></li>

<?
mysql_connect("localhost", "", "");
mysql_select_db("");
if (isset($_COOKIE['id']) and isset($_COOKIE['hash'])) { 
    $query = mysql_query("SELECT *,INET_NTOA(ip) FROM users WHERE id = '".intval($_COOKIE['id'])."' LIMIT 1");
    $userdata = mysql_fetch_assoc($query);

    if(($userdata['hash'] != $_COOKIE['hash']) or ($userdata['id'] != $_COOKIE['id']) or (($userdata['ip'] != ip2long($_SERVER['REMOTE_ADDR'])) and ($userdata['ip'] != "0"))) {
        setcookie("id", "", time() - 3600*24*30*12, "/");
        setcookie("hash", "", time() - 3600*24*30*12, "/");
        ?>
          <li><a href="signin.php" target="main">ВОЙТИ</a></li>
        <?
    } else {
  
?>

          <li><a href="exitev.php" target="_top">ВЫХОД</a></li>

<?

    }
} else {    
    ?>
    <li><a href="signin.php" target="main">ВОЙТИ</a></li>
    <?
}
?>

        </ul>        
      </div>
    </div>
  </div>
</div>

</body>
</html>
