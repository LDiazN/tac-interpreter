call ___main main__0
exit 0
@function it_fib__0 16
add n__T1 BASE 0
assignw T2 n__T1[0]
assignw T3 0
eq T4 T2 T3
goifnot if_else__L1 T4
assignw T5 0
return T5
goto if_out__L2
@label if_else__L1
@label if_out__L2
assignw T6 0
add dp__T7 BASE 4
# Copy from "T6" to "dp__T7"
assignw dp__T7[0] T6
assignw T8 1
add next_dp__T9 BASE 8
# Copy from "T8" to "next_dp__T9"
assignw next_dp__T9[0] T8
assignw T11 0
add n__T12 BASE 0
assignw T13 n__T12[0]
assignw T14 1
# FOR BEGIN
assignw BASE[12] T11
@label for_start__L3
assignw ___T16 BASE[12]
geq T15 ___T16 T13
goif for_end__L5 T15
# FOR BODY BEGIN
add dp__T17 BASE 4
assignw T18 dp__T17[0]
add next_dp__T19 BASE 8
assignw T20 next_dp__T19[0]
add T21 T18 T20
add next_dp__T22 BASE 8
# Copy from "T21" to "next_dp__T22"
assignw next_dp__T22[0] T21
add next_dp__T23 BASE 8
assignw T24 next_dp__T23[0]
add dp__T25 BASE 4
assignw T26 dp__T25[0]
sub T27 T24 T26
add dp__T28 BASE 4
# Copy from "T27" to "dp__T28"
assignw dp__T28[0] T27
# FOR BODY END
@label for_step__L4
add ___T16 ___T16 T14
assignw BASE[12] ___T16
assignw for_result__T10 T27
# FOR END
goto for_start__L3
@label for_end__L5
return for_result__T10
@label it_fib_end__L0
@endfunction 16
@function main__0 24
@label while_start__L7
assignb T30 True
goifnot while_out__L8 T30
assignw T31 STACK
add STACK STACK 36
add T32 BASE 0
assignw T32[0] T31
assignw T32[4] 36
assignb T33 'D'
add T34 T31 0
# Copy from "T33" to "T34"
assignb T34[0] T33
assignb T35 'E'
add T36 T31 1
# Copy from "T35" to "T36"
assignb T36[0] T35
assignb T37 ' '
add T38 T31 2
# Copy from "T37" to "T38"
assignb T38[0] T37
assignb T39 '0'
add T40 T31 3
# Copy from "T39" to "T40"
assignb T40[0] T39
assignb T41 ' '
add T42 T31 4
# Copy from "T41" to "T42"
assignb T42[0] T41
assignb T43 'P'
add T44 T31 5
# Copy from "T43" to "T44"
assignb T44[0] T43
assignb T45 'A'
add T46 T31 6
# Copy from "T45" to "T46"
assignb T46[0] T45
assignb T47 'R'
add T48 T31 7
# Copy from "T47" to "T48"
assignb T48[0] T47
assignb T49 'A'
add T50 T31 8
# Copy from "T49" to "T50"
assignb T50[0] T49
assignb T51 ' '
add T52 T31 9
# Copy from "T51" to "T52"
assignb T52[0] T51
assignb T53 'T'
add T54 T31 10
# Copy from "T53" to "T54"
assignb T54[0] T53
assignb T55 'E'
add T56 T31 11
# Copy from "T55" to "T56"
assignb T56[0] T55
assignb T57 'R'
add T58 T31 12
# Copy from "T57" to "T58"
assignb T58[0] T57
assignb T59 'M'
add T60 T31 13
# Copy from "T59" to "T60"
assignb T60[0] T59
assignb T61 'I'
add T62 T31 14
# Copy from "T61" to "T62"
assignb T62[0] T61
assignb T63 'N'
add T64 T31 15
# Copy from "T63" to "T64"
assignb T64[0] T63
assignb T65 'A'
add T66 T31 16
# Copy from "T65" to "T66"
assignb T66[0] T65
assignb T67 'R'
add T68 T31 17
# Copy from "T67" to "T68"
assignb T68[0] T67
assignb T69 ' '
add T70 T31 18
# Copy from "T69" to "T70"
assignb T70[0] T69
assignb T71 'O'
add T72 T31 19
# Copy from "T71" to "T72"
assignb T72[0] T71
assignb T73 ' '
add T74 T31 20
# Copy from "T73" to "T74"
assignb T74[0] T73
assignb T75 '1'
add T76 T31 21
# Copy from "T75" to "T76"
assignb T76[0] T75
assignb T77 ' '
add T78 T31 22
# Copy from "T77" to "T78"
assignb T78[0] T77
assignb T79 'P'
add T80 T31 23
# Copy from "T79" to "T80"
assignb T80[0] T79
assignb T81 'A'
add T82 T31 24
# Copy from "T81" to "T82"
assignb T82[0] T81
assignb T83 'R'
add T84 T31 25
# Copy from "T83" to "T84"
assignb T84[0] T83
assignb T85 'A'
add T86 T31 26
# Copy from "T85" to "T86"
assignb T86[0] T85
assignb T87 ' '
add T88 T31 27
# Copy from "T87" to "T88"
assignb T88[0] T87
assignb T89 'F'
add T90 T31 28
# Copy from "T89" to "T90"
assignb T90[0] T89
assignb T91 'I'
add T92 T31 29
# Copy from "T91" to "T92"
assignb T92[0] T91
assignb T93 'B'
add T94 T31 30
# Copy from "T93" to "T94"
assignb T94[0] T93
assignb T95 ' '
add T96 T31 31
# Copy from "T95" to "T96"
assignb T96[0] T95
assignb T97 'I'
add T98 T31 32
# Copy from "T97" to "T98"
assignb T98[0] T97
assignb T99 'T'
add T100 T31 33
# Copy from "T99" to "T100"
assignb T100[0] T99
assignb T101 'E'
add T102 T31 34
# Copy from "T101" to "T102"
assignb T102[0] T101
assignb T103 'R'
add T104 T31 35
# Copy from "T103" to "T104"
assignb T104[0] T103
assignw T105 T32[0]
print T105
readi T106
add finish__T107 BASE 8
# Copy from "T106" to "finish__T107"
assignw finish__T107[0] T106
add finish__T109 BASE 8
assignw T110 finish__T109[0]
assignw T111 0
eq T112 T110 T111
goifnot if_else__L9 T112
goto while_out__L8
goto if_out__L10
@label if_else__L9
assignw T113 STACK
add STACK STACK 40
add T114 BASE 12
assignw T114[0] T113
assignw T114[4] 40
assignb T115 'I'
add T116 T113 0
# Copy from "T115" to "T116"
assignb T116[0] T115
assignb T117 'N'
add T118 T113 1
# Copy from "T117" to "T118"
assignb T118[0] T117
assignb T119 'T'
add T120 T113 2
# Copy from "T119" to "T120"
assignb T120[0] T119
assignb T121 'R'
add T122 T113 3
# Copy from "T121" to "T122"
assignb T122[0] T121
assignb T123 'O'
add T124 T113 4
# Copy from "T123" to "T124"
assignb T124[0] T123
assignb T125 'D'
add T126 T113 5
# Copy from "T125" to "T126"
assignb T126[0] T125
assignb T127 'U'
add T128 T113 6
# Copy from "T127" to "T128"
assignb T128[0] T127
assignb T129 'Z'
add T130 T113 7
# Copy from "T129" to "T130"
assignb T130[0] T129
assignb T131 'C'
add T132 T113 8
# Copy from "T131" to "T132"
assignb T132[0] T131
assignb T133 'A'
add T134 T113 9
# Copy from "T133" to "T134"
assignb T134[0] T133
assignb T135 ' '
add T136 T113 10
# Copy from "T135" to "T136"
assignb T136[0] T135
assignb T137 'U'
add T138 T113 11
# Copy from "T137" to "T138"
assignb T138[0] T137
assignb T139 'N'
add T140 T113 12
# Copy from "T139" to "T140"
assignb T140[0] T139
assignb T141 ' '
add T142 T113 13
# Copy from "T141" to "T142"
assignb T142[0] T141
assignb T143 'N'
add T144 T113 14
# Copy from "T143" to "T144"
assignb T144[0] T143
assignb T145 'U'
add T146 T113 15
# Copy from "T145" to "T146"
assignb T146[0] T145
assignb T147 'M'
add T148 T113 16
# Copy from "T147" to "T148"
assignb T148[0] T147
assignb T149 'E'
add T150 T113 17
# Copy from "T149" to "T150"
assignb T150[0] T149
assignb T151 'R'
add T152 T113 18
# Copy from "T151" to "T152"
assignb T152[0] T151
assignb T153 'O'
add T154 T113 19
# Copy from "T153" to "T154"
assignb T154[0] T153
assignb T155 ' '
add T156 T113 20
# Copy from "T155" to "T156"
assignb T156[0] T155
assignb T157 'M'
add T158 T113 21
# Copy from "T157" to "T158"
assignb T158[0] T157
assignb T159 'A'
add T160 T113 22
# Copy from "T159" to "T160"
assignb T160[0] T159
assignb T161 'Y'
add T162 T113 23
# Copy from "T161" to "T162"
assignb T162[0] T161
assignb T163 'O'
add T164 T113 24
# Copy from "T163" to "T164"
assignb T164[0] T163
assignb T165 'R'
add T166 T113 25
# Copy from "T165" to "T166"
assignb T166[0] T165
assignb T167 ' '
add T168 T113 26
# Copy from "T167" to "T168"
assignb T168[0] T167
assignb T169 'O'
add T170 T113 27
# Copy from "T169" to "T170"
assignb T170[0] T169
assignb T171 ' '
add T172 T113 28
# Copy from "T171" to "T172"
assignb T172[0] T171
assignb T173 'I'
add T174 T113 29
# Copy from "T173" to "T174"
assignb T174[0] T173
assignb T175 'G'
add T176 T113 30
# Copy from "T175" to "T176"
assignb T176[0] T175
assignb T177 'U'
add T178 T113 31
# Copy from "T177" to "T178"
assignb T178[0] T177
assignb T179 'A'
add T180 T113 32
# Copy from "T179" to "T180"
assignb T180[0] T179
assignb T181 'L'
add T182 T113 33
# Copy from "T181" to "T182"
assignb T182[0] T181
assignb T183 ' '
add T184 T113 34
# Copy from "T183" to "T184"
assignb T184[0] T183
assignb T185 'Q'
add T186 T113 35
# Copy from "T185" to "T186"
assignb T186[0] T185
assignb T187 'U'
add T188 T113 36
# Copy from "T187" to "T188"
assignb T188[0] T187
assignb T189 'E'
add T190 T113 37
# Copy from "T189" to "T190"
assignb T190[0] T189
assignb T191 ' '
add T192 T113 38
# Copy from "T191" to "T192"
assignb T192[0] T191
assignb T193 '0'
add T194 T113 39
# Copy from "T193" to "T194"
assignb T194[0] T193
assignw T195 T114[0]
print T195
readi T196
add n__T197 BASE 20
# Copy from "T196" to "n__T197"
assignw n__T197[0] T196
# Code to calculate parameters
add n__T198 BASE 20
assignw T199 n__T198[0]
# Push parameters
param T201 0
# Copy from "T199" to "T201"
assignw T201[0] T199
call freturn__T200 it_fib__0
printi freturn__T200
@label if_out__L10
goto while_start__L7
@label while_out__L8
@label main_end__L6
@endfunction 24
@label endProgram
