--(1)
select Sno, Gmark from Grade
where Cno = 3
order by Gmark desc;

--(2)
select * from Student
order by Clno, Sage desc;

--(3)
select Cno, count(Cno) as count 
from Grade
group by Cno;

--(4)
select Sno from Grade
group by Sno having count(Cno) > 3;