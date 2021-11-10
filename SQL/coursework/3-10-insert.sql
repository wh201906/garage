-- delete from Student;

insert into Student
	(Sno, Sname, Ssex, Sage, Clno)
values
    ('2000101', N'李勇', N'男', 20, '00311'),
    ('2000102', N'刘诗晨', N'女', 19, '00311'),
    ('2000103', N'王一鸣', N'男', 20, '00312'),
    ('2000104', N'张婷婷', N'女', 21, '00312'),
    ('2001101', N'李勇敏', N'女', 19, '01311'),
    ('2001102', N'贾向东', N'男', 22, '01311'),
    ('2001103', N'陈宝玉', N'男', 20, '01311'),
    ('2001104', N'张逸凡', N'男', 21, '01311');

-- delete from Course;

insert into Course
	(Cno, Cname, Credit)
values
    ('1', N'数据库', '4'),
    ('2', N'离散数学', '3'),
    ('3', N'管理信息系统', '2'),
    ('4', N'操作系统', '4'),
    ('5', N'数据结构', '4'),
    ('6', N'数据处理', '2'),
    ('7', N'C语言', '4');
    
-- delete from Course;

insert into Class
	(Clno, Speciality, Inyear, Number, Monitor)
values
    ('00311', N'计算机软件', 2000, '120', '2000101'),
    ('00312', N'计算机应用', 2000, '140', '2000103'),
    ('01311', N'计算机软件', 2001, '220', '2001103');
    
-- delete from Grade;

insert into Grade
	(Sno, Cno, Gmark)
values
    ('2000101', '1', 92),
    ('2000101', '3', null),
    ('2000101', '5', 86),
    ('2000102', '1', 78),
    ('2000102', '6', 55),
    ('2000103', '3', 65),
    ('2000103', '6', 78),
    ('2000103', '5', 66),
    ('2000104', '1', 54),
    ('2000104', '6', 83),
    ('2001101', '2', 70),
    ('2001101', '4', 65),
    ('2001102', '2', 80),
    ('2001102', '4', null),
    ('2000103', '1', 83),
    ('2000103', '2', 76),
    ('2000103', '4', 56),
    ('2000103', '7', 88);