<?php
require_once('header.php');

function execInBackground($cmd)
{
	if (substr(php_uname(), 0, 7) == "Windows")
	{
		pclose(popen("stat /B " . $cmd, "r"));
	}
	else
	{
		shell_exec($cmd . ' ' . escapeshellarg('/home/pi/Desktop/test/test.py') . " > /dev/null &");
	}
}

echo 'active modules : <br>';

// loop that iterates and displays selected modules
foreach($_GET as $module)
{	
	
	if ($module != $_GET['temps'])
	{
		echo $module . '<br>';
	}
	else
	{
		echo 'game duration : ' . $module . ' minutes <br>';
	}
	
}

// for testing
if (isset($_GET['module1']))
{
	execInBackground('python3');
}
?>

<!-- Some HTML -->
<a href="index.php" class="btn btn-primary">Index</a>

<?php require_once('footer.php'); ?>
