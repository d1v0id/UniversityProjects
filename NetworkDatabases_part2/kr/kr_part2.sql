/* Создать две таблицы, имеющие уникальные поля и первичные ключи.
Таблицы должны быть связаны с помощью внешнего ключа. Таблицы должны содержать
данные о Нефтяных компаниях и Нефтепроводах. Каждая компания эксплуатирует
несколько нефтепроводов. Компания имеет название, страну, в которой
зарегистрирована, и объем добычи. Нефтепровод имеет название и протяженность. */
/*create table company(cid number(10), cname varchar2(40), ccountry varchar2(40), cvolume number(20))
create table pipeline(pid number(10), pname varchar2(40), plength number(20), cid number(10))
alter table company add(constraint company_pk_cid primary key(cid))
alter table pipeline add(constraint pipeline_pk_pid primary key(pid),
  constraint pipeline_fk_cid foreign key(cid) references company(cid))*/

/* Создать представление для связанных таблиц, которое позволяет вывести
только часть полей и часть строк таблиц. */
/*create view v_pipeline_companies as select
  company.cname, pipeline.pname, pipeline.plength
  from company inner join pipeline on company.cid = pipeline.cid;*/
/*select * from v_pipeline_companies;*/

/* Создать пакет PL/SQL, содержащий процедуру начального заполнения таблиц
данными (по 5-7 записей в таблице) и процедуру очистки таблиц (удаления
записей). Добавить в пакет процедуру изменения данных в таблицах. Значения
изменяемых данных должны передаваться в процедуру как параметры. В процедурах
предусмотреть обработку исключений. Процедура должна добавлять в таблицу новую
компанию и нефтепровод, данные о которых передаются в процедуру как параметры.
Включить в пакет еще одну процедуру, которая выводит компании, суммарная
протяженность нефтепроводов которых не менее заданной в параметре. */
create or replace package LIB is
  procedure InsertAllData;
  procedure DeleteAllData;
  procedure InsertData(
    cname varchar2,
    ccountry varchar2,
    cvolume number,
    pname varchar2,
    plength number);
  procedure showBiggerThen(plength number);
end LIB;
/

create or replace package body LIB is

  v_currentCid number(10);
  v_currentPid number(10);
  
  procedure InsertAllData is
    v_sqlStr varchar2(400);
    v_cnt number(10);
  begin
    v_sqlStr := 'insert into company(cid, cname, ccountry, cvolume) values(:id, :name, :country, :volume)';
    
    execute immediate v_sqlStr using 1000000001, 'Bashneft', 'Russia', 1235236;
    execute immediate v_sqlStr using 1000000002, 'Gazprom Neft', 'Russia', 512344;
    execute immediate v_sqlStr using 1000000003, 'Krasnoleninsky Refinery', 'Russia', 5624571;
    execute immediate v_sqlStr using 1000000004, 'Lukoil', 'Russia', 345146;
    execute immediate v_sqlStr using 1000000005, 'Rosneft', 'Russia', 634534;
    execute immediate v_sqlStr using 1000000006, 'Russneft', 'Russia', 4017563;
    execute immediate v_sqlStr using 1000000007, 'Sibir Energy', 'Russia', 724513;
    execute immediate v_sqlStr using 1000000008, 'Surgutneftegas', 'Russia', 834951;
    execute immediate v_sqlStr using 1000000009, 'Tatneft', 'Russia', 1135624;
    v_currentCid := 1000000010;
    
    execute immediate 'select count(*) from company' into v_cnt;
    dbms_output.put_line('Added ' || v_cnt || ' oil companies.');
    
    v_sqlStr := 'insert into pipeline(pid, pname, plength, cid) values(:id, :name, :length, :cid)';
    execute immediate v_sqlStr using 2000000001, 'The Baku - Novorossiysk', 2005, 1000000001;
    execute immediate v_sqlStr using 2000000002, 'The Balakhani - Black city', 1005, 1000000002;
    execute immediate v_sqlStr using 2000000003, 'The Baltic pipeline system', 3005, 1000000003;
    execute immediate v_sqlStr using 2000000004, 'The Baltic pipeline system-II', 1505, 1000000004;
    execute immediate v_sqlStr using 2000000005, 'The Eastern Siberia - Pacific ocean', 7005, 1000000005;
    execute immediate v_sqlStr using 2000000006, 'The Pipeline Grozny - Tuapse', 5205, 1000000006;
    execute immediate v_sqlStr using 2000000007, 'The Friendship', 1055, 1000000007;
    execute immediate v_sqlStr using 2000000008, 'The Caspian pipeline consortium', 5065, 1000000008;
    execute immediate v_sqlStr using 2000000009, 'The Murmansk pipeline', 2005, 1000000009;
    execute immediate v_sqlStr using 2000000010, 'The Pipeline Surgut - Polotsk', 1605, 1000000001;
    execute immediate v_sqlStr using 2000000011, 'The Pipeline Uzen - Atyrau - Samara', 1465, 1000000002;
    v_currentPid := 2000000012;

    execute immediate 'select count(*) from pipeline' into v_cnt;
    dbms_output.put_line('Added ' || v_cnt || ' oil pipelines.');
  end;
  
  procedure DeleteAllData is
  begin
    execute immediate 'delete from pipeline';
    execute immediate 'delete from company';
    v_currentCid := 0;
    v_currentPid := 0;
  end;
  
  procedure InsertData(
      cname varchar2,
      ccountry varchar2,
      cvolume number,
      pname varchar2,
      plength number) is
    
    v_companyRow company%rowtype;
    v_pipelineRow pipeline%rowtype;
    v_sqlStr varchar2(400);
  begin
    v_sqlStr := 'insert into company(cid, cname, ccountry, cvolume) values(:id, :name, :country, :volume)';
    execute immediate v_sqlStr using v_currentCid, cname, ccountry, cvolume;
    
    execute immediate 'select * from company where cid = ' || v_currentCid into v_companyRow;
    dbms_output.put_line('Added: ' || v_companyRow.cname || ', ' || v_companyRow.ccountry || ', ' || v_companyRow.cvolume);
    
    v_sqlStr := 'insert into pipeline(pid, pname, plength, cid) values(:id, :name, :length, :cid)';
    execute immediate v_sqlStr using v_currentPid, pname, plength, v_currentCid;
    
    execute immediate 'select * from pipeline where pid = ' || v_currentPid into v_pipelineRow;
    dbms_output.put_line('Added: ' || v_pipelineRow.pname || ', ' || v_pipelineRow.plength);
    
    v_currentCid := v_currentCid + 1;
    v_currentPid := v_currentPid + 1;
  end;
  
  /* компании, суммарная протяженность нефтепроводов которых не менее заданной в параметре */
  procedure showBiggerThen(plength number) is
    v_sqlStr varchar2(400);
  begin
    v_sqlStr := 'select cname, sum(plength) from company inner join pipeline on company.cid = pipeline.cid where plength >= :length group by cname';
    execute immediate v_sqlStr using plength;
  end;
  
end LIB;
/

begin
  LIB.DeleteAllData;
  LIB.InsertAllData;

  LIB.InsertData('Gazprom Neft', 'Russia', 512344, 'The Eastern Siberia - Pacific ocean', 7005);
  LIB.InsertData('Gazprom', 'Russia', 61345, 'The Eastern Siberia - Pacific ocean', 6134);
  LIB.showBiggerThen(50000);
end;
