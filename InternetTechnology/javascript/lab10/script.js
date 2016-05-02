var delay = 1000;
var ClockString;
clock();

function reloadMe() {
	document.location.reload(true);
}

function checkLength(item) {
	if (item< 10) {
		item = "0" + item;
	}
	else {
		item = "" + item;
	}

	return (item);
}

function clock() {
	var OpenImg = '<img src=images/'+'dg';
	var CloseImg='.gif class=\"DigitImage\" />';
	ClockString = "";
	now = new Date();
	var CurHour = now.getHours();
	var CurMinute = now.getMinutes();
	var CurMonth = now.getMonth() + 1; // потому что отсчет месаца с 0
	var CurDay = now.getDate();
	var CurYear = now.getYear();
	now = null;

	if (CurHour >= 12) {
		CurHour = CurHour - 12;
		Ampm = "pm";
	}
	else {
		Ampm = "am";
	}

	if (CurHour == 0) {
		CurHour = "12";
	}

	CurHour = checkLength(CurHour);
	CurMinute = checkLength(CurMinute);
	CurMonth = checkLength(CurMonth);
	CurDay = checkLength(CurDay);
	CurYear = checkLength(CurYear);

	CurHour = "" + CurHour;
	for (Count = 0; Count < CurHour.length; Count++) {
		ClockString += OpenImg + CurHour.substring(Count, Count + 1) + CloseImg;
	}

	ClockString += OpenImg + "c" + CloseImg;

	for (Count = 0; Count < CurMinute.length; Count++) {
		ClockString += OpenImg + CurMinute.substring(Count, Count + 1) + CloseImg;
	}

	ClockString += OpenImg + Ampm + CloseImg;

	for (Count = 0; Count < CurMonth.length; Count++) {
		ClockString += OpenImg + CurMonth.substring(Count, Count + 1) + CloseImg;
	}

	ClockString += OpenImg + "p" + CloseImg;

	for (Count = 0; Count < CurDay.length; Count++) {
		ClockString += OpenImg + CurDay.substring(Count, Count + 1) + CloseImg;
	}

	ClockString += OpenImg + "p" + CloseImg;

	for (Count = 1; Count < CurYear.length; Count++) { /* цикл начинается с 1 потому что getYear() возвращает текущий год - 1900 */
		ClockString += OpenImg + CurYear.substring(Count, Count + 1) + CloseImg;
	}
}

function pathOnly(InString)  {
        LastSlash = InString.lastIndexOf('/', InString.length-1);
        OutString = InString.substring(0, LastSlash+1);
        return (OutString);
}

