--(1)
select s.Sno, s.Sname, count(g.Cno) as num
from Student s left join Grade g
on s.Sno = g.Sno
group by s.Sno, s.Sname;

--(2)
select s.Clno, g.Cno, count(g.Cno) as num, avg(g.Gmark) as ave
from Student s inner join Grade g
on s.Sno = g.Sno
group by s.Clno, g.Cno;