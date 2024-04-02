

@echo off
@REM for %%j in (easy_input) do (
for %%j in (diff_input) do (
@REM for %%j in (comp_input) do (
@REM for %%j in (one_input) do (
    python test_usage.py > 0_sample_output.txt
    @REM for %%i in (6) do (
    for %%i in (1,2,3,4,5,6,7,8,9,10,11) do (
        processing_file.exe < %%j/input%%i.txt >> 0_sample_output.txt
    )
    python test_usage.py > 0_your_output.txt
    @REM for %%i in (6) do (
    for %%i in (1,2,3,4,5,6,7,8,9,10,11) do (
        @REM @echo off
        @REM for /f "tokens=*" %%f in (%%j/input%%i.txt) do (
        @REM     echo %%f
        @REM )
        @REM java tested_file.java < %%j/input%%i.txt >> 0_your_output.txt
        @REM python tested_file.py < %%j/input%%i.txt >> 0_your_output.txt
        @REM python tested_file_lty.py < %%j/input%%i.txt >> 0_your_output.txt
        python tested_file_lyy.py < %%j/input%%i.txt >> 0_your_output.txt
        @echo on
    )
)