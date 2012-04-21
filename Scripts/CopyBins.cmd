
rem Run this cmd file to copy the Retail files to the Retail folder

call CopyResources.cmd
xcopy /Y /D /S ..\bin\*.exe  ..\Retail\
xcopy /Y /D /S ..\bin\*.dll ..\Retail\

pause