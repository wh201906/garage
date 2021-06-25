flex SysY.l
if [ $? -ne 0 ]; then exit 1; fi
echo "flex completed"
gcc -g lex.yy.c -o flexx
if [ $? -ne 0 ]; then exit 1; fi
echo "compile completed"
chmod u+x ./flexx
./flexx
