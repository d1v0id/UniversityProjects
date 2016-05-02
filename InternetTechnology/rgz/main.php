<!DOCTYPE html>
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf8">
<link rel="stylesheet" href="style.css">
<title>Dmitry's home page</title>
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
      header("Location: signin.php"); exit();
    } else {
  
?>

<div class="content">
  <div class="blog_item">    
    <div class="blog_title">
      Linux local root exploit (2.6.37 - 3.8.10)
    </div>

    <div class="blog_text">
      <p>
        Compile: gcc-4.7 -O2 exploit.c -o getroot<br>
        #define _GNU_SOURCE 1<br>
        #include &ltstdint.h&gt<br>        
      </p>
    </div>

    <div class="blog_info">
      dmitry в 03:38 PM 05/16/13
      <a href="#" id="text4_2">
        <font class="text_alink">читать</font>
      </a>      
    </div>    
  </div>

  <div class="blog_item">    
    <div class="blog_title">
      Clone OTRS to another server
    </div>

    <div class="blog_text">
      <p>
        For clone all otrs settings and tickets from one server to another I connect to my old otrs server and type:<br>
        &nbsp&nbsp&nbsp&nbsp$ cd /opt/otrs/scripts<br>
        &nbsp&nbsp&nbsp&nbsp$ sudo ./backup.pl -d &ltdirectory-for-backup&gt -t fullbackup<br>
      </p>
    </div>

    <div class="blog_info">
      dmitry в 01:56 PM 05/16/13
      <a href="#" id="text3_2">
        <font class="text_alink">читать</font>
      </a>
    </div>    
  </div>

  <div class="blog_item">    
    <div class="blog_title">
      Parallel computing in home cluster
    </div>

    <div class="blog_text">
      <p>
        I did it in debian.<br>
        1) Install ssh: sudo apt-get install ssh<br>
        2) Install on all nodes mpich2: sudo apt-get install mpich2<br>
      </p>
    </div>

    <div class="blog_info">
      dmitry в 01:24 PM 05/16/13
      <a href="#" id="text2_2">
        <font class="text_alink">читать</font>
      </a>
    </div>    
  </div> 

  <div class="blog_item">    
    <div class="blog_title">
      BSOD in Windows7/8 after six lines of code
    </div>

    <div class="blog_text">
      <p>
        #include &ltwindows.h&gt<br>
        int main() {<br>
        &nbsp&nbsp&nbsp&nbspHDC dc = CreateCompatibleDC (NULL);<br>
      </p>
    </div>

    <div class="blog_info">
      dmitry в 01:01 PM 05/16/13
      <a href="#" id="text1_2">
        <font class="text_alink">читать</font>
      </a>      
    </div>    
  </div>
</div>

<?

    }
} else {
    header("Location: signin.php"); exit();
}
?>

</body>
</html>
