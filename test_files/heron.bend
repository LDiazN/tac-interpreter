call ___main main__0
exit 0
@function heron__0 12
assignw f0 1.0
add x__T0 BASE 4
# Copy from "f0" to "x__T0"
assignw x__T0[0] f0
assignw T1 0
assignw T2 50
assignw T3 1
# FOR BEGIN
assignw BASE[8] T1
@label for_start__L1
assignw ___T5 BASE[8]
geq T4 ___T5 T2
goif for_end__L3 T4
# FOR BODY BEGIN
assignw f2 0.5
add x__T6 BASE 4
assignw f3 x__T6[0]
add s__T7 BASE 0
assignw f4 s__T7[0]
add x__T8 BASE 4
assignw f5 x__T8[0]
div f6 f4 f5
add f7 f3 f6
mult f8 f2 f7
add x__T9 BASE 4
# Copy from "f8" to "x__T9"
assignw x__T9[0] f8
# FOR BODY END
@label for_step__L2
add ___T5 ___T5 T3
assignw BASE[8] ___T5
assignw for_result__f1 f8
# FOR END
goto for_start__L1
@label for_end__L3
return for_result__f1
@label heron_end__L0
@endfunction 12
@function main__0 8
readf f9
add x__T10 BASE 0
# Copy from "f9" to "x__T10"
assignw x__T10[0] f9
# Code to calculate parameters
add x__T11 BASE 0
assignw f10 x__T11[0]
# Push parameters
param T12 0
# Copy from "f10" to "T12"
assignw T12[0] f10
call freturn__f11 heron__0
add y__T13 BASE 4
# Copy from "freturn__f11" to "y__T13"
assignw y__T13[0] freturn__f11
add y__T14 BASE 4
assignw f12 y__T14[0]
printf f12
@label main_end__L4
@endfunction 8
@label endProgram
