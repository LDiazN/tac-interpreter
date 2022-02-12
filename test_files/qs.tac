@string ___OUT_OF_BOUNDS "Avatar doesn't allow using non existing disciples\n"
@string ___DIVSION_BY_0 "Avatar doesn't allow doing besides 0\n"
@string ___UNACTIVE_UNION_FIELD "Avatar doesn't allow using an energy's non-active technique\n"
call ___main main__0
exit 0
@function swapi__0 12
goto L1
@label L1
add _a__T0 BASE 0
assignw T1 _a__T0[0]
add _tmp__T2 BASE 8
# Copy from "T1" to "_tmp__T2"
assignw _tmp__T2[0] T1
add _b__T3 BASE 4
assignw T4 _b__T3[0]
add _a__T5 BASE 0
# Copy from "T4" to "_a__T5"
# Copy from "T4" to "_a__T5"
assignw _a__T5[0] T4
add _tmp__T6 BASE 8
assignw T7 _tmp__T6[0]
add _b__T8 BASE 4
# Copy from "T7" to "_b__T8"
# Copy from "T7" to "_b__T8"
assignw _b__T8[0] T7
@label _swapi_end__L0
@endfunction 12
@function quickSort__0 20
goto L3
@label L3
add _low__T10 BASE 0
assignw T11 _low__T10[0]
add _high__T12 BASE 4
assignw T13 _high__T12[0]
lt T14 T11 T13
goifnot _if_else__L4 T14
# INICIO IF
# Code to calculate parameters
add _low__T15 BASE 0
assignw T16 _low__T15[0]
add _high__T17 BASE 4
assignw T18 _high__T17[0]
add _ARR__T19 BASE 8
# Push parameters
param T21 0
# Copy from "T16" to "T21"
assignw T21[0] T16
param T22 4
# Copy from "T18" to "T22"
assignw T22[0] T18
param T23 8
# Copy from "_ARR__T19" to "T23"
memcpy T23 _ARR__T19 8
call _freturn__T20 partition__0
add _pi__T24 BASE 16
# Copy from "_freturn__T20" to "_pi__T24"
assignw _pi__T24[0] _freturn__T20
# Code to calculate parameters
add _low__T25 BASE 0
assignw T26 _low__T25[0]
add _pi__T27 BASE 16
assignw T28 _pi__T27[0]
assignw T29 1
sub T30 T28 T29
add _ARR__T31 BASE 8
# Push parameters
param T33 0
# Copy from "T26" to "T33"
assignw T33[0] T26
param T34 4
# Copy from "T30" to "T34"
assignw T34[0] T30
param T35 8
# Copy from "_ARR__T31" to "T35"
memcpy T35 _ARR__T31 8
call _freturn__T32 quickSort__0
# Code to calculate parameters
add _pi__T36 BASE 16
assignw T37 _pi__T36[0]
assignw T38 1
add T39 T37 T38
add _high__T40 BASE 4
assignw T41 _high__T40[0]
add _ARR__T42 BASE 8
# Push parameters
param T44 0
# Copy from "T39" to "T44"
assignw T44[0] T39
param T45 4
# Copy from "T41" to "T45"
assignw T45[0] T41
param T46 8
# Copy from "_ARR__T42" to "T46"
memcpy T46 _ARR__T42 8
call _freturn__T43 quickSort__0
goto _if_out__L5
@label _if_else__L4
# INICIO ELSE
@label _if_out__L5
@label _quickSort_end__L2
@endfunction 20
@function partition__0 28
goto L7
@label L7
add _ARR__T47 BASE 8
add _high__T48 BASE 4
assignw T49 _high__T48[0]
assignw T50 _ARR__T47[0]
assignw T51 _ARR__T47[4]
lt T53 T49 0
geq T54 T49 T51
or T55 T53 T54
goifnot L8 T55
# EXIT POR OUT OF BOUNDS
assignw T56 ___OUT_OF_BOUNDS
print T56
exit 1
@label L8
mult T52 T49 4
add T52 T52 T50
assignw T57 T52[0]
add _pivot__T58 BASE 16
# Copy from "T57" to "_pivot__T58"
assignw _pivot__T58[0] T57
add _low__T59 BASE 0
assignw T60 _low__T59[0]
assignw T61 1
sub T62 T60 T61
add _i__T63 BASE 20
# Copy from "T62" to "_i__T63"
assignw _i__T63[0] T62
add _low__T65 BASE 0
assignw T66 _low__T65[0]
add _high__T67 BASE 4
assignw T68 _high__T67[0]
assignw T69 1
# FOR BEGIN
assignw BASE[24] T66
@label _for_start__L9
assignw _j__T71 BASE[24]
geq T70 _j__T71 T68
goif _for_end__L11 T70
# FOR BODY BEGIN
add _ARR__T73 BASE 8
add _j__T74 BASE 24
assignw T75 _j__T74[0]
assignw T76 _ARR__T73[0]
assignw T77 _ARR__T73[4]
lt T79 T75 0
geq T80 T75 T77
or T81 T79 T80
goifnot L14 T81
# EXIT POR OUT OF BOUNDS
assignw T82 ___OUT_OF_BOUNDS
print T82
exit 1
@label L14
mult T78 T75 4
add T78 T78 T76
assignw T83 T78[0]
add _pivot__T84 BASE 16
assignw T85 _pivot__T84[0]
lt T86 T83 T85
goifnot _if_else__L12 T86
# INICIO IF
add _i__T87 BASE 20
assignw T88 _i__T87[0]
assignw T89 1
add T90 T88 T89
add _i__T91 BASE 20
# Copy from "T90" to "_i__T91"
assignw _i__T91[0] T90
# Code to calculate parameters
add _ARR__T92 BASE 8
add _i__T93 BASE 20
assignw T94 _i__T93[0]
assignw T95 _ARR__T92[0]
assignw T96 _ARR__T92[4]
lt T98 T94 0
geq T99 T94 T96
or T100 T98 T99
goifnot L15 T100
# EXIT POR OUT OF BOUNDS
assignw T101 ___OUT_OF_BOUNDS
print T101
exit 1
@label L15
mult T97 T94 4
add T97 T97 T95
assignw T102 T97[0]
add _ARR__T103 BASE 8
add _j__T104 BASE 24
assignw T105 _j__T104[0]
assignw T106 _ARR__T103[0]
assignw T107 _ARR__T103[4]
lt T109 T105 0
geq T110 T105 T107
or T111 T109 T110
goifnot L16 T111
# EXIT POR OUT OF BOUNDS
assignw T112 ___OUT_OF_BOUNDS
print T112
exit 1
@label L16
mult T108 T105 4
add T108 T108 T106
assignw T113 T108[0]
# Push parameters
param T115 0
# Copy from "T102" to "T115"
# Copy from "T102" to "T115"
assignw T115[0] T102
param T116 4
# Copy from "T113" to "T116"
# Copy from "T113" to "T116"
assignw T116[0] T113
call _freturn__T114 swapi__0
# Assign reference of array access
add _ARR__T117 BASE 8
add _i__T118 BASE 20
assignw T119 _i__T118[0]
assignw _ARR__T117 _ARR__T117[0]
mult T119 T119 4
add _ARR__T117 _ARR__T117 T119
assignw T115 T115[0]
# Copy from "T115" to "_ARR__T117"
assignw _ARR__T117[0] T115
# Assign reference of array access
add _ARR__T120 BASE 8
add _j__T121 BASE 24
assignw T122 _j__T121[0]
assignw _ARR__T120 _ARR__T120[0]
mult T122 T122 4
add _ARR__T120 _ARR__T120 T122
assignw T116 T116[0]
# Copy from "T116" to "_ARR__T120"
assignw _ARR__T120[0] T116
goto _if_out__L13
@label _if_else__L12
# INICIO ELSE
@label _if_out__L13
# FOR BODY END
@label _for_step__L10
add _j__T71 _j__T71 T69
assignw BASE[24] _j__T71
# FOR END
goto _for_start__L9
@label _for_end__L11
# Code to calculate parameters
add _ARR__T123 BASE 8
add _i__T124 BASE 20
assignw T125 _i__T124[0]
assignw T126 1
add T127 T125 T126
assignw T128 _ARR__T123[0]
assignw T129 _ARR__T123[4]
lt T131 T127 0
geq T132 T127 T129
or T133 T131 T132
goifnot L17 T133
# EXIT POR OUT OF BOUNDS
assignw T134 ___OUT_OF_BOUNDS
print T134
exit 1
@label L17
mult T130 T127 4
add T130 T130 T128
assignw T135 T130[0]
add _ARR__T136 BASE 8
add _high__T137 BASE 4
assignw T138 _high__T137[0]
assignw T139 _ARR__T136[0]
assignw T140 _ARR__T136[4]
lt T142 T138 0
geq T143 T138 T140
or T144 T142 T143
goifnot L18 T144
# EXIT POR OUT OF BOUNDS
assignw T145 ___OUT_OF_BOUNDS
print T145
exit 1
@label L18
mult T141 T138 4
add T141 T141 T139
assignw T146 T141[0]
# Push parameters
param T148 0
# Copy from "T135" to "T148"
# Copy from "T135" to "T148"
assignw T148[0] T135
param T149 4
# Copy from "T146" to "T149"
# Copy from "T146" to "T149"
assignw T149[0] T146
call _freturn__T147 swapi__0
# Assign reference of array access
add _ARR__T150 BASE 8
add _i__T151 BASE 20
assignw T152 _i__T151[0]
assignw T153 1
add T154 T152 T153
assignw _ARR__T150 _ARR__T150[0]
mult T154 T154 4
add _ARR__T150 _ARR__T150 T154
assignw T148 T148[0]
# Copy from "T148" to "_ARR__T150"
assignw _ARR__T150[0] T148
# Assign reference of array access
add _ARR__T155 BASE 8
add _high__T156 BASE 4
assignw T157 _high__T156[0]
assignw _ARR__T155 _ARR__T155[0]
mult T157 T157 4
add _ARR__T155 _ARR__T155 T157
assignw T149 T149[0]
# Copy from "T149" to "_ARR__T155"
assignw _ARR__T155[0] T149
add _i__T158 BASE 20
assignw T159 _i__T158[0]
assignw T160 1
add T161 T159 T160
return T161
@label _partition_end__L6
@endfunction 28
@function main__0 40
goto L20
@label L20
add _ARR__T162 BASE 0
assignw _ARR__T162[0] STACK
assignw T163 50
assignw _ARR__T162[4] T163
mult T163 T163 4
add T163 T163 3
div T163 T163 4
mult T163 T163 4
add STACK STACK T163
@label _while_start__L21
assignb T165 True
goifnot _while_out__L22 T165
assignw T166 STACK
add STACK STACK 36
add T167 BASE 8
assignw T167[0] T166
assignw T167[4] 34
assignb T168 'D'
add T169 T166 0
# Copy from "T168" to "T169"
assignb T169[0] T168
assignb T170 'E'
add T171 T166 1
# Copy from "T170" to "T171"
assignb T171[0] T170
assignb T172 ' '
add T173 T166 2
# Copy from "T172" to "T173"
assignb T173[0] T172
assignb T174 '0'
add T175 T166 3
# Copy from "T174" to "T175"
assignb T175[0] T174
assignb T176 ' '
add T177 T166 4
# Copy from "T176" to "T177"
assignb T177[0] T176
assignb T178 'P'
add T179 T166 5
# Copy from "T178" to "T179"
assignb T179[0] T178
assignb T180 'A'
add T181 T166 6
# Copy from "T180" to "T181"
assignb T181[0] T180
assignb T182 'R'
add T183 T166 7
# Copy from "T182" to "T183"
assignb T183[0] T182
assignb T184 'A'
add T185 T166 8
# Copy from "T184" to "T185"
assignb T185[0] T184
assignb T186 ' '
add T187 T166 9
# Copy from "T186" to "T187"
assignb T187[0] T186
assignb T188 'T'
add T189 T166 10
# Copy from "T188" to "T189"
assignb T189[0] T188
assignb T190 'E'
add T191 T166 11
# Copy from "T190" to "T191"
assignb T191[0] T190
assignb T192 'R'
add T193 T166 12
# Copy from "T192" to "T193"
assignb T193[0] T192
assignb T194 'M'
add T195 T166 13
# Copy from "T194" to "T195"
assignb T195[0] T194
assignb T196 'I'
add T197 T166 14
# Copy from "T196" to "T197"
assignb T197[0] T196
assignb T198 'N'
add T199 T166 15
# Copy from "T198" to "T199"
assignb T199[0] T198
assignb T200 'A'
add T201 T166 16
# Copy from "T200" to "T201"
assignb T201[0] T200
assignb T202 'R'
add T203 T166 17
# Copy from "T202" to "T203"
assignb T203[0] T202
assignb T204 ' '
add T205 T166 18
# Copy from "T204" to "T205"
assignb T205[0] T204
assignb T206 'O'
add T207 T166 19
# Copy from "T206" to "T207"
assignb T207[0] T206
assignb T208 ' '
add T209 T166 20
# Copy from "T208" to "T209"
assignb T209[0] T208
assignb T210 '1'
add T211 T166 21
# Copy from "T210" to "T211"
assignb T211[0] T210
assignb T212 ' '
add T213 T166 22
# Copy from "T212" to "T213"
assignb T213[0] T212
assignb T214 'C'
add T215 T166 23
# Copy from "T214" to "T215"
assignb T215[0] T214
assignb T216 'O'
add T217 T166 24
# Copy from "T216" to "T217"
assignb T217[0] T216
assignb T218 'N'
add T219 T166 25
# Copy from "T218" to "T219"
assignb T219[0] T218
assignb T220 'T'
add T221 T166 26
# Copy from "T220" to "T221"
assignb T221[0] T220
assignb T222 'I'
add T223 T166 27
# Copy from "T222" to "T223"
assignb T223[0] T222
assignb T224 'N'
add T225 T166 28
# Copy from "T224" to "T225"
assignb T225[0] T224
assignb T226 'U'
add T227 T166 29
# Copy from "T226" to "T227"
assignb T227[0] T226
assignb T228 'A'
add T229 T166 30
# Copy from "T228" to "T229"
assignb T229[0] T228
assignb T230 'R'
add T231 T166 31
# Copy from "T230" to "T231"
assignb T231[0] T230
assignb T232 '\n'
add T233 T166 32
# Copy from "T232" to "T233"
assignb T233[0] T232
assignb T234 ' '
add T235 T166 33
# Copy from "T234" to "T235"
assignb T235[0] T234
assignw T236 T167[0]
print T236
readi T237
add _finish__T238 BASE 16
# Copy from "T237" to "_finish__T238"
assignw _finish__T238[0] T237
add _finish__T240 BASE 16
assignw T241 _finish__T240[0]
assignw T242 0
eq T243 T241 T242
goifnot _if_else__L23 T243
# INICIO IF
goto _while_out__L22
goto _if_out__L24
@label _if_else__L23
# INICIO ELSE
assignw T244 STACK
add STACK STACK 36
add T245 BASE 20
assignw T245[0] T244
assignw T245[4] 35
assignb T246 'I'
add T247 T244 0
# Copy from "T246" to "T247"
assignb T247[0] T246
assignb T248 'N'
add T249 T244 1
# Copy from "T248" to "T249"
assignb T249[0] T248
assignb T250 'T'
add T251 T244 2
# Copy from "T250" to "T251"
assignb T251[0] T250
assignb T252 'R'
add T253 T244 3
# Copy from "T252" to "T253"
assignb T253[0] T252
assignb T254 'O'
add T255 T244 4
# Copy from "T254" to "T255"
assignb T255[0] T254
assignb T256 'D'
add T257 T244 5
# Copy from "T256" to "T257"
assignb T257[0] T256
assignb T258 'U'
add T259 T244 6
# Copy from "T258" to "T259"
assignb T259[0] T258
assignb T260 'Z'
add T261 T244 7
# Copy from "T260" to "T261"
assignb T261[0] T260
assignb T262 'C'
add T263 T244 8
# Copy from "T262" to "T263"
assignb T263[0] T262
assignb T264 'A'
add T265 T244 9
# Copy from "T264" to "T265"
assignb T265[0] T264
assignb T266 ' '
add T267 T244 10
# Copy from "T266" to "T267"
assignb T267[0] T266
assignb T268 'L'
add T269 T244 11
# Copy from "T268" to "T269"
assignb T269[0] T268
assignb T270 'A'
add T271 T244 12
# Copy from "T270" to "T271"
assignb T271[0] T270
assignb T272 ' '
add T273 T244 13
# Copy from "T272" to "T273"
assignb T273[0] T272
assignb T274 'C'
add T275 T244 14
# Copy from "T274" to "T275"
assignb T275[0] T274
assignb T276 'A'
add T277 T244 15
# Copy from "T276" to "T277"
assignb T277[0] T276
assignb T278 'N'
add T279 T244 16
# Copy from "T278" to "T279"
assignb T279[0] T278
assignb T280 'T'
add T281 T244 17
# Copy from "T280" to "T281"
assignb T281[0] T280
assignb T282 'I'
add T283 T244 18
# Copy from "T282" to "T283"
assignb T283[0] T282
assignb T284 'D'
add T285 T244 19
# Copy from "T284" to "T285"
assignb T285[0] T284
assignb T286 'A'
add T287 T244 20
# Copy from "T286" to "T287"
assignb T287[0] T286
assignb T288 'D'
add T289 T244 21
# Copy from "T288" to "T289"
assignb T289[0] T288
assignb T290 ' '
add T291 T244 22
# Copy from "T290" to "T291"
assignb T291[0] T290
assignb T292 'D'
add T293 T244 23
# Copy from "T292" to "T293"
assignb T293[0] T292
assignb T294 'E'
add T295 T244 24
# Copy from "T294" to "T295"
assignb T295[0] T294
assignb T296 ' '
add T297 T244 25
# Copy from "T296" to "T297"
assignb T297[0] T296
assignb T298 'E'
add T299 T244 26
# Copy from "T298" to "T299"
assignb T299[0] T298
assignb T300 'N'
add T301 T244 27
# Copy from "T300" to "T301"
assignb T301[0] T300
assignb T302 'T'
add T303 T244 28
# Copy from "T302" to "T303"
assignb T303[0] T302
assignb T304 'E'
add T305 T244 29
# Copy from "T304" to "T305"
assignb T305[0] T304
assignb T306 'R'
add T307 T244 30
# Copy from "T306" to "T307"
assignb T307[0] T306
assignb T308 'O'
add T309 T244 31
# Copy from "T308" to "T309"
assignb T309[0] T308
assignb T310 'S'
add T311 T244 32
# Copy from "T310" to "T311"
assignb T311[0] T310
assignb T312 '\n'
add T313 T244 33
# Copy from "T312" to "T313"
assignb T313[0] T312
assignb T314 ' '
add T315 T244 34
# Copy from "T314" to "T315"
assignb T315[0] T314
assignw T316 T245[0]
print T316
readi T317
add _n__T318 BASE 28
# Copy from "T317" to "_n__T318"
assignw _n__T318[0] T317
assignw T320 0
add _n__T321 BASE 28
assignw T322 _n__T321[0]
assignw T323 1
# FOR BEGIN
assignw BASE[32] T320
@label _for_start__L25
assignw _i__T325 BASE[32]
geq T324 _i__T325 T322
goif _for_end__L27 T324
# FOR BODY BEGIN
readi T326
add _ARR__T327 BASE 0
add _i__T328 BASE 32
assignw T329 _i__T328[0]
assignw T330 _ARR__T327[0]
assignw T331 _ARR__T327[4]
lt T333 T329 0
geq T334 T329 T331
or T335 T333 T334
goifnot L28 T335
# EXIT POR OUT OF BOUNDS
assignw T336 ___OUT_OF_BOUNDS
print T336
exit 1
@label L28
mult T332 T329 4
add T332 T332 T330
# Copy from "T326" to "T332"
assignw T332[0] T326
# FOR BODY END
@label _for_step__L26
add _i__T325 _i__T325 T323
assignw BASE[32] _i__T325
# FOR END
goto _for_start__L25
@label _for_end__L27
# Code to calculate parameters
assignw T337 0
add _n__T338 BASE 28
assignw T339 _n__T338[0]
assignw T340 1
sub T341 T339 T340
add _ARR__T342 BASE 0
# Push parameters
param T344 0
# Copy from "T337" to "T344"
assignw T344[0] T337
param T345 4
# Copy from "T341" to "T345"
assignw T345[0] T341
param T346 8
# Copy from "_ARR__T342" to "T346"
memcpy T346 _ARR__T342 8
call _freturn__T343 quickSort__0
assignw T348 0
add _n__T349 BASE 28
assignw T350 _n__T349[0]
assignw T351 1
# FOR BEGIN
assignw BASE[36] T348
@label _for_start__L29
assignw _i__T353 BASE[36]
geq T352 _i__T353 T350
goif _for_end__L31 T352
# FOR BODY BEGIN
add _ARR__T354 BASE 0
add _i__T355 BASE 36
assignw T356 _i__T355[0]
assignw T357 _ARR__T354[0]
assignw T358 _ARR__T354[4]
lt T360 T356 0
geq T361 T356 T358
or T362 T360 T361
goifnot L32 T362
# EXIT POR OUT OF BOUNDS
assignw T363 ___OUT_OF_BOUNDS
print T363
exit 1
@label L32
mult T359 T356 4
add T359 T359 T357
assignw T364 T359[0]
printi T364
assignb T365 '\n'
printc T365
# FOR BODY END
@label _for_step__L30
add _i__T353 _i__T353 T351
assignw BASE[36] _i__T353
# FOR END
goto _for_start__L29
@label _for_end__L31
@label _if_out__L24
goto _while_start__L21
@label _while_out__L22
@label _main_end__L19
@endfunction 40
@label endProgram
