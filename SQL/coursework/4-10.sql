create table Student
(
    Sno Char(7) primary key,
    Sname NVarChar(20) not null,
    Ssex NChar(2) not null check(Ssex in ('男', '女')) default('男'),
    Sage Smallint check(Sage >= 14 and Sage <= 65),
    Clno Char(5) not null
    --Clno的约束在后面使用alter table实现，否则会由于找不到Class表而报错
);

create table Course
(
    Cno Char(1) primary key,
    Cname NVarChar(20) not null,
    Credit Smallint check(Credit in (1, 2, 3, 4, 5, 6))
);

create table Class
(
    Clno Char(5) primary key,
    Speciality NVarChar(20) not null,
    Inyear Char(4) not null,
    Number Integer check(Number > 1 and Number < 100),
    Monitor Char(7) references Student(Sno)
);

create table Grade
(
    Sno Char(7) not null references Student(Sno)
        on update cascade
        on delete cascade,
    Cno Char(1) not null references Course(Cno)
        on update cascade
        on delete cascade,
    Gmark Numeric(4,1) check(Gmark > 0 and Gmark < 100),
    primary key(Sno, Cno)
);

alter table Student
    add constraint const_Clno
        foreign key(Clno) references Class(Clno)
            on update cascade;