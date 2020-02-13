var slider = document.getElementById("range");

var output = document.getElementById("sliderOutput");

output.innerHTML = slider.value;

slider.oninput = function()
{
	output.innerHTML = this.value;
}

function test(element)
{
	var checked = document.querySelectorAll("input[type=checkbox]:checked");
	
	var unchecked = document.querySelectorAll("input[type=checkbox]");
	
	unchecked.forEach((item) => {
		item.parentNode.style.backgroundColor = 'red';
	});
	
	checked.forEach((item) => {
		item.parentNode.style.backgroundColor = 'green';
	});
}

