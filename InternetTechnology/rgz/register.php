<!DOCTYPE html>
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf8">
<link rel="stylesheet" href="style.css">
<title>Register | Dmitry's home page</title>
</head>

<body bgcolor="#ffffff" text="black" link="blue" alink="red" vlink="green">

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

<div class="logwin">

<div class="top"><b>регистрация</b></div>
<div class="login">
<form action="regev.php" method="post" name="formlogin">
  <table class="center">
  <tr>
    <td colspan="2" class="right">
      <code>логин</code><br>
      <input class="bord" type="text" name="login">
    </td>
  </tr>
  <tr>
    <td colspan="2" class="right">
      <code>пароль</code><br>
      <input class="bord" type="password" name="password" size="23">
    </td>
  </tr>

  <tr>
    <td colspan="2" class="right">
      <code>пароль еще раз</code><br>
      <input class="bord" type="password" name="password2" size="23">
    </td>
  </tr>
            
  <tr>
    <td class="left"><br>
      <input type="checkbox" name="not_attach_ip"><code>не проверять IP</code>
    </td>
    <td class="right"><br><input name="submit" type="submit" value="далее"></td>
  </tr>  

  </table>
</form>

</div>

<?
    } else {
    header("Location: http://server.com/main.php");
?>

<?

    }
} else {
    
    /* again */
?>
    <div class="logwin">

<div class="top"><b>регистрация</b></div>
<div class="login">
<form action="regev.php" method="post" name="formlogin" target="_top">
  <table class="center">
  <tr>
    <td colspan="2" class="right">
      <code>логин</code><br>
      <input class="bord" type="text" name="login">
    </td>
  </tr>
  <tr>
    <td colspan="2" class="right">
      <code>пароль</code><br>
      <input class="bord" type="password" name="password" size="23">
    </td>
  </tr>

  <tr>
    <td colspan="2" class="right">
      <code>пароль еще раз</code><br>
      <input class="bord" type="password" name="password2" size="23">
    </td>
  </tr>
            
  <tr>
    <td class="right"><br><input name="submit" type="submit" value="далее"></td>
  </tr>  

  </table>
</form>

</div>
<?

}
?>

</body>
</html>
