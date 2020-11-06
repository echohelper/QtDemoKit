::@echo off
rem *****************************************************************
rem desc: copy project-files from build to bin
rem note: no blank lines before and after brackets
rem %1:$(ConfigurationName)  %2:$(SolutionName)  %3:$(ProjectName)
rem %4:$(OutputType)
rem start $(ProjectDir)script\build_event_after.bat $(Configuration) $(SolutionName) $(ProjectName) $(OutputType)
rem author: echohelper
rem *****************************************************************

echo run script, after build event!

rem use vs macro to set param
@set ConfigurationName=%1
@set SolutionName=%2
@set ProjectName=%3
@set OutputType=%4

@set SolutionOutput=%SolutionName%_%ConfigurationName%_x64


rem CurrentDir is ProjectDir. switch to SolutinDir.
rem CurrentDir is SolutinDir Now.
cd ..\..

rem copy runtime files
if "%1" == "Release" (
	xcopy /Y /F /E /R build\%SolutionOutput%\%ProjectName%.exe bin\
	del /Q bin\%ProjectName%.pdb
) else (
	xcopy /Y /F /E /R build\%SolutionOutput%\%ProjectName%.exe bin\
	xcopy /Y /F /E /R build\%SolutionOutput%\%ProjectName%.pdb bin\
	xcopy /Y /F /E /R build\%SolutionOutput%\%ProjectName%.pdb pdb\
)

rem debug
::pause

rem it is need
exit
