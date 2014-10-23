<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>优麒麟意见和建议反馈</title>
<?php
// every page needs to start with these basic things 

// I'm using a separate config file. so pull in those values 
require("include/config.inc.php"); 

// pull in the file with the database class 
require("include/Database.class.php"); 

// create the $db object 
$db = new Database(DB_SERVER, DB_USER, DB_PASS, DB_DATABASE); 

// connect to the server 
$db->connect();
/**************************接收post请求插入数据****************************/
if (isset($_POST['name'])&&isset($_POST['email'])&&isset($_POST['suggestion']))
{   
// your main code would go here 
	
	$data['name'] = $_POST['name'];
	$data['email'] = $_POST['email'];
	$data['location'] = $_POST['location'];
	$data['telephone'] = $_POST['telephone'];
	$data['suggestion'] = $_POST['suggestion'];
	date_default_timezone_set("Asia/Shanghai");//修正时间为中国准确时间
	$time=date("Y-m-d H:i:s");//将时间赋值给变量$time
	$data['create_time'] = $time;
	$data['create_time_int'] = time();
	$data['solve_time'] = "";
	$db->query_insert("feedback", $data);	
echo $data['name'];
echo $data['location'];
}
// and when finished, remember to close connection 
$db->close();

?>		
</body>
</html>
