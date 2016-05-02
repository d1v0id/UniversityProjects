function Exchange(a, b) {
	var tmp = a.src;
	a.src = b.src;
	b.src = tmp;
}
