--1
--(1)
create view Stu_01311_1
as select * from Student
where Sno in 
(
  select Sno from Grade
  where Cno = 1
)
and Clno = 01311;

--(2)
create view Stu_01311_2
as select * from Student
where Sno in 
(
  select Sno from Grade
  where Cno = 1
  and Gmark < 60
)
and Clno = 01311;

--(3)
create view Stu_year(Sno, Sname, Syear)
as select Sno, Sname,
(
  datepart(year, dateadd(year, -Sage, getdate()))
) from Student;

--(4)
select Sname from Stu_year
where Syear > 1990;

--(5)
select y.Sno, y.Sname, y.Syear 
from Stu_year y inner join Stu_01311_2 s
on y.Sno = s.Sno;


--3
--不能，因为对平均成绩的更新无法转换为对基本表的更新。