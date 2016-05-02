/* Данный скрипт позволяет перемещать мышью любой 
 * абсолютно позиционированный элемент 
 * с индивидуальным атрибутом dragEnabled. */
var elDragged = null  // Перемещаемый элемент.

function doMouseMove() {
	// Проверяет, нажата ли кнопка мыши и находится ли элемент
	// в состоянии перемещения.
	if ((1 == event.button) && (elDragged != null)) {
		// Перемещение элемента.
		// Сохранение положения мыши в документе.
		var intTop = event.clientY + document.body.scrollTop;
		var intLeft = event.clientX + document.body.scrollLeft;
		// Определение элемента, над которым находится мышь.
		var intLessTop  = 0;
		var intLessLeft = 0;
		var elCurrent = elDragged.offsetParent;
		while (elCurrent.offsetParent != null) {
			intLessTop += elCurrent.offsetTop;
			intLessLeft += elCurrent.offsetLeft;
			elCurrent = elCurrent.offsetParent;
		}
		// Установка нового положения.
		elDragged.style.pixelTop = intTop - intLessTop - elDragged.y;
		elDragged.style.pixelLeft = intLeft - intLessLeft - elDragged.x;
		event.returnValue = false;
	}
}

function checkDrag(elCheck) {
	// Проверка того, находится ли указатель мыши над элементом,
	// который поддерживает перемещение.
	while (elCheck != null) {
		if (null != elCheck.getAttribute("dragEnabled")) 
			return elCheck;
		elCheck = elCheck.parentElement;
	}      
	return null;
}

function doMouseDown() {
	// Сохранение перемещаемого элемента.
	var elCurrent = checkDrag(event.srcElement);
	if (null != elCurrent) {
		elDragged = elCurrent;
		// Определение местоположения указателя мыши в элементе.
		elDragged.x = event.offsetX;
		elDragged.y = event.offsetY;
		var op = event.srcElement;
		// Поиск действительного местоположения по отношению 
		// к перемещаемому элементу.
		if ((elDragged != op.offsetParent) && (elDragged != event.srcElement)) {
			while (op != elDragged) {
				elDragged.x += op.offsetLeft;
				elDragged.y += op.offsetTop;
				op = op.offsetParent;
			}
		}
	}
}

function doSelectTest() {
	// Не разрешать выделение текста в перемещаемых элементах.
	return (null == checkDrag(event.srcElement) && (elDragged!=null));
}

// Связать обработчики событий мыши.
document.onmousedown = doMouseDown;
document.onmousemove = doMouseMove;
// Сброс элемента при отпускании кнопки мыши.
document.onmouseup = new Function("elDragged = null;");
document.ondragstart = doSelectTest;
document.onselectstart = doSelectTest;


