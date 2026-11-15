bat
```

@echo off
g++ Solver.cpp -O2 -o main.exe
if errorlevel 1 exit /b 1

g++ brute.cpp -O2 -o brute.exe
if errorlevel 1 exit /b 1

:loop
python gen.py > input.txt
if errorlevel 1 exit /b 1

main.exe < input.txt > out1.txt
if errorlevel 1 exit /b 1

brute.exe < input.txt > out2.txt
if errorlevel 1 exit /b 1

fc out1.txt out2.txt > nul
if errorlevel 1 goto end

echo OK
goto loop

:end
echo Difference found!
fc out1.txt out2.txt
pause
```