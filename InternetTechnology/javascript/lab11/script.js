var i;
var array1 = new Array(10); // массив чисел

function Update() {
	document.form1.reset();
	for (i = 1; i < 11; i++) {
		array1[i] = Math.floor(Math.random() * (999 - 100 + 1)) + 100;
		document.form1.elements["textArr" + i].value = array1[i];
	}
}

function Sort() {
	array1.sort(function(a,b){return a - b});
	for (i = 1; i < 11; i++) {
		document.form1.elements["sortArr" + i].value = array1[i];
	}
}
