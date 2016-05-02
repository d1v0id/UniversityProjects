/* Создать пакет, в который поместить процедуру из п.1. Вызвать процедуру
пакета из безымянного блока. */

create or replace package lib is
  procedure PrMin(p_n1 in number, p_n2 in number);
end lib;
/

create or replace package body lib is
  procedure PrMin(p_n1 in number, p_n2 in number) is
    res number;
  begin
    res := case when (p_n1 < p_n2) then p_n1 else p_n2 end;
    dbms_output.put_line(res);
  end PrMin;
end lib;
/

begin
  lib.PrMin(1, 2);
end;