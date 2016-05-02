/* Создать хранимую процедуру PL/SQL, которая выводит минимальное из двух чисел,
заданных в качестве аргументов. Вызвать процедуру из безымянного блока. */

create or replace procedure PrMin(p_n1 in number, p_n2 in number) is
  res number;
begin
  res := case when (p_n1 < p_n2) then p_n1 else p_n2 end;
  dbms_output.put_line(res);
end;
/

begin
  PrMin(1, 2);
end;