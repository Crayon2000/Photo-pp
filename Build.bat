@echo off
set toolkit=D:\Programmes
set path=%path%;%toolkit%

echo Compressing executable...
upx --brute --force -qq Photo.exe
if errorlevel 1 goto error

echo Zipping files...
zip -q photo.zip Photo.exe lisez-moi.htm
if errorlevel 1 goto error

echo Build successful.
goto end
:error
echo Build incomplete!
:end
pause