
bcc32 ./src/main.cpp

set /P password="Please enter password:"
set /P fileName="Please enter file name:"

main %password% h2t %fileName%

