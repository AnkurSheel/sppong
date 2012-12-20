
rem Run this cmd file to copy the Retail files to the Retail folder

del ..\Retail\*.*   /s /f  /q
FOR /D %%p IN ("..\Retail\*.*") DO rmdir "%%p" /s /q

xcopy /Y /D /S ..\bin\*.exe  ..\Retail\
xcopy /Y /D /S ..\bin\*.dll ..\Retail\
xcopy /Y /D /S ..\bin\OptionsRetail.ini ..\Retail\

call CopyResources.cmd

pause