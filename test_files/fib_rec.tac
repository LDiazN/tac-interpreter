@string ___OUT_OF_BOUNDS "Avatar doesn't allow using non existing disciples\n"
@string ___DIVSION_BY_0 "Avatar doesn't allow doing besides 0\n"
@string ___UNACTIVE_UNION_FIELD "Avatar doesn't allow using an energy's non-active technique\n"
call ___main main__0
exit 0
@function rec_fib__0 4
goto L1
@label L1
add _n__T1 BASE 0
assignw T2 _n__T1[0]
assignw T3 0
eq T4 T2 T3
goifnot _if_else__L2 T4
# INICIO IF
assignw T5 0
assignw T0 T5
goto _if_out__L3
@label _if_else__L2
# INICIO ELSE
add _n__T7 BASE 0
assignw T8 _n__T7[0]
assignw T9 1
eq T10 T8 T9
goifnot _if_else__L4 T10
# INICIO IF
assignw T11 1
assignw T6 T11
goto _if_out__L5
@label _if_else__L4
# INICIO ELSE
# Code to calculate parameters
add _n__T12 BASE 0
assignw T13 _n__T12[0]
assignw T14 1
sub T15 T13 T14
# Push parameters
param T17 0
# Copy from "T15" to "T17"
assignw T17[0] T15
call _freturn__T16 rec_fib__0
# Code to calculate parameters
add _n__T18 BASE 0
assignw T19 _n__T18[0]
assignw T20 2
sub T21 T19 T20
# Push parameters
param T23 0
# Copy from "T21" to "T23"
assignw T23[0] T21
call _freturn__T22 rec_fib__0
add T24 _freturn__T16 _freturn__T22
assignw T6 T24
@label _if_out__L5
assignw T0 T6
@label _if_out__L3
return T0
@label _rec_fib_end__L0
@endfunction 4
@function main__0 24
goto L7
@label L7
@label _while_start__L8
assignb T26 True
goifnot _while_out__L9 T26
assignw T27 STACK
add STACK STACK 40
add T28 BASE 0
assignw T28[0] T27
assignw T28[4] 37
assignb T29 'D'
add T30 T27 0
# Copy from "T29" to "T30"
assignb T30[0] T29
assignb T31 'E'
add T32 T27 1
# Copy from "T31" to "T32"
assignb T32[0] T31
assignb T33 ' '
add T34 T27 2
# Copy from "T33" to "T34"
assignb T34[0] T33
assignb T35 '0'
add T36 T27 3
# Copy from "T35" to "T36"
assignb T36[0] T35
assignb T37 ' '
add T38 T27 4
# Copy from "T37" to "T38"
assignb T38[0] T37
assignb T39 'P'
add T40 T27 5
# Copy from "T39" to "T40"
assignb T40[0] T39
assignb T41 'A'
add T42 T27 6
# Copy from "T41" to "T42"
assignb T42[0] T41
assignb T43 'R'
add T44 T27 7
# Copy from "T43" to "T44"
assignb T44[0] T43
assignb T45 'A'
add T46 T27 8
# Copy from "T45" to "T46"
assignb T46[0] T45
assignb T47 ' '
add T48 T27 9
# Copy from "T47" to "T48"
assignb T48[0] T47
assignb T49 'T'
add T50 T27 10
# Copy from "T49" to "T50"
assignb T50[0] T49
assignb T51 'E'
add T52 T27 11
# Copy from "T51" to "T52"
assignb T52[0] T51
assignb T53 'R'
add T54 T27 12
# Copy from "T53" to "T54"
assignb T54[0] T53
assignb T55 'M'
add T56 T27 13
# Copy from "T55" to "T56"
assignb T56[0] T55
assignb T57 'I'
add T58 T27 14
# Copy from "T57" to "T58"
assignb T58[0] T57
assignb T59 'N'
add T60 T27 15
# Copy from "T59" to "T60"
assignb T60[0] T59
assignb T61 'A'
add T62 T27 16
# Copy from "T61" to "T62"
assignb T62[0] T61
assignb T63 'R'
add T64 T27 17
# Copy from "T63" to "T64"
assignb T64[0] T63
assignb T65 ' '
add T66 T27 18
# Copy from "T65" to "T66"
assignb T66[0] T65
assignb T67 'O'
add T68 T27 19
# Copy from "T67" to "T68"
assignb T68[0] T67
assignb T69 ' '
add T70 T27 20
# Copy from "T69" to "T70"
assignb T70[0] T69
assignb T71 '1'
add T72 T27 21
# Copy from "T71" to "T72"
assignb T72[0] T71
assignb T73 ' '
add T74 T27 22
# Copy from "T73" to "T74"
assignb T74[0] T73
assignb T75 'P'
add T76 T27 23
# Copy from "T75" to "T76"
assignb T76[0] T75
assignb T77 'A'
add T78 T27 24
# Copy from "T77" to "T78"
assignb T78[0] T77
assignb T79 'R'
add T80 T27 25
# Copy from "T79" to "T80"
assignb T80[0] T79
assignb T81 'A'
add T82 T27 26
# Copy from "T81" to "T82"
assignb T82[0] T81
assignb T83 ' '
add T84 T27 27
# Copy from "T83" to "T84"
assignb T84[0] T83
assignb T85 'F'
add T86 T27 28
# Copy from "T85" to "T86"
assignb T86[0] T85
assignb T87 'I'
add T88 T27 29
# Copy from "T87" to "T88"
assignb T88[0] T87
assignb T89 'B'
add T90 T27 30
# Copy from "T89" to "T90"
assignb T90[0] T89
assignb T91 ' '
add T92 T27 31
# Copy from "T91" to "T92"
assignb T92[0] T91
assignb T93 'R'
add T94 T27 32
# Copy from "T93" to "T94"
assignb T94[0] T93
assignb T95 'E'
add T96 T27 33
# Copy from "T95" to "T96"
assignb T96[0] T95
assignb T97 'C'
add T98 T27 34
# Copy from "T97" to "T98"
assignb T98[0] T97
assignb T99 '\n'
add T100 T27 35
# Copy from "T99" to "T100"
assignb T100[0] T99
assignb T101 ' '
add T102 T27 36
# Copy from "T101" to "T102"
assignb T102[0] T101
assignw T103 T28[0]
print T103
readi T104
add _finish__T105 BASE 8
# Copy from "T104" to "_finish__T105"
assignw _finish__T105[0] T104
add _finish__T107 BASE 8
assignw T108 _finish__T107[0]
assignw T109 0
eq T110 T108 T109
goifnot _if_else__L10 T110
# INICIO IF
goto _while_out__L9
goto _if_out__L11
@label _if_else__L10
# INICIO ELSE
assignw T111 STACK
add STACK STACK 44
add T112 BASE 12
assignw T112[0] T111
assignw T112[4] 42
assignb T113 'I'
add T114 T111 0
# Copy from "T113" to "T114"
assignb T114[0] T113
assignb T115 'N'
add T116 T111 1
# Copy from "T115" to "T116"
assignb T116[0] T115
assignb T117 'T'
add T118 T111 2
# Copy from "T117" to "T118"
assignb T118[0] T117
assignb T119 'R'
add T120 T111 3
# Copy from "T119" to "T120"
assignb T120[0] T119
assignb T121 'O'
add T122 T111 4
# Copy from "T121" to "T122"
assignb T122[0] T121
assignb T123 'D'
add T124 T111 5
# Copy from "T123" to "T124"
assignb T124[0] T123
assignb T125 'U'
add T126 T111 6
# Copy from "T125" to "T126"
assignb T126[0] T125
assignb T127 'Z'
add T128 T111 7
# Copy from "T127" to "T128"
assignb T128[0] T127
assignb T129 'C'
add T130 T111 8
# Copy from "T129" to "T130"
assignb T130[0] T129
assignb T131 'A'
add T132 T111 9
# Copy from "T131" to "T132"
assignb T132[0] T131
assignb T133 ' '
add T134 T111 10
# Copy from "T133" to "T134"
assignb T134[0] T133
assignb T135 'U'
add T136 T111 11
# Copy from "T135" to "T136"
assignb T136[0] T135
assignb T137 'N'
add T138 T111 12
# Copy from "T137" to "T138"
assignb T138[0] T137
assignb T139 ' '
add T140 T111 13
# Copy from "T139" to "T140"
assignb T140[0] T139
assignb T141 'N'
add T142 T111 14
# Copy from "T141" to "T142"
assignb T142[0] T141
assignb T143 'U'
add T144 T111 15
# Copy from "T143" to "T144"
assignb T144[0] T143
assignb T145 'M'
add T146 T111 16
# Copy from "T145" to "T146"
assignb T146[0] T145
assignb T147 'E'
add T148 T111 17
# Copy from "T147" to "T148"
assignb T148[0] T147
assignb T149 'R'
add T150 T111 18
# Copy from "T149" to "T150"
assignb T150[0] T149
assignb T151 'O'
add T152 T111 19
# Copy from "T151" to "T152"
assignb T152[0] T151
assignb T153 ' '
add T154 T111 20
# Copy from "T153" to "T154"
assignb T154[0] T153
assignb T155 'M'
add T156 T111 21
# Copy from "T155" to "T156"
assignb T156[0] T155
assignb T157 'A'
add T158 T111 22
# Copy from "T157" to "T158"
assignb T158[0] T157
assignb T159 'Y'
add T160 T111 23
# Copy from "T159" to "T160"
assignb T160[0] T159
assignb T161 'O'
add T162 T111 24
# Copy from "T161" to "T162"
assignb T162[0] T161
assignb T163 'R'
add T164 T111 25
# Copy from "T163" to "T164"
assignb T164[0] T163
assignb T165 ' '
add T166 T111 26
# Copy from "T165" to "T166"
assignb T166[0] T165
assignb T167 'O'
add T168 T111 27
# Copy from "T167" to "T168"
assignb T168[0] T167
assignb T169 ' '
add T170 T111 28
# Copy from "T169" to "T170"
assignb T170[0] T169
assignb T171 'I'
add T172 T111 29
# Copy from "T171" to "T172"
assignb T172[0] T171
assignb T173 'G'
add T174 T111 30
# Copy from "T173" to "T174"
assignb T174[0] T173
assignb T175 'U'
add T176 T111 31
# Copy from "T175" to "T176"
assignb T176[0] T175
assignb T177 'A'
add T178 T111 32
# Copy from "T177" to "T178"
assignb T178[0] T177
assignb T179 'L'
add T180 T111 33
# Copy from "T179" to "T180"
assignb T180[0] T179
assignb T181 ' '
add T182 T111 34
# Copy from "T181" to "T182"
assignb T182[0] T181
assignb T183 'Q'
add T184 T111 35
# Copy from "T183" to "T184"
assignb T184[0] T183
assignb T185 'U'
add T186 T111 36
# Copy from "T185" to "T186"
assignb T186[0] T185
assignb T187 'E'
add T188 T111 37
# Copy from "T187" to "T188"
assignb T188[0] T187
assignb T189 ' '
add T190 T111 38
# Copy from "T189" to "T190"
assignb T190[0] T189
assignb T191 '0'
add T192 T111 39
# Copy from "T191" to "T192"
assignb T192[0] T191
assignb T193 '\n'
add T194 T111 40
# Copy from "T193" to "T194"
assignb T194[0] T193
assignb T195 ' '
add T196 T111 41
# Copy from "T195" to "T196"
assignb T196[0] T195
assignw T197 T112[0]
print T197
readi T198
add _n__T199 BASE 20
# Copy from "T198" to "_n__T199"
assignw _n__T199[0] T198
# Code to calculate parameters
add _n__T200 BASE 20
assignw T201 _n__T200[0]
# Push parameters
param T203 0
# Copy from "T201" to "T203"
assignw T203[0] T201
call _freturn__T202 rec_fib__0
printi _freturn__T202
assignb T204 '\n'
printc T204
@label _if_out__L11
goto _while_start__L8
@label _while_out__L9
@label _main_end__L6
@endfunction 24
@label endProgram
