--(1)
select distinct c.Cno
from Course c inner join Grade g
on c.Cno = g.Cno;

--(2)
select * from Student
where Clno = '01311' and Ssex = N'女';

--(3)
select Sname, Ssex, 
(
  datepart(year, dateadd(year, -Sage, getdate()))
) as Birthyear
from Student
where Clno = '01311' or Clno = '01312';

--(4)
select * from Student
where left(Student.Sname, 1) = N'李';

--(5)
select Number from Class
where Clno =
(
  select Clno from Student
  where Sname = N'李勇'
)

--(6)
select avg(distinct Gmark) as average, max(Gmark) as max, min(Gmark) as min from Grade
where Cno = 
(
  select Cno from Course
  where Cname = N'操作系统'
)

--(7)
select count(distinct s.Sno)
from Student s inner join Grade g
on S.Sno = g.Sno;

--(8)
--select count(distinct *) will report a error there
select count(distinct Sno) from Student
where Sno in
(
  select Sno from Grade
  where Cno = 
  (
    select Cno from Course
    where Cname = N'操作系统'
  )
);

--(9)
select Sname from Student
where Sno in
(
  select Sno from Grade
  where Gmark is null
)
and Clno in
(
  select Clno from Class
  where Inyear = 2000 and Speciality = N'计算机软件'
);