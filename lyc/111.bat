

@echo off
@REM for %%j in (easy_input) do (
@REM for %%j in (diff_input) do (
for %%j in (comp_input) do (
    python test_usage.py > 0_sample_output.txt
    for %%i in (1,2,3,4,5,6,7,8,9,10,11) do (
        processing_file.exe < %%j/input%%i.txt >> 0_sample_output.txt
    )
    python test_usage.py > 0_your_output.txt
    for %%i in (1,2,3,4,5,6,7,8,9,10,11) do (
        @echo off
        for /f "tokens=*" %%f in (%%j/input%%i.txt) do (
            echo %%f
        )
        python check9.py < %%j/input%%i.txt >> 0_your_output.txt
        @echo on
    )
)