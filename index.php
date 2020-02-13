<?php 

require_once('header.php'); 

$modules = [
	'module1',
	'module2',
	'module3',
	'module4',
	'module5',
	'module6',
	'module7',
	'module8',
	'module9',
	'module10',
	'module11',
	'module12',
	'module13',
	'module14',
	'module15',
	'module16',
	'module17',
	'module18',
	'module19',
	'module20',
	'module21',
	'module22',
	'module23',
	'module24',
	'module25',
]

?>

<form action="/formHandler.php" method="get">
	
	<div class="row">
		
		<?php foreach($modules as $module){ ?>
			
		<div class="card" style="width: 7rem;" onclick="test(this)">
			<div class="card-body">
				<h5 class="card-title"><?php echo $module ?></h5>
				<input type="checkbox" name="<?php echo $module ?>" value="<?php echo $module ?>">Activate<br>
			</div>
		</div>
		
		<?php } ?>
			
	</div>
	<p id="sliderOutput">15</p>
	<div class="d-flex flex-column row slideContainer">
		<div class="d-flex justify-content-center row">
			<input type="range" class="slider" id="range" name="temps" min="10" max="120"><br>
		</div>
		
		<div class="d-flex justify-content-center row">
			<input type="submit" value = "submit">
		</div>
	</div>
</form>

<?php require_once('footer.php'); ?>
