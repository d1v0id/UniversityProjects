﻿goal :- writeln('Введите список элементов:'),
        readln(X),
        only_one(X, L),
        writeln('Результат:'),
        writeln(L).

only_one([], []) :- !. % пустой список - решение
only_one([X], [X]) :- !. % список из одного элемента и есть решение
only_one([X, X | T], L) :- !, only_one([X | T], L). % если встертили эелемент который равен предыдущему - игнорируем
only_one([X1, X2 | T1], [X1 | T2]) :- !, only_one([X2 | T1], T2). % если встретили элемент который не равен предыдущему (с конца) то добавляем его в ответ
only_one(L, L).
