<?php
require_once('header.php');

$activeModules = [];

function execInBackground($cmd, $file, $modules)
{
	$cmd = $cmd . ' ' . escapeshellarg($file) . ' ';
	
	foreach($modules as $module)
	{
		$cmd = $cmd . escapeshellarg($module) . ' ';
	}
	
	$cmd = $cmd . "> /dev/null &";
	echo '<br>' . $cmd . '<br>';
	shell_exec($cmd);
}

echo 'active modules : <br>';

// loop that iterates and displays selected modules
foreach($_GET as $module)
{	
	if ($module != $_GET['temps'])
	{
		echo $module . '<br>';
		array_push($activeModules, $module);
	}
	else
	{
		echo 'game duration : ' . $module . ' minutes <br>';
	}
}

// for testing

execInBackground('python3', '/home/pi/Desktop/test/test.py', $_GET);

?>

<!-- Some HTML -->
<a href="index.php" class="btn btn-primary">Index</a>

<?php require_once('footer.php'); ?>
