@string ___OUT_OF_BOUNDS "Avatar doesn't allow using non existing disciples\n"
@string ___DIVSION_BY_0 "Avatar doesn't allow doing besides 0\n"
@string ___UNACTIVE_UNION_FIELD "Avatar doesn't allow using an energy's non-active technique\n"
call ___main main__0
exit 0
@function heron__0 12
goto L1
@label L1
assignw f0 1.0
add _x__T0 BASE 4
# Copy from "f0" to "_x__T0"
assignw _x__T0[0] f0
assignw f_for_result__f1 0.0
assignw T1 0
assignw T2 50
assignw T3 1
# FOR BEGIN
assignw BASE[8] T1
@label _for_start__L2
assignw ____T5 BASE[8]
geq T4 ____T5 T2
goif _for_end__L4 T4
# FOR BODY BEGIN
assignw f2 0.5
add _x__T6 BASE 4
assignw f3 _x__T6[0]
add _s__T7 BASE 0
assignw f4 _s__T7[0]
add _x__T8 BASE 4
assignw f5 _x__T8[0]
eq T9 f5 0
goifnot L5 T9
assignw T10 ___DIVSION_BY_0
print T10
exit 1
@label L5
div f6 f4 f5
add f7 f3 f6
mult f8 f2 f7
add _x__T11 BASE 4
# Copy from "f8" to "_x__T11"
assignw _x__T11[0] f8
# FOR BODY END
@label _for_step__L3
add ____T5 ____T5 T3
assignw BASE[8] ____T5
assignw f_for_result__f1 f8
# FOR END
goto _for_start__L2
@label _for_end__L4
return f_for_result__f1
@label _heron_end__L0
@endfunction 12
@function main__0 24
goto L7
@label L7
@label _while_start__L8
assignb T13 True
goifnot _while_out__L9 T13
assignw T14 STACK
add STACK STACK 40
add T15 BASE 0
assignw T15[0] T14
assignw T15[4] 39
assignb T16 'D'
add T17 T14 0
# Copy from "T16" to "T17"
assignb T17[0] T16
assignb T18 'E'
add T19 T14 1
# Copy from "T18" to "T19"
assignb T19[0] T18
assignb T20 ' '
add T21 T14 2
# Copy from "T20" to "T21"
assignb T21[0] T20
assignb T22 '0'
add T23 T14 3
# Copy from "T22" to "T23"
assignb T23[0] T22
assignb T24 ' '
add T25 T14 4
# Copy from "T24" to "T25"
assignb T25[0] T24
assignb T26 'P'
add T27 T14 5
# Copy from "T26" to "T27"
assignb T27[0] T26
assignb T28 'A'
add T29 T14 6
# Copy from "T28" to "T29"
assignb T29[0] T28
assignb T30 'R'
add T31 T14 7
# Copy from "T30" to "T31"
assignb T31[0] T30
assignb T32 'A'
add T33 T14 8
# Copy from "T32" to "T33"
assignb T33[0] T32
assignb T34 ' '
add T35 T14 9
# Copy from "T34" to "T35"
assignb T35[0] T34
assignb T36 'T'
add T37 T14 10
# Copy from "T36" to "T37"
assignb T37[0] T36
assignb T38 'E'
add T39 T14 11
# Copy from "T38" to "T39"
assignb T39[0] T38
assignb T40 'R'
add T41 T14 12
# Copy from "T40" to "T41"
assignb T41[0] T40
assignb T42 'M'
add T43 T14 13
# Copy from "T42" to "T43"
assignb T43[0] T42
assignb T44 'I'
add T45 T14 14
# Copy from "T44" to "T45"
assignb T45[0] T44
assignb T46 'N'
add T47 T14 15
# Copy from "T46" to "T47"
assignb T47[0] T46
assignb T48 'A'
add T49 T14 16
# Copy from "T48" to "T49"
assignb T49[0] T48
assignb T50 'R'
add T51 T14 17
# Copy from "T50" to "T51"
assignb T51[0] T50
assignb T52 ' '
add T53 T14 18
# Copy from "T52" to "T53"
assignb T53[0] T52
assignb T54 'O'
add T55 T14 19
# Copy from "T54" to "T55"
assignb T55[0] T54
assignb T56 ' '
add T57 T14 20
# Copy from "T56" to "T57"
assignb T57[0] T56
assignb T58 '1'
add T59 T14 21
# Copy from "T58" to "T59"
assignb T59[0] T58
assignb T60 ' '
add T61 T14 22
# Copy from "T60" to "T61"
assignb T61[0] T60
assignb T62 'P'
add T63 T14 23
# Copy from "T62" to "T63"
assignb T63[0] T62
assignb T64 'A'
add T65 T14 24
# Copy from "T64" to "T65"
assignb T65[0] T64
assignb T66 'R'
add T67 T14 25
# Copy from "T66" to "T67"
assignb T67[0] T66
assignb T68 'A'
add T69 T14 26
# Copy from "T68" to "T69"
assignb T69[0] T68
assignb T70 ' '
add T71 T14 27
# Copy from "T70" to "T71"
assignb T71[0] T70
assignb T72 'C'
add T73 T14 28
# Copy from "T72" to "T73"
assignb T73[0] T72
assignb T74 'O'
add T75 T14 29
# Copy from "T74" to "T75"
assignb T75[0] T74
assignb T76 'N'
add T77 T14 30
# Copy from "T76" to "T77"
assignb T77[0] T76
assignb T78 'T'
add T79 T14 31
# Copy from "T78" to "T79"
assignb T79[0] T78
assignb T80 'I'
add T81 T14 32
# Copy from "T80" to "T81"
assignb T81[0] T80
assignb T82 'N'
add T83 T14 33
# Copy from "T82" to "T83"
assignb T83[0] T82
assignb T84 'U'
add T85 T14 34
# Copy from "T84" to "T85"
assignb T85[0] T84
assignb T86 'A'
add T87 T14 35
# Copy from "T86" to "T87"
assignb T87[0] T86
assignb T88 'R'
add T89 T14 36
# Copy from "T88" to "T89"
assignb T89[0] T88
assignb T90 '\n'
add T91 T14 37
# Copy from "T90" to "T91"
assignb T91[0] T90
assignb T92 ' '
add T93 T14 38
# Copy from "T92" to "T93"
assignb T93[0] T92
assignw T94 T15[0]
print T94
readi T95
add _finish__T96 BASE 8
# Copy from "T95" to "_finish__T96"
assignw _finish__T96[0] T95
add _finish__T98 BASE 8
assignw T99 _finish__T98[0]
assignw T100 0
eq T101 T99 T100
goifnot _if_else__L10 T101
# INICIO IF
goto _while_out__L9
goto _if_out__L11
@label _if_else__L10
# INICIO ELSE
assignw T102 STACK
add STACK STACK 48
add T103 BASE 12
assignw T103[0] T102
assignw T103[4] 47
assignb T104 'I'
add T105 T102 0
# Copy from "T104" to "T105"
assignb T105[0] T104
assignb T106 'N'
add T107 T102 1
# Copy from "T106" to "T107"
assignb T107[0] T106
assignb T108 'T'
add T109 T102 2
# Copy from "T108" to "T109"
assignb T109[0] T108
assignb T110 'R'
add T111 T102 3
# Copy from "T110" to "T111"
assignb T111[0] T110
assignb T112 'O'
add T113 T102 4
# Copy from "T112" to "T113"
assignb T113[0] T112
assignb T114 'D'
add T115 T102 5
# Copy from "T114" to "T115"
assignb T115[0] T114
assignb T116 'U'
add T117 T102 6
# Copy from "T116" to "T117"
assignb T117[0] T116
assignb T118 'Z'
add T119 T102 7
# Copy from "T118" to "T119"
assignb T119[0] T118
assignb T120 'C'
add T121 T102 8
# Copy from "T120" to "T121"
assignb T121[0] T120
assignb T122 'A'
add T123 T102 9
# Copy from "T122" to "T123"
assignb T123[0] T122
assignb T124 ' '
add T125 T102 10
# Copy from "T124" to "T125"
assignb T125[0] T124
assignb T126 'U'
add T127 T102 11
# Copy from "T126" to "T127"
assignb T127[0] T126
assignb T128 'N'
add T129 T102 12
# Copy from "T128" to "T129"
assignb T129[0] T128
assignb T130 ' '
add T131 T102 13
# Copy from "T130" to "T131"
assignb T131[0] T130
assignb T132 'N'
add T133 T102 14
# Copy from "T132" to "T133"
assignb T133[0] T132
assignb T134 'U'
add T135 T102 15
# Copy from "T134" to "T135"
assignb T135[0] T134
assignb T136 'M'
add T137 T102 16
# Copy from "T136" to "T137"
assignb T137[0] T136
assignb T138 'E'
add T139 T102 17
# Copy from "T138" to "T139"
assignb T139[0] T138
assignb T140 'R'
add T141 T102 18
# Copy from "T140" to "T141"
assignb T141[0] T140
assignb T142 'O'
add T143 T102 19
# Copy from "T142" to "T143"
assignb T143[0] T142
assignb T144 ' '
add T145 T102 20
# Copy from "T144" to "T145"
assignb T145[0] T144
assignb T146 'R'
add T147 T102 21
# Copy from "T146" to "T147"
assignb T147[0] T146
assignb T148 'E'
add T149 T102 22
# Copy from "T148" to "T149"
assignb T149[0] T148
assignb T150 'A'
add T151 T102 23
# Copy from "T150" to "T151"
assignb T151[0] T150
assignb T152 'L'
add T153 T102 24
# Copy from "T152" to "T153"
assignb T153[0] T152
assignb T154 ' '
add T155 T102 25
# Copy from "T154" to "T155"
assignb T155[0] T154
assignb T156 'M'
add T157 T102 26
# Copy from "T156" to "T157"
assignb T157[0] T156
assignb T158 'A'
add T159 T102 27
# Copy from "T158" to "T159"
assignb T159[0] T158
assignb T160 'Y'
add T161 T102 28
# Copy from "T160" to "T161"
assignb T161[0] T160
assignb T162 'O'
add T163 T102 29
# Copy from "T162" to "T163"
assignb T163[0] T162
assignb T164 'R'
add T165 T102 30
# Copy from "T164" to "T165"
assignb T165[0] T164
assignb T166 ' '
add T167 T102 31
# Copy from "T166" to "T167"
assignb T167[0] T166
assignb T168 'O'
add T169 T102 32
# Copy from "T168" to "T169"
assignb T169[0] T168
assignb T170 ' '
add T171 T102 33
# Copy from "T170" to "T171"
assignb T171[0] T170
assignb T172 'I'
add T173 T102 34
# Copy from "T172" to "T173"
assignb T173[0] T172
assignb T174 'G'
add T175 T102 35
# Copy from "T174" to "T175"
assignb T175[0] T174
assignb T176 'U'
add T177 T102 36
# Copy from "T176" to "T177"
assignb T177[0] T176
assignb T178 'A'
add T179 T102 37
# Copy from "T178" to "T179"
assignb T179[0] T178
assignb T180 'L'
add T181 T102 38
# Copy from "T180" to "T181"
assignb T181[0] T180
assignb T182 ' '
add T183 T102 39
# Copy from "T182" to "T183"
assignb T183[0] T182
assignb T184 'Q'
add T185 T102 40
# Copy from "T184" to "T185"
assignb T185[0] T184
assignb T186 'U'
add T187 T102 41
# Copy from "T186" to "T187"
assignb T187[0] T186
assignb T188 'E'
add T189 T102 42
# Copy from "T188" to "T189"
assignb T189[0] T188
assignb T190 ' '
add T191 T102 43
# Copy from "T190" to "T191"
assignb T191[0] T190
assignb T192 '0'
add T193 T102 44
# Copy from "T192" to "T193"
assignb T193[0] T192
assignb T194 '\n'
add T195 T102 45
# Copy from "T194" to "T195"
assignb T195[0] T194
assignb T196 ' '
add T197 T102 46
# Copy from "T196" to "T197"
assignb T197[0] T196
assignw T198 T103[0]
print T198
readf f9
add _n__T199 BASE 20
# Copy from "f9" to "_n__T199"
assignw _n__T199[0] f9
# Code to calculate parameters
add _n__T200 BASE 20
assignw f10 _n__T200[0]
# Push parameters
param T201 0
# Copy from "f10" to "T201"
assignw T201[0] f10
call f_freturn__f11 heron__0
printf f_freturn__f11
assignb T202 '\n'
printc T202
@label _if_out__L11
goto _while_start__L8
@label _while_out__L9
@label _main_end__L6
@endfunction 24
@label endProgram
