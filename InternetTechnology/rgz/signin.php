<!DOCTYPE html>
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf8">
<link rel="stylesheet" href="style.css">
<title>Dmitry's home page</title>
</head>

<body bgcolor="#ffffff" text="black" link="blue" alink="red" vlink="green">
<div class="logwin">

<?
function generateCode($length=6) {
    $chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPRQSTUVWXYZ0123456789";
    $code = "";
    $clen = strlen($chars) - 1;  
    while (strlen($code) < $length) {
            $code .= $chars[mt_rand(0,$clen)];  
    }
    return $code;
}

mysql_connect("localhost", "", "");
mysql_select_db("");
if(isset($_POST['submit'])) {
    $query = mysql_query("SELECT id, password FROM users WHERE login='".mysql_real_escape_string($_POST['login'])."' LIMIT 1");
    $data = mysql_fetch_assoc($query);
    if($data['password'] === md5(md5($_POST['password']))) {
        $hash = md5(generateCode(10));
        if(!@$_POST['not_attach_ip']) {
            $insip = ", ip=INET_ATON('".$_SERVER['REMOTE_ADDR']."')";
        }

        $query = "update users set hash='" . $hash . "'" . $insip . " where id='".$data['id']."'";
        mysql_query($query);

        setcookie("id", $data['id'], time()+60*60*24*30);
        setcookie("hash", $hash, time()+60*60*24*30);

        $login = $_POST['login'];
        $pass = $_POST['password'];                
        header("Location: http://server.com/index.html");
    } else {
        /*print "Invalid login or password!";*/
        header("Location: http://server.com/error.php");
    }
}
?>

<div class="top"><b>авторизация</b></div>
<div class="login">
<form action="signin.php" method="post" name="formlogin" target="_top">
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
    <td class="left"><br>
      <input type="checkbox" name="not_attach_ip"><code>не проверять IP</code>
    </td>
    <td class="right"><br><input name="submit" type="submit" value="войти"></td>
  </tr>

  <tr>
    <td colspan="2" class="center"></br>
      <a href="register.php" class="reglink">Зарегистрироваться?</a>
    </td>
  </tr>

  </table>
</form>

</div>

</body>
</html>
