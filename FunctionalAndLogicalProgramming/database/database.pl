:- dynamic metall/3.

database :- load_data('metall.txt'),
            repeat,
            writeln('���� ������ � ��������.'),
            writeln('1 - ��������'),
            writeln('2 - ��������'),
            writeln('3 - �������'),
            writeln('4 - ������ (������� � ����������� �������������)'),
            writeln('5 - �����'),
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
           writeln('���������� ����.'),
           writeln('Name  Conductivity  Cost'),
           metall(Name, Conductivity, Cost),
           write(Name),
           write(' '),
           write(Conductivity),
           write(' '),
           writeln(Cost).
item(2) :- writeln('���������� � ����.'),
           write_in_metall,
           write_in_file('metall.txt').
item(3) :- writeln('�������� ������� �� ����.'),
           writeln('������������: '),
           read(Name),
           check_name(Name),
           retractall(metall(Name, _, _)),
           write_in_file('metall.txt').
item(4) :- writeln('������� � ����������� �������������:'),
           metall(Name, Conductivity, _),
           is_min(Conductivity),
           min(Conductivity),
           writeln(Name).

load_data(Filename) :- consult(Filename), !.
load_data(_).

check_exist(Filename) :- exists_file(Filename), !.
check_exist(_) :- writeln('���� ���� ������ �� ������!'), fail.

check_name(Name) :- metall(Name, _, _), !.
check_name(_) :- writeln('������� � ����� ������������� ��� � ����!'), fail.

is_min(X) :- metall(_, Y, _), X > Y, !, fail.
is_min(_).
min(X) :- metall(_, X, _), is_min(X), !.

write_in_metall :- write('������������: '),
                   read(Name),
                   write('�������� ������������: '),
                   read(Conductivity),
                   write('���������: '),
                   read(Cost),
                   assertz(metall(Name, Conductivity, Cost)).

write_in_file(Filename) :- tell(Filename),
                           listing(metall/3),
                           told.