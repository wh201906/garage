--(1)
update Grade
set Gmark = 0
where Sno in
(
  select Sno from Student
  where Clno = '01311'
);

--(2)
delete from Grade
where Sno in
(
  select Sno from Student
  where Clno in
  (
    select Clno from Class
    where Inyear = 2001 and Speciality = N'计算机软件'
  )
);

--(3)
delete from Grade
where Sno =
(
  select Sno from Student
  where Sname = N'李勇'
);
update Class
set Number = Number - 1
where Clno = 
(
  select Clno from Student
  where Sname = N'李勇'
);
delete from Student
where Sname = N'李勇';

--(4)
alter table Class
add Average Numeric(4,1);
update Class
set Average = 
(
  select avg(Sage) from Student
  where Clno = Class.Clno
);