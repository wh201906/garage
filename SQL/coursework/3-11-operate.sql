--(1)
alter table Student
add Nation Varchar(20);

--(2)
alter table Student
drop column Nation;

--(3)
insert into Grade
values('2001110', '3', 80);

--(4)
update Grade
set Gmark=70 where Sno='2001110';

--(5)
delete from Grade
where Sno='2001110';

--(6)
create index IX_Class
on Student (Clno asc);

--(7)
drop index Student.IX_Class;