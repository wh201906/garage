--(1)
select * from Student
where Clno = 
(
  select Clno from Student
  where Sname = N'李勇'
);

--(2)
select * from Student
where Sno in
(
  select Sno from Grade
  where Cno in
  (
    select Cno from Grade
    where Sno = 
    (
      select Sno from Student
      where Sname = N'李勇'
    )
  )
);

--(3)
select * from Student
where Sage <= 25 and Sage >=
(
  select Sage from Student
  where Sname = N'李勇'
);

--(4)
select Sno, Sname from Student
where Sno in 
(
  select Sno from Grade
  where Cno =
  (
    select Cno from Course
    where Cname = N'操作系统'
  )
);

--(5)
select Sname from Student
where Sno not in -- no null value in Student table
(
  select Sno from Grade
  where Cno = 1
);

--(6)
Select s.Sname 
from Student s inner join Grade g
on s.Sno = g.Sno
group by s.Sname having count(g.Cno) = 7