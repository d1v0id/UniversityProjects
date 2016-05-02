/* Лабораторная работа № 5 */

/* Составить и выполнить программу PL/SQL, которая считывает из базы данных
имена продавцов, чьи комиссионные меньше 0.15, и выводит результат. Добавить
в программу раздел Exception с обработчиком OTHERS и выводом сообщения
об ошибке из этого раздела. */

declare
  cursor c_less is select sname from sal where comm < 0.15;
  v_sname sal.sname%TYPE;
  
begin
  open c_less;
  loop
    fetch c_less into v_sname;
      exit when c_less%NOTFOUND;
    dbms_output.put_line(v_sname);
  end loop;
  close c_less;
  
exception
  when others then
    dbms_output.put_line('Sellers not found!');
end;