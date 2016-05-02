/* ������������ ������ � 4 */

/* �������� � ��������� ���������� ���� PL/SQL, � ������� �������� ����
���������� ��������� ����, ���� ���������� ����������� ���� � ����
���������� ���� ����. ���������� ��������� ���� ��������� ��������� ��������.
� �������� ����� ����� ��������� ���������� ���������� � ���������� ����
���� ���������� �������� � �������� ������� ������ �������� ���� ����������. */

declare
  v_num number(10) := 11;
  v_char char;
  v_date date;
  
  procedure print_variables(v_num number, v_char char, v_date date) is
  begin
    dbms_output.put_line('����� = ' || v_num);
    dbms_output.put_line('������ = ' || v_char);
    dbms_output.put_line('���� = ' || v_date);
  end;
  
begin
  v_char := 'c';
  v_date := sysdate;
  
  print_variables(v_num, v_char, v_date);
end;