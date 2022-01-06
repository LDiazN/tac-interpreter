call ___main main__0
exit 0
@function rec_fib__0 4
add _n__T1 BASE 0
assignw T2 _n__T1[0]
assignw T3 0
eq T4 T2 T3
goifnot _if_else__L1 T4
assignw T5 0
assignw T0 T5
goto _if_out__L2
@label _if_else__L1
add _n__T7 BASE 0
assignw T8 _n__T7[0]
assignw T9 1
eq T10 T8 T9
goifnot _if_else__L3 T10
assignw T11 1
assignw T6 T11
goto _if_out__L4
@label _if_else__L3
add _n__T12 BASE 0
assignw T13 _n__T12[0]
assignw T14 1
sub T15 T13 T14
param T17 0
assignw T17[0] T15
call _freturn__T16 rec_fib__0
add _n__T18 BASE 0
assignw T19 _n__T18[0]
assignw T20 2
sub T21 T19 T20
param T23 0
assignw T23[0] T21
call _freturn__T22 rec_fib__0
add T24 _freturn__T16 _freturn__T22
assignw T6 T24
@label _if_out__L4
assignw T0 T6
@label _if_out__L2
return T0
@label _rec_fib_end__L0
@endfunction 4
@function main__0 24
@label _while_start__L6
assignb T26 True
goifnot _while_out__L7 T26
assignw T27 STACK
add STACK STACK 36
add T28 BASE 0
assignw T28[0] T27
assignw T28[4] 36
assignb T29 'D'
add T30 T27 0
assignb T30[0] T29
assignb T31 'E'
add T32 T27 1
assignb T32[0] T31
assignb T33 ' '
add T34 T27 2
assignb T34[0] T33
assignb T35 '0'
add T36 T27 3
assignb T36[0] T35
assignb T37 ' '
add T38 T27 4
assignb T38[0] T37
assignb T39 'P'
add T40 T27 5
assignb T40[0] T39
assignb T41 'A'
add T42 T27 6
assignb T42[0] T41
assignb T43 'R'
add T44 T27 7
assignb T44[0] T43
assignb T45 'A'
add T46 T27 8
assignb T46[0] T45
assignb T47 ' '
add T48 T27 9
assignb T48[0] T47
assignb T49 'T'
add T50 T27 10
assignb T50[0] T49
assignb T51 'E'
add T52 T27 11
assignb T52[0] T51
assignb T53 'R'
add T54 T27 12
assignb T54[0] T53
assignb T55 'M'
add T56 T27 13
assignb T56[0] T55
assignb T57 'I'
add T58 T27 14
assignb T58[0] T57
assignb T59 'N'
add T60 T27 15
assignb T60[0] T59
assignb T61 'A'
add T62 T27 16
assignb T62[0] T61
assignb T63 'R'
add T64 T27 17
assignb T64[0] T63
assignb T65 ' '
add T66 T27 18
assignb T66[0] T65
assignb T67 'O'
add T68 T27 19
assignb T68[0] T67
assignb T69 ' '
add T70 T27 20
assignb T70[0] T69
assignb T71 '1'
add T72 T27 21
assignb T72[0] T71
assignb T73 ' '
add T74 T27 22
assignb T74[0] T73
assignb T75 'P'
add T76 T27 23
assignb T76[0] T75
assignb T77 'A'
add T78 T27 24
assignb T78[0] T77
assignb T79 'R'
add T80 T27 25
assignb T80[0] T79
assignb T81 'A'
add T82 T27 26
assignb T82[0] T81
assignb T83 ' '
add T84 T27 27
assignb T84[0] T83
assignb T85 'F'
add T86 T27 28
assignb T86[0] T85
assignb T87 'I'
add T88 T27 29
assignb T88[0] T87
assignb T89 'B'
add T90 T27 30
assignb T90[0] T89
assignb T91 ' '
add T92 T27 31
assignb T92[0] T91
assignb T93 'I'
add T94 T27 32
assignb T94[0] T93
assignb T95 'T'
add T96 T27 33
assignb T96[0] T95
assignb T97 'E'
add T98 T27 34
assignb T98[0] T97
assignb T99 'R'
add T100 T27 35
assignb T100[0] T99
assignw T101 T28[0]
print T101
readi T102
add _finish__T103 BASE 8
assignw _finish__T103[0] T102
add _finish__T105 BASE 8
assignw T106 _finish__T105[0]
assignw T107 0
eq T108 T106 T107
goifnot _if_else__L8 T108
goto _while_out__L7
goto _if_out__L9
@label _if_else__L8
assignw T109 STACK
add STACK STACK 40
add T110 BASE 12
assignw T110[0] T109
assignw T110[4] 40
assignb T111 'I'
add T112 T109 0
assignb T112[0] T111
assignb T113 'N'
add T114 T109 1
assignb T114[0] T113
assignb T115 'T'
add T116 T109 2
assignb T116[0] T115
assignb T117 'R'
add T118 T109 3
assignb T118[0] T117
assignb T119 'O'
add T120 T109 4
assignb T120[0] T119
assignb T121 'D'
add T122 T109 5
assignb T122[0] T121
assignb T123 'U'
add T124 T109 6
assignb T124[0] T123
assignb T125 'Z'
add T126 T109 7
assignb T126[0] T125
assignb T127 'C'
add T128 T109 8
assignb T128[0] T127
assignb T129 'A'
add T130 T109 9
assignb T130[0] T129
assignb T131 ' '
add T132 T109 10
assignb T132[0] T131
assignb T133 'U'
add T134 T109 11
assignb T134[0] T133
assignb T135 'N'
add T136 T109 12
assignb T136[0] T135
assignb T137 ' '
add T138 T109 13
assignb T138[0] T137
assignb T139 'N'
add T140 T109 14
assignb T140[0] T139
assignb T141 'U'
add T142 T109 15
assignb T142[0] T141
assignb T143 'M'
add T144 T109 16
assignb T144[0] T143
assignb T145 'E'
add T146 T109 17
assignb T146[0] T145
assignb T147 'R'
add T148 T109 18
assignb T148[0] T147
assignb T149 'O'
add T150 T109 19
assignb T150[0] T149
assignb T151 ' '
add T152 T109 20
assignb T152[0] T151
assignb T153 'M'
add T154 T109 21
assignb T154[0] T153
assignb T155 'A'
add T156 T109 22
assignb T156[0] T155
assignb T157 'Y'
add T158 T109 23
assignb T158[0] T157
assignb T159 'O'
add T160 T109 24
assignb T160[0] T159
assignb T161 'R'
add T162 T109 25
assignb T162[0] T161
assignb T163 ' '
add T164 T109 26
assignb T164[0] T163
assignb T165 'O'
add T166 T109 27
assignb T166[0] T165
assignb T167 ' '
add T168 T109 28
assignb T168[0] T167
assignb T169 'I'
add T170 T109 29
assignb T170[0] T169
assignb T171 'G'
add T172 T109 30
assignb T172[0] T171
assignb T173 'U'
add T174 T109 31
assignb T174[0] T173
assignb T175 'A'
add T176 T109 32
assignb T176[0] T175
assignb T177 'L'
add T178 T109 33
assignb T178[0] T177
assignb T179 ' '
add T180 T109 34
assignb T180[0] T179
assignb T181 'Q'
add T182 T109 35
assignb T182[0] T181
assignb T183 'U'
add T184 T109 36
assignb T184[0] T183
assignb T185 'E'
add T186 T109 37
assignb T186[0] T185
assignb T187 ' '
add T188 T109 38
assignb T188[0] T187
assignb T189 '0'
add T190 T109 39
assignb T190[0] T189
assignw T191 T110[0]
print T191
readi T192
add _n__T193 BASE 20
assignw _n__T193[0] T192
add _n__T194 BASE 20
assignw T195 _n__T194[0]
param T197 0
assignw T197[0] T195
call _freturn__T196 rec_fib__0
printi _freturn__T196
@label _if_out__L9
goto _while_start__L6
@label _while_out__L7
@label _main_end__L5
@endfunction 24
@label endProgram
