@echo off

doxygen Doxyfile
if errorlevel 1 exit /b 1

if not exist docs\html\uml mkdir docs\html\uml
copy /y uml\student.puml docs\html\uml\student.puml >nul
if errorlevel 1 exit /b 1
copy /y uml\student.svg docs\html\uml\student.svg >nul
if errorlevel 1 exit /b 1
