create table Student
(
    Sno Char(7) primary key,
    Sname VarChar(20) not null,
    Ssex Char(2) not null,
    Sage Smallint,
    Clno Char(5) not null
);

create table Course
(
    Cno Char(1) primary key,
    Cname VarChar(20) not null,
    Credit Smallint
);

create table Class
(
    Clno Char(5) primary key,
    Speciality VarChar(20) not null,
    Inyear Char(4) not null,
    Number Integer,
    Monitor Char(7)
);

create table Grade
(
    Sno Char(7) not null,
    Cno Char(1) not null,
    Gmark Numeric(4,1),
    primary key(Sno, Cno)
);