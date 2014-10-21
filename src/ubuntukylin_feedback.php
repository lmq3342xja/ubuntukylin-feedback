<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>优麒麟意见和建议反馈</title>
<?php
$con = mysql_connect('localhost', 'root');
/************************在数据库中创建表*************************/
if (!$con) {
    die ('连接服务器出错: ' . mysql_error());
}
$database="feedback_db";
$sqlDatabase = 'create database '.$database;
if(mysql_query($sqlDatabase, $con))
{
echo "恭喜你，数据库".$database."创建成功了!";
}
else
{
echo   "创建数据库出错，错误号：".mysql_errno()." 错误原因：".mysql_error();
}
/******************************end***************************************/
/************************在数据库中创建表*************************/
mysql_select_db("feedback_db",$con);  
$FeedbackTable="create   table   feedback_table(    
name   varchar(20),  
email   varchar(20),  
location varchar(20),
telephone varchar(20),
suggestion varchar(2048)
)";  

if(mysql_query($FeedbackTable))
{
echo "恭喜你，数据表创建成功了!";
}
else
{
echo "创建数据表出错，错误号：".mysql_errno()." 错误原因：".mysql_error();
}

/******************************end***************************************/
mysql_close();


/**************************接收post请求插入数据****************************/
if (isset($_POST['name'])&&isset($_POST['email'])&&isset($_POST['suggestion']))
{   /*
     mysql_select_db("feedback_db", $con);
     mysql_query("INSERT INTO feedback_table (name,email,location,telephone,suggestion) 
     VALUES ($_POST['name'],$_POST['email'],$_POST['location'],$_POST['telephone'],
     $_POST['suggestion']);	*/	
}

?>		

</body>
</html>
