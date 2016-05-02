// массив для хранения данных о поле
var arr = new Array (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

// массив для поиска пути
var arr_path = new Array (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

var num = 0;

function DrawCell(x1, y1) { // функция прорисовки клетки
  if (arr[9 * y1 + x1] > 19) {
    document.images[9 * y1 + x1].src = 'images/mine.jpg'
  }
  else {
    document.images[9 * y1 + x1].src = 'images/' + arr[9 * y1 + x1] + '.jpg';
  }
}

function StartNewGame() { // новая игра
  num = 0;

  for (var x = -2; x <= 11; x++) {
    for (var y = -2; y <= 11; y++) {
      arr[9 * y + x] = 0;
      arr_path[9 * y + x] = 0;
    }
  }

  for (var x = 0; x <= 8; x++) {
    for (var y = 0; y <= 8; y++) {
      document.images[9 * y + x].src = 'images/p.jpg';
    }
  }

  // расстановка мин на поле
  var i = 1;
  while (i < 14) {
    x = Math.floor(Math.random() * 9);
    y = Math.floor(Math.random() * 9);
    if (arr[9 * y + x] == 20) {
      continue;
    }
    arr[9 * y + x] = 20;
    i++;
  }

  // расстановка цифр вокруг мин
  for (x = 0; x <= 8; x++) {
    for (y = 0; y <= 8; y++) {
      if (arr[9 * y + x] > 19) {
        if ((x - 1 >= 0) && (x - 1 <= 8)) {
          arr[9 * y + x - 1]++;
        }

        if ((x - 1 >= 0) && (x - 1 <= 8) && (y - 1 >= 0) && (y - 1 <= 8)) {
          arr[9 * (y - 1) + x - 1]++;
        }

        if ((y - 1 >= 0) && (y - 1 <= 8)) {
          arr[9 * (y - 1) + x]++;
        }

        if ((x + 1 >= 0) && (x + 1 <= 8) && (y - 1 >= 0) && (y - 1 <= 8)) {
          arr[9 * (y - 1) + x + 1]++;
        }

        if ((x + 1 >= 0) && (x + 1 <= 8)) {
          arr[9 * y + x + 1]++;
        }

        if ((x + 1 >= 0) && (x + 1 <= 8) && (y + 1 >= 0) && (y + 1 <= 8)) {
          arr[9 * (y + 1) + x + 1]++;
        }

        if ((y + 1 >= 0) && (y + 1 <= 8)) {
          arr[9 * (y + 1) + x]++;
        }

        if ((x - 1 >= 0) && (x - 1 <= 8) && (y + 1 >= 0) && (y + 1 <= 8)) {
          arr[9 * (y + 1) + x - 1]++;
        }
      }
    }
  }
}

function PoleClick(x1, y1) { // выбор клетки
  if (arr[9 * y1 + x1] > 19) {
    DrawCell(x1, y1);
    for (var x2 = -2; x2 <= 11; x2++) {
      for (var y2 = -2; y2 <= 11; y2++) {
        if (arr[9 * y2 + x2] > 19) {
          DrawCell(x2, y2);
        }
      }
    }
    alert('Вы проиграли!');
    StartNewGame();
  } else if (arr_path[9 * y1 + x1] == 0) {
    arr_path[9 * y1 + x1] = 1;
    num++;
    DrawCell(x1, y1);
    if (num == 68) {
      WinGame();
    }
    if (arr[9 * y1 + x1] == 0) {
      FindZeroCell(x1, y1);
    }
  }
}

function FindZeroCell(x1, y1) { // функция для поиска пустоты
  for (var i = x1 - 1; i <= x1 + 1; i++) {
    for (var j = y1 - 1; j <= y1 + 1; j++) {
      if (num == 68) {
        WinGame();
      }
      if ((i >= 0) && (i < 9) && (j >= 0) && (j < 9) && (arr_path[9 * j + i] == 0)) {
        if ((i == x1 - 1) && (j == y1 - 1) && (arr[9 * (y1 - 1) + x1 - 1] == 0)) {
          continue;
        }
        if ((i == x1 + 1) && (j == y1 - 1) && (arr[9 * (y1 - 1) + x1 + 1] == 0)) {
          continue;
        }
        if ((i == x1 + 1) && (j == y1 + 1) && (arr[9 * (y1 + 1) + x1 + 1] == 0)) {
          continue;
        }
        if ((i == x1 - 1) && (j == y1 + 1) && (arr[9 * (y1 + 1) + x1 - 1] == 0)) {
          continue;
        }

        if (arr[9 * j + i] == 0) {
          DrawCell(i, j);
          num++;
          arr_path[9 * j + i] = 1;
          FindZeroCell(i, j);
        } else {
          num++;
          arr_path[9 * j + i] = 1;
          DrawCell(i, j);
        }
      }
    }
  }
}

function WinGame() { // обработка выигрыша
  for (x = 0; x <= 8; x++) {
    for (y = 0; y <= 8; y++) {
      if (arr[9*y+x] > 19) {
        document.images[9*y+x].src = 'images/flag.jpg';
      }
    }
  }
  alert('Вы выиграли!');
  StartNewGame();
}
