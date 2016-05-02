/* ������������ ������ � 5 */

/* ��������� � ��������� ��������� PL/SQL, ������� ��������� �� ���� ������
����� ���������, ��� ������������ ������ 0.15, � ������� ���������. ��������
� ��������� ������ Exception � ������������ OTHERS � ������� ���������
�� ������ �� ����� �������. */

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