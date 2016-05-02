:- dynamic metall/3.

database :- load_data('metall.txt'),
            repeat,
            writeln('База данных о металлах.'),
            writeln('1 - Просмотр'),
            writeln('2 - Добавить'),
            writeln('3 - Удалить'),
            writeln('4 - Запрос (металлы с минимальной проводимостью)'),
            writeln('5 - Выход'),
            write('? '),
            read(X),
            X < 6,
            item(X),
            X = 5, !.

item(5).
item(1) :- check_exist('metall.txt'),
           retractall(metall(_, _, _)),
           listing(metall/3),
           consult('metall.txt'),
           writeln('Содержимое базы.'),
           writeln('Name  Conductivity  Cost'),
           metall(Name, Conductivity, Cost),
           write(Name),
           write(' '),
           write(Conductivity),
           write(' '),
           writeln(Cost).
item(2) :- writeln('Добавление в базу.'),
           write_in_metall,
           write_in_file('metall.txt').
item(3) :- writeln('Удаление металла из базы.'),
           writeln('Наименование: '),
           read(Name),
           check_name(Name),
           retractall(metall(Name, _, _)),
           write_in_file('metall.txt').
item(4) :- writeln('Металлы с минимальной проводимостью:'),
           metall(Name, Conductivity, _),
           is_min(Conductivity),
           min(Conductivity),
           writeln(Name).

load_data(Filename) :- consult(Filename), !.
load_data(_).

check_exist(Filename) :- exists_file(Filename), !.
check_exist(_) :- writeln('Файл базы данных не найден!'), fail.

check_name(Name) :- metall(Name, _, _), !.
check_name(_) :- writeln('Металла с таким наименованием нет в базе!'), fail.

is_min(X) :- metall(_, Y, _), X > Y, !, fail.
is_min(_).
min(X) :- metall(_, X, _), is_min(X), !.

write_in_metall :- write('Наименование: '),
                   read(Name),
                   write('Удельная проводимость: '),
                   read(Conductivity),
                   write('Стоимость: '),
                   read(Cost),
                   assertz(metall(Name, Conductivity, Cost)).

write_in_file(Filename) :- tell(Filename),
                           listing(metall/3),
                           told.