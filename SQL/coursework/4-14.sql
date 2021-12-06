--(1)
grant select
    on Student
    to ZhangYong;
grant select
    on Course
    to ZhangYong;

--(2)
grant insert, delete
    on Student
    to ZhangSan
    with grant option;

--(3)
grant select, update(Credit)
    on Course
    to LiSi;

--(4)
grant all privileges
    on Student
    to LiYongMing
    with grant option;

--(5)
revoke select
    on Student
    from ZhangYong;
revoke select
    on Course
    from ZhangYong;

--(6)
revoke insert, delete
    on Student
    from ZhangSan;