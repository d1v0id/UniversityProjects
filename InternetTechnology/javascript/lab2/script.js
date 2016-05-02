var delay = 100; // задержка по умолчанию
var imageNum = 1; // стартовый номер картинки
var theImages = new Array();
var rideStatus = false;
var rideDirection = true;

for(i = 1; i < 11; i++) {
	theImages[i] = new Image();
	theImages[i].src = "images/s" + i + ".gif";
}

function SantaRideOnDeers() {
	if (rideStatus == true) {
		document.animation.src = theImages[imageNum].src;
		if (rideDirection) {
			imageNum++;
			if (imageNum > 10) {
				imageNum = 1;
			}
		}
		else {
			imageNum--;
			if (imageNum < 1) {
				imageNum = 10;
			}
		}
		
	}
}

function rideStart() {
	if (rideStatus == false) {
		rideStatus = true;
		SantaRideOnDeers();
	}
}

function rideSlower() {
	if (rideStatus == true) {
		delay += 10;
		if (delay > 4000) delay = 4000;
	}
}

function rideFaster() {
	if (rideStatus == true) {
		delay -= 10;
		if (delay < 0) delay = 0;
	}
}

function rideReverse() {
	rideDirection = !rideDirection;
}

function rideStop() {
	rideStatus = false;
}

