<?php require_once('header.php'); ?>

<form action="/formHandler.php" method="get">
	<input type="checkbox" name="module1" value="module1">Module 1<br>
	<input type="checkbox" name="module2" value="module2">Module 2<br>
	<input type="checkbox" name="module3" value="module3">Module 3<br>
	<input type="checkbox" name="module4" value="module4">Module 4<br>
	<input type="checkbox" name="module5" value="module5">Module 5<br>
	<input type="checkbox" name="module6" value="module6">Module 6<br>
	<input type="range" name="temps" min="10" max="120"><br>
	<input type="submit" value = "submit">
</form>

