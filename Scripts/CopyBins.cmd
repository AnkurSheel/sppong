
rem Run this cmd file to copy the Retail files to the Retail folder

xcopy /Y /D /S ..\bin\*.exe  ..\Retail\
xcopy /Y /D /S ..\bin\*.dll ..\Retail\
xcopy /Y /D /S ..\Media\*.* ..\Retail\resources\

pause