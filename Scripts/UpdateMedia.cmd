	       
rem Run this cmd file to update the media folder from bin

xcopy /Y /D /S ..\Debug\resources\*.*  ..\bin\resources\*.*
xcopy /Y /D /S ..\bin\resources\*.*  ..\Media\*.*

rem pause