/* Лабораторная работа № 4 */

/* Написать и выполнить безымянный блок PL/SQL, в котором объявите одну
переменную числового типа, одну переменную символьного типа и одну
переменную типа даты. Переменной числового типа присвойте начальное значение.
В основной части блока присвойте символьной переменной и переменной типа
даты конкретные значения и напишите функцию вывода значений всех переменных. */

declare
  v_num number(10) := 11;
  v_char char;
  v_date date;
  
  procedure print_variables(v_num number, v_char char, v_date date) is
  begin
    dbms_output.put_line('число = ' || v_num);
    dbms_output.put_line('символ = ' || v_char);
    dbms_output.put_line('дата = ' || v_date);
  end;
  
begin
  v_char := 'c';
  v_date := sysdate;
  
  print_variables(v_num, v_char, v_date);
end;