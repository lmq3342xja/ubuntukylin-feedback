<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>反馈主页</title>
</head>
<link rel="stylesheet" type="text/css" href="css/style.css"/>
<body>
<div id="s_top"></div>
<div id="s_center">
  <div class="s_center1">

<h3><a href="" target="_self">首页</a> &gt;&nbsp;建议查看</h3>
<?php
session_start();	 

$con = mysql_connect("localhost","root","1");
if (!$con)
  {
  die('Could not connect: ' . mysql_error());
  }
//mysql_select_db() 函数选取数据库
mysql_select_db("feedback_db", $con);
mysql_query("set names utf8");  
if (isset($_POST['action']) && $_POST['action'] == "add")
{	
	date_default_timezone_set("Asia/Shanghai");//修正时间为中国准确时间
	$time=date("Y-m-d H:i:s");//将时间赋值给变量$time
	mysql_query("UPDATE feedback SET solve_time = '".$time."' WHERE create_time_int = '".$_POST[create_time_int]."'");	
}
//将表中数据读取出来

$result = mysql_query("SELECT count( * ) FROM feedback");
$total = 0;
while($row = mysql_fetch_array($result))
{ 
	$total = $row[0];
}

$total_page = 0;
if ($total%5 == 0)
	$total_page = (int)($total / 5);
else
	$total_page = (int)($total / 5 + 1);

$page = @$_GET["page"];
if (!isset($page))
	$page = 0;
if ($page < 0)
	$page = 0;

if ($page >= $total_page)
	$page = $total_page - 1;

echo "<div class='msg_look' id='msg_look'>";

$start = $page * 5;

$result = mysql_query("SELECT * FROM feedback order by create_time_int desc LIMIT $start, 5");

while($row = mysql_fetch_array($result))
  { 
	if($row['solve_time']=="")
	{
		$submit = 'submit';	
	}	
	else
	{
		$submit = 'hidden';
	}
	 echo "<p class='m_p'>姓名：".$row['name']." 　　邮箱：".$row['email']." 　所在地：".$row['location']."　联系电话：".$row['telephone']." 　　提交时间：".$row['create_time']." 　　解决时间：".$row['solve_time']." 　　 
	<td>
		<form action='display_feedback.php' method='post'  name='form1' id='form1'>
		<td><label>
              		<input type=".$submit." name='Submit' value='标记为已解决' />
              		<input name='action' type='hidden' id='action' value='add' />
              		<input name='create_time_int' type='hidden'  value=".$row['create_time_int']." />
            	</label></td>
		</form>
	</td>
	       </p>";
    	 echo "<p class='m_pc'>意见和建议：<br/> 　　<span>".$row['suggestion']."</span></p><br/><hr>";
}

mysql_close($con);

?>
</div>

 <div id="pages" style="font-size:12px; width:100%; line-height:40px; text-align:center; margin-top:20px">
 <b>共<?=$total_page?>页</b> 
 <?php
 for($i = 0; $i < $total_page; $i ++)
 	echo "<a href=\"display_feedback.php?page=".$i."\">第".($i + 1)."页</a> ";

 	echo " <a href=\"display_feedback.php?page=".($page - 1)."\">上一页</a>  <a href=\"display_feedback.php?page=".($page + 1)."\">下一页</a>";

 ?>
 </div>
</body>
</html>
