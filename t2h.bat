
bcc32 ./src/main.cpp

set /P password="Please enter password:"
set /P fileName="Please enter file name:"

main %password% t2h %fileName%

