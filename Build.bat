@echo off
set toolkit=D:\Programmes
set path=%toolkit%

echo Compressing executable...
upx --best --force -qq Photo.exe
if errorlevel 1 goto error

echo Zipping files...
zip photo.zip Photo.exe lisez-moi.htm

echo Build successful.
goto end
:error
echo Build incomplete!
:end
pause