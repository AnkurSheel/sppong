
rem Run this cmd file to copy the Retail files to the Retail folder

call UpdateMedia.cmd
xcopy /Y /D /S ..\Media\*.* ..\Retail\resources\

rem pause