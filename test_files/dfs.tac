@string ___OUT_OF_BOUNDS "Avatar doesn't allow using non existing disciples\n"
@string ___DIVSION_BY_0 "Avatar doesn't allow doing besides 0\n"
@string ___UNACTIVE_UNION_FIELD "Avatar doesn't allow using an energy's non-active technique\n"
@staticv _FROM__0__L0 8
@staticv _TO__0__L0 8
@staticv _VIS__0__L0 8
@staticv _E__0__L6 4
@staticv _V__0__L13 4
# _FROM__T0 := _FROM__0__L0 # address of variable FROM
assignw _FROM__T0 _FROM__0__L0
assignw _FROM__T0[0] STACK
assignw T1 169
assignw _FROM__T0[4] T1
mult T1 T1 4
add T1 T1 3
div T1 T1 4
mult T1 T1 4
add STACK STACK T1
# _TO__T2 := _TO__0__L0 # address of variable TO
assignw _TO__T2 _TO__0__L0
assignw _TO__T2[0] STACK
assignw T3 169
assignw _TO__T2[4] T3
mult T3 T3 4
add T3 T3 3
div T3 T3 4
mult T3 T3 4
add STACK STACK T3
# _VIS__T4 := _VIS__0__L0 # address of variable VIS
assignw _VIS__T4 _VIS__0__L0
assignw _VIS__T4[0] STACK
assignw T5 169
assignw _VIS__T4[4] T5
mult T5 T5 1
add T5 T5 3
div T5 T5 4
mult T5 T5 4
add STACK STACK T5
call ___main main__0
exit 0
@function dfs__0 16
goto L1
@label L1
# _VIS__T6 := _VIS__0__L0 # address of variable VIS
assignw _VIS__T6 _VIS__0__L0
add _u__T7 BASE 0
assignw T8 _u__T7[0]
assignb T9 True
assignw T10 _VIS__T6[0]
assignw T11 _VIS__T6[4]
lt T13 T8 0
geq T14 T8 T11
or T15 T13 T14
goifnot L2 T15
# EXIT POR OUT OF BOUNDS
assignw T16 ___OUT_OF_BOUNDS
print T16
exit 1
@label L2
mult T12 T8 1
add T12 T12 T10
# Copy from "T9" to "T12"
assignb T12[0] T9
add _u__T17 BASE 0
assignw T18 _u__T17[0]
printi T18
assignb T19 '\n'
printc T19
assignw T21 0
# _E__T22 := _E__0__L6 # address of variable E
assignw _E__T22 _E__0__L6
assignw T23 _E__T22[0]
assignw T24 1
# FOR BEGIN
assignw BASE[4] T21
@label _for_start__L3
assignw _i__T26 BASE[4]
geq T25 _i__T26 T23
goif _for_end__L5 T25
# FOR BODY BEGIN
# _FROM__T27 := _FROM__0__L0 # address of variable FROM
assignw _FROM__T27 _FROM__0__L0
add _i__T28 BASE 4
assignw T29 _i__T28[0]
assignw T30 _FROM__T27[0]
assignw T31 _FROM__T27[4]
lt T33 T29 0
geq T34 T29 T31
or T35 T33 T34
goifnot L6 T35
# EXIT POR OUT OF BOUNDS
assignw T36 ___OUT_OF_BOUNDS
print T36
exit 1
@label L6
mult T32 T29 4
add T32 T32 T30
assignw T37 T32[0]
add _a__T38 BASE 8
# Copy from "T37" to "_a__T38"
assignw _a__T38[0] T37
# _TO__T39 := _TO__0__L0 # address of variable TO
assignw _TO__T39 _TO__0__L0
add _i__T40 BASE 4
assignw T41 _i__T40[0]
assignw T42 _TO__T39[0]
assignw T43 _TO__T39[4]
lt T45 T41 0
geq T46 T41 T43
or T47 T45 T46
goifnot L7 T47
# EXIT POR OUT OF BOUNDS
assignw T48 ___OUT_OF_BOUNDS
print T48
exit 1
@label L7
mult T44 T41 4
add T44 T44 T42
assignw T49 T44[0]
add _b__T50 BASE 12
# Copy from "T49" to "_b__T50"
assignw _b__T50[0] T49
add _a__T52 BASE 8
assignw T53 _a__T52[0]
add _u__T54 BASE 0
assignw T55 _u__T54[0]
eq T56 T53 T55
# _VIS__T57 := _VIS__0__L0 # address of variable VIS
assignw _VIS__T57 _VIS__0__L0
add _b__T58 BASE 12
assignw T59 _b__T58[0]
assignw T60 _VIS__T57[0]
assignw T61 _VIS__T57[4]
lt T63 T59 0
geq T64 T59 T61
or T65 T63 T64
goifnot L10 T65
# EXIT POR OUT OF BOUNDS
assignw T66 ___OUT_OF_BOUNDS
print T66
exit 1
@label L10
mult T62 T59 1
add T62 T62 T60
assignb T67 T62[0]
assignb T68 False
eq T69 T67 T68
and T70 T56 T69
goifnot _if_else__L8 T70
# INICIO IF
# Code to calculate parameters
add _b__T71 BASE 12
assignw T72 _b__T71[0]
# Push parameters
param T74 0
# Copy from "T72" to "T74"
assignw T74[0] T72
call _freturn__T73 dfs__0
goto _if_out__L9
@label _if_else__L8
# INICIO ELSE
@label _if_out__L9
# FOR BODY END
@label _for_step__L4
add _i__T26 _i__T26 T24
assignw BASE[4] _i__T26
# FOR END
goto _for_start__L3
@label _for_end__L5
@label _dfs_end__L0
@endfunction 16
@function main__0 32
goto L12
@label L12
assignw T75 STACK
add STACK STACK 24
add T76 BASE 0
assignw T76[0] T75
assignw T76[4] 23
assignb T77 'D'
add T78 T75 0
# Copy from "T77" to "T78"
assignb T78[0] T77
assignb T79 'E'
add T80 T75 1
# Copy from "T79" to "T80"
assignb T80[0] T79
assignb T81 ' '
add T82 T75 2
# Copy from "T81" to "T82"
assignb T82[0] T81
assignb T83 'E'
add T84 T75 3
# Copy from "T83" to "T84"
assignb T84[0] T83
assignb T85 'L'
add T86 T75 4
# Copy from "T85" to "T86"
assignb T86[0] T85
assignb T87 ' '
add T88 T75 5
# Copy from "T87" to "T88"
assignb T88[0] T87
assignb T89 'N'
add T90 T75 6
# Copy from "T89" to "T90"
assignb T90[0] T89
assignb T91 'U'
add T92 T75 7
# Copy from "T91" to "T92"
assignb T92[0] T91
assignb T93 'M'
add T94 T75 8
# Copy from "T93" to "T94"
assignb T94[0] T93
assignb T95 'E'
add T96 T75 9
# Copy from "T95" to "T96"
assignb T96[0] T95
assignb T97 'R'
add T98 T75 10
# Copy from "T97" to "T98"
assignb T98[0] T97
assignb T99 'O'
add T100 T75 11
# Copy from "T99" to "T100"
assignb T100[0] T99
assignb T101 ' '
add T102 T75 12
# Copy from "T101" to "T102"
assignb T102[0] T101
assignb T103 'D'
add T104 T75 13
# Copy from "T103" to "T104"
assignb T104[0] T103
assignb T105 'E'
add T106 T75 14
# Copy from "T105" to "T106"
assignb T106[0] T105
assignb T107 ' '
add T108 T75 15
# Copy from "T107" to "T108"
assignb T108[0] T107
assignb T109 'N'
add T110 T75 16
# Copy from "T109" to "T110"
assignb T110[0] T109
assignb T111 'O'
add T112 T75 17
# Copy from "T111" to "T112"
assignb T112[0] T111
assignb T113 'D'
add T114 T75 18
# Copy from "T113" to "T114"
assignb T114[0] T113
assignb T115 'O'
add T116 T75 19
# Copy from "T115" to "T116"
assignb T116[0] T115
assignb T117 'S'
add T118 T75 20
# Copy from "T117" to "T118"
assignb T118[0] T117
assignb T119 '\n'
add T120 T75 21
# Copy from "T119" to "T120"
assignb T120[0] T119
assignb T121 ' '
add T122 T75 22
# Copy from "T121" to "T122"
assignb T122[0] T121
assignw T123 T76[0]
print T123
readi T124
# _V__T125 := _V__0__L13 # address of variable V
assignw _V__T125 _V__0__L13
# Copy from "T124" to "_V__T125"
assignw _V__T125[0] T124
assignw T126 STACK
add STACK STACK 24
add T127 BASE 8
assignw T127[0] T126
assignw T127[4] 23
assignb T128 'D'
add T129 T126 0
# Copy from "T128" to "T129"
assignb T129[0] T128
assignb T130 'E'
add T131 T126 1
# Copy from "T130" to "T131"
assignb T131[0] T130
assignb T132 ' '
add T133 T126 2
# Copy from "T132" to "T133"
assignb T133[0] T132
assignb T134 'E'
add T135 T126 3
# Copy from "T134" to "T135"
assignb T135[0] T134
assignb T136 'L'
add T137 T126 4
# Copy from "T136" to "T137"
assignb T137[0] T136
assignb T138 ' '
add T139 T126 5
# Copy from "T138" to "T139"
assignb T139[0] T138
assignb T140 'N'
add T141 T126 6
# Copy from "T140" to "T141"
assignb T141[0] T140
assignb T142 'U'
add T143 T126 7
# Copy from "T142" to "T143"
assignb T143[0] T142
assignb T144 'M'
add T145 T126 8
# Copy from "T144" to "T145"
assignb T145[0] T144
assignb T146 'E'
add T147 T126 9
# Copy from "T146" to "T147"
assignb T147[0] T146
assignb T148 'R'
add T149 T126 10
# Copy from "T148" to "T149"
assignb T149[0] T148
assignb T150 'O'
add T151 T126 11
# Copy from "T150" to "T151"
assignb T151[0] T150
assignb T152 ' '
add T153 T126 12
# Copy from "T152" to "T153"
assignb T153[0] T152
assignb T154 'D'
add T155 T126 13
# Copy from "T154" to "T155"
assignb T155[0] T154
assignb T156 'E'
add T157 T126 14
# Copy from "T156" to "T157"
assignb T157[0] T156
assignb T158 ' '
add T159 T126 15
# Copy from "T158" to "T159"
assignb T159[0] T158
assignb T160 'E'
add T161 T126 16
# Copy from "T160" to "T161"
assignb T161[0] T160
assignb T162 'D'
add T163 T126 17
# Copy from "T162" to "T163"
assignb T163[0] T162
assignb T164 'G'
add T165 T126 18
# Copy from "T164" to "T165"
assignb T165[0] T164
assignb T166 'E'
add T167 T126 19
# Copy from "T166" to "T167"
assignb T167[0] T166
assignb T168 'S'
add T169 T126 20
# Copy from "T168" to "T169"
assignb T169[0] T168
assignb T170 '\n'
add T171 T126 21
# Copy from "T170" to "T171"
assignb T171[0] T170
assignb T172 ' '
add T173 T126 22
# Copy from "T172" to "T173"
assignb T173[0] T172
assignw T174 T127[0]
print T174
readi T175
# _E__T176 := _E__0__L6 # address of variable E
assignw _E__T176 _E__0__L6
# Copy from "T175" to "_E__T176"
assignw _E__T176[0] T175
assignw T178 0
# _E__T179 := _E__0__L6 # address of variable E
assignw _E__T179 _E__0__L6
assignw T180 _E__T179[0]
assignw T181 1
# FOR BEGIN
assignw BASE[16] T178
@label _for_start__L13
assignw _i__T183 BASE[16]
geq T182 _i__T183 T180
goif _for_end__L15 T182
# FOR BODY BEGIN
assignw T184 STACK
add STACK STACK 60
add T185 BASE 20
assignw T185[0] T184
assignw T185[4] 57
assignb T186 'D'
add T187 T184 0
# Copy from "T186" to "T187"
assignb T187[0] T186
assignb T188 'E'
add T189 T184 1
# Copy from "T188" to "T189"
assignb T189[0] T188
assignb T190 ' '
add T191 T184 2
# Copy from "T190" to "T191"
assignb T191[0] T190
assignb T192 'U'
add T193 T184 3
# Copy from "T192" to "T193"
assignb T193[0] T192
assignb T194 'N'
add T195 T184 4
# Copy from "T194" to "T195"
assignb T195[0] T194
assignb T196 ' '
add T197 T184 5
# Copy from "T196" to "T197"
assignb T197[0] T196
assignb T198 'E'
add T199 T184 6
# Copy from "T198" to "T199"
assignb T199[0] T198
assignb T200 'D'
add T201 T184 7
# Copy from "T200" to "T201"
assignb T201[0] T200
assignb T202 'G'
add T203 T184 8
# Copy from "T202" to "T203"
assignb T203[0] T202
assignb T204 'E'
add T205 T184 9
# Copy from "T204" to "T205"
assignb T205[0] T204
assignb T206 ' '
add T207 T184 10
# Copy from "T206" to "T207"
assignb T207[0] T206
assignb T208 'D'
add T209 T184 11
# Copy from "T208" to "T209"
assignb T209[0] T208
assignb T210 'I'
add T211 T184 12
# Copy from "T210" to "T211"
assignb T211[0] T210
assignb T212 'R'
add T213 T184 13
# Copy from "T212" to "T213"
assignb T213[0] T212
assignb T214 'E'
add T215 T184 14
# Copy from "T214" to "T215"
assignb T215[0] T214
assignb T216 'C'
add T217 T184 15
# Copy from "T216" to "T217"
assignb T217[0] T216
assignb T218 'C'
add T219 T184 16
# Copy from "T218" to "T219"
assignb T219[0] T218
assignb T220 'I'
add T221 T184 17
# Copy from "T220" to "T221"
assignb T221[0] T220
assignb T222 'O'
add T223 T184 18
# Copy from "T222" to "T223"
assignb T223[0] T222
assignb T224 'N'
add T225 T184 19
# Copy from "T224" to "T225"
assignb T225[0] T224
assignb T226 'A'
add T227 T184 20
# Copy from "T226" to "T227"
assignb T227[0] T226
assignb T228 'L'
add T229 T184 21
# Copy from "T228" to "T229"
assignb T229[0] T228
assignb T230 ' '
add T231 T184 22
# Copy from "T230" to "T231"
assignb T231[0] T230
assignb T232 '('
add T233 T184 23
# Copy from "T232" to "T233"
assignb T233[0] T232
assignb T234 'D'
add T235 T184 24
# Copy from "T234" to "T235"
assignb T235[0] T234
assignb T236 'O'
add T237 T184 25
# Copy from "T236" to "T237"
assignb T237[0] T236
assignb T238 'S'
add T239 T184 26
# Copy from "T238" to "T239"
assignb T239[0] T238
assignb T240 ' '
add T241 T184 27
# Copy from "T240" to "T241"
assignb T241[0] T240
assignb T242 'E'
add T243 T184 28
# Copy from "T242" to "T243"
assignb T243[0] T242
assignb T244 'N'
add T245 T184 29
# Copy from "T244" to "T245"
assignb T245[0] T244
assignb T246 'T'
add T247 T184 30
# Copy from "T246" to "T247"
assignb T247[0] T246
assignb T248 'E'
add T249 T184 31
# Copy from "T248" to "T249"
assignb T249[0] T248
assignb T250 'R'
add T251 T184 32
# Copy from "T250" to "T251"
assignb T251[0] T250
assignb T252 'O'
add T253 T184 33
# Copy from "T252" to "T253"
assignb T253[0] T252
assignb T254 'S'
add T255 T184 34
# Copy from "T254" to "T255"
assignb T255[0] T254
assignb T256 ','
add T257 T184 35
# Copy from "T256" to "T257"
assignb T257[0] T256
assignb T258 ' '
add T259 T184 36
# Copy from "T258" to "T259"
assignb T259[0] T258
assignb T260 'E'
add T261 T184 37
# Copy from "T260" to "T261"
assignb T261[0] T260
assignb T262 'M'
add T263 T184 38
# Copy from "T262" to "T263"
assignb T263[0] T262
assignb T264 'P'
add T265 T184 39
# Copy from "T264" to "T265"
assignb T265[0] T264
assignb T266 'E'
add T267 T184 40
# Copy from "T266" to "T267"
assignb T267[0] T266
assignb T268 'Z'
add T269 T184 41
# Copy from "T268" to "T269"
assignb T269[0] T268
assignb T270 'A'
add T271 T184 42
# Copy from "T270" to "T271"
assignb T271[0] T270
assignb T272 'N'
add T273 T184 43
# Copy from "T272" to "T273"
assignb T273[0] T272
assignb T274 'D'
add T275 T184 44
# Copy from "T274" to "T275"
assignb T275[0] T274
assignb T276 'O'
add T277 T184 45
# Copy from "T276" to "T277"
assignb T277[0] T276
assignb T278 ' '
add T279 T184 46
# Copy from "T278" to "T279"
assignb T279[0] T278
assignb T280 'D'
add T281 T184 47
# Copy from "T280" to "T281"
assignb T281[0] T280
assignb T282 'E'
add T283 T184 48
# Copy from "T282" to "T283"
assignb T283[0] T282
assignb T284 'S'
add T285 T184 49
# Copy from "T284" to "T285"
assignb T285[0] T284
assignb T286 'D'
add T287 T184 50
# Copy from "T286" to "T287"
assignb T287[0] T286
assignb T288 'E'
add T289 T184 51
# Copy from "T288" to "T289"
assignb T289[0] T288
assignb T290 ' '
add T291 T184 52
# Copy from "T290" to "T291"
assignb T291[0] T290
assignb T292 '0'
add T293 T184 53
# Copy from "T292" to "T293"
assignb T293[0] T292
assignb T294 ')'
add T295 T184 54
# Copy from "T294" to "T295"
assignb T295[0] T294
assignb T296 '\n'
add T297 T184 55
# Copy from "T296" to "T297"
assignb T297[0] T296
assignb T298 ' '
add T299 T184 56
# Copy from "T298" to "T299"
assignb T299[0] T298
assignw T300 T185[0]
print T300
readi T301
# _FROM__T302 := _FROM__0__L0 # address of variable FROM
assignw _FROM__T302 _FROM__0__L0
add _i__T303 BASE 16
assignw T304 _i__T303[0]
assignw T305 _FROM__T302[0]
assignw T306 _FROM__T302[4]
lt T308 T304 0
geq T309 T304 T306
or T310 T308 T309
goifnot L16 T310
# EXIT POR OUT OF BOUNDS
assignw T311 ___OUT_OF_BOUNDS
print T311
exit 1
@label L16
mult T307 T304 4
add T307 T307 T305
# Copy from "T301" to "T307"
assignw T307[0] T301
readi T312
# _TO__T313 := _TO__0__L0 # address of variable TO
assignw _TO__T313 _TO__0__L0
add _i__T314 BASE 16
assignw T315 _i__T314[0]
assignw T316 _TO__T313[0]
assignw T317 _TO__T313[4]
lt T319 T315 0
geq T320 T315 T317
or T321 T319 T320
goifnot L17 T321
# EXIT POR OUT OF BOUNDS
assignw T322 ___OUT_OF_BOUNDS
print T322
exit 1
@label L17
mult T318 T315 4
add T318 T318 T316
# Copy from "T312" to "T318"
assignw T318[0] T312
# FOR BODY END
@label _for_step__L14
add _i__T183 _i__T183 T181
assignw BASE[16] _i__T183
# FOR END
goto _for_start__L13
@label _for_end__L15
assignw T324 0
# _V__T325 := _V__0__L13 # address of variable V
assignw _V__T325 _V__0__L13
assignw T326 _V__T325[0]
assignw T327 1
# FOR BEGIN
assignw BASE[28] T324
@label _for_start__L18
assignw _u__T329 BASE[28]
geq T328 _u__T329 T326
goif _for_end__L20 T328
# FOR BODY BEGIN
# _VIS__T331 := _VIS__0__L0 # address of variable VIS
assignw _VIS__T331 _VIS__0__L0
add _u__T332 BASE 28
assignw T333 _u__T332[0]
assignw T334 _VIS__T331[0]
assignw T335 _VIS__T331[4]
lt T337 T333 0
geq T338 T333 T335
or T339 T337 T338
goifnot L23 T339
# EXIT POR OUT OF BOUNDS
assignw T340 ___OUT_OF_BOUNDS
print T340
exit 1
@label L23
mult T336 T333 1
add T336 T336 T334
assignb T341 T336[0]
assignb T342 False
eq T343 T341 T342
goifnot _if_else__L21 T343
# INICIO IF
# Code to calculate parameters
add _u__T344 BASE 28
assignw T345 _u__T344[0]
# Push parameters
param T347 0
# Copy from "T345" to "T347"
assignw T347[0] T345
call _freturn__T346 dfs__0
goto _if_out__L22
@label _if_else__L21
# INICIO ELSE
@label _if_out__L22
# FOR BODY END
@label _for_step__L19
add _u__T329 _u__T329 T327
assignw BASE[28] _u__T329
# FOR END
goto _for_start__L18
@label _for_end__L20
@label _main_end__L11
@endfunction 32
@label endProgram
