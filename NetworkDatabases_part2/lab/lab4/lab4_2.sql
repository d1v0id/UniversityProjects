/* Ћабораторна€ работа є 4 */

/* —оставить и выполнить программу PL/SQL, котора€ вычисл€ет квадраты первых
п€ти положительных чисел, кратных 2, использу€ цикл While, и выводит результат. */

declare
  v_cnt number(1);
  v_num number(2);

begin
  v_cnt := 0;
  v_num := 0;
  while v_cnt < 5 loop
    if mod(v_num, 2) = 0 then
      dbms_output.put_line(v_num * v_num);
      v_cnt := v_cnt + 1;
    end if;
    v_num := v_num + 1;
  end loop;
end;