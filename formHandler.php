<?php
require_once('header.php');

$activeModules = [];

// function that parses $_GET arguments received from the web interface into a shell command.
function execInBackground($cmd, $file, $modules)
{
	$cmd = $cmd . ' ' . escapeshellarg($file) . ' ';
	
	foreach($modules as $module)
	{
		$cmd = $cmd . escapeshellarg($module) . ' ';
	}
	
	$cmd = $cmd . "> /dev/null &";

	shell_exec($cmd);
}

// loop that iterates and displays selected modules
echo 'active modules : <br>';
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

// call our function passing all the GET variables
execInBackground('python3', '/home/pi/Desktop/test/test.py', $_GET);

?>

<!-- Return to index -->
<a href="index.php" class="btn btn-primary">Index</a>

<?php require_once('footer.php'); ?>
