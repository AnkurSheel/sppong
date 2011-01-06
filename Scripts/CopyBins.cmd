
rem Run this cmd file to copy the Retail files to the Retail folder

md ..\Retail\

copy ..\bin\*.exe ..\Retail\
copy ..\bin\*.dll ..\Retail\

md ..\Retail\resources\
md ..\Retail\resources\Sprites
copy ..\Media\Sprites\ ..\Retail\resources\Sprites

pause