var slider = document.getElementById("range");

var output = document.getElementById("sliderOutput");

output.innerHTML = slider.value;

slider.oninput = function()
{
	output.innerHTML = this.value;
}

function activate(element)
{
	var checked = document.querySelectorAll("input[type=checkbox]:checked");
	
	var unchecked = document.querySelectorAll("input[type=checkbox]");
	
	unchecked.forEach((item) => {
		item.parentNode.style.backgroundColor = '#F0FFFF';
	});
	
	checked.forEach((item) => {
		item.parentNode.style.backgroundColor = '#4CAF50';
	});
}

