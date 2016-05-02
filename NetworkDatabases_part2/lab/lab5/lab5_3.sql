/* —оставить и выполнить программу PL/SQL, котора€, использу€ курсор, считывает
из базы данных суммы заказов, сделанных после 04.01.2009, и выводит результат. */

declare
  cursor c_bigger is select amt from ord where odate > to_date('04-JAN-2009');
  v_amt ord.amt%TYPE;
  
begin
  open c_bigger;
  loop
    fetch c_bigger into v_amt;
      exit when c_bigger%NOTFOUND;
    dbms_output.put_line(v_amt);
  end loop;
  close c_bigger;
  
exception
  when others then
    dbms_output.put_line('Amounts not found!');
end;