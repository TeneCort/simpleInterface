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
		exec($cmd . " > /dev/null &");
	}
}

foreach($_GET as $module)
{
	echo $module . ' is active <br>';
}
if (isset($_GET['module1']))
{
	execInBackground('lxterminal');
}
?>
<button><a href="index.php">Index</a></button>

<?php require_once('footer.php'); ?>
