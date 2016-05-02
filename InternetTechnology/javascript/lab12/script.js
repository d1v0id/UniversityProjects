var i, k; // счетчики
var array1 = new Array(10); // массив чисел
var historyArray = new Array(40);

function arrayGenerate() {
	for (i = 0; i < 10; i++) {
		array1[i] = Math.floor(Math.random() * (999 - 100 + 1)) + 100;
		/*document.form1.elements["textArr" + i].value = array1[i];*/
	}

	array1.sort(function(a,b){return a - b});

	for (i = 0; i < 10; i++) {
		document.form1.elements["textArr" + i].value = array1[i];
	}
}

function tableCreate() {
	form2.removeChild(form2.lastChild);
	var dstForm= document.getElementsByName("form2")[0];
	var tbl = document.createElement("table");
	var tblBody = document.createElement("tbody");

	var hrow = document.createElement("tr");
	var hcell = document.createElement("td");    
	var hcellText = document.createTextNode("Low");
	hcell.appendChild(hcellText);
	hrow.appendChild(hcell);
	hcell = document.createElement("td");    
	hcellText = document.createTextNode("High");
	hcell.appendChild(hcellText);
	hrow.appendChild(hcell);
	hcell = document.createElement("td");
	hcellText = document.createTextNode("Medium");
	hcell.appendChild(hcellText);
	hrow.appendChild(hcell);
	hcell = document.createElement("td");
	hcellText = document.createTextNode("A[medium]");
	hcell.appendChild(hcellText);
	hrow.appendChild(hcell);
	tblBody.appendChild(hrow);

	for (var j = 0; j <= ((k - 4) / 4); j++) {
	    var row = document.createElement("tr");
	    for (var i = 0; i < 4; i++) {
		var cell = document.createElement("td");    
		var cellText = document.createTextNode(historyArray[j * 4 + i]); 
		cell.appendChild(cellText);
		row.appendChild(cell);
	    }
	    tblBody.appendChild(row);
	}

	tbl.appendChild(tblBody);
	dstForm.appendChild(tbl);
	tbl.setAttribute("class", "FlatTable");

	var cap = tbl.createCaption();
	cap.innerHTML = "<font class=\"FlatFont\">Промежуточные результаты</font>";
}

function binarySearch(value) {
	k = 0;
	var startIndex = 0,
	    stopIndex = array1.length - 1,
	    middle = Math.floor((stopIndex + startIndex) / 2);

	while (array1[middle] != value && startIndex < stopIndex) {
		if (value < array1[middle]){
		    stopIndex = middle - 1;
		} else if (value > array1[middle]){
		    startIndex = middle + 1;
		}
		middle = Math.floor((stopIndex + startIndex) / 2);
		historyArray[k] = startIndex;
		historyArray[k + 1] = stopIndex;
		historyArray[k + 2] = middle;
		historyArray[k + 3] = array1[middle];
		k += 4;	
	}

	return (array1[middle] != value) ? -1 : middle;
}

function find() {
	var val = binarySearch(document.form1.findField.value);
	if (val != -1) {
		document.form1.resultField.value = val;
	}
	else {
		document.form1.resultField.value = "не найден";
	}
	tableCreate();
}

function clearHistory() {
	form2.removeChild(form2.lastChild);
}
 
