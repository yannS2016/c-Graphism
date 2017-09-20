@echo off
if not %0%*==%0 goto ok
echo usage:
echo   %0 FILE ...
echo.
echo Compiles your WinBGIm program. The first file listed must be the file 
echo containing your main() function, and will be the name of your final 
echo executable. For example:
echo.
echo   %0 pong.cpp data.cpp options.cpp
echo.
echo produces an executable named "pong.exe".
echo.
echo You can also specify other standard compile options on the command line, 
echo such as libraries you wish to link with.
echo.
goto :end

:ok
g++ -Wall -std=c++11 -pedantic -O2 -o %~n1 %* -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 
:end
