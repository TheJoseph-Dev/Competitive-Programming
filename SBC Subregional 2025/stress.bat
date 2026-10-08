@echo off

g++ G.cpp -O2 -o main.exe
g++ G-brute.cpp -O2 -o brute.exe

:loop
python gen.py > input.txt

main.exe < input.txt > out1.txt
brute.exe < input.txt > out2.txt

fc out1.txt out2.txt > nul
if errorlevel 1 goto :end

echo OK
goto :loop

:end
echo Mismatch found!
pause