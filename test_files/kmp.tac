@string ___OUT_OF_BOUNDS "Avatar doesn't allow using non existing disciples\n"
@string ___DIVSION_BY_0 "Avatar doesn't allow doing besides 0\n"
@string ___UNACTIVE_UNION_FIELD "Avatar doesn't allow using an energy's non-active technique\n"
call ___main main__0
exit 0
@function kmp__0 100
goto L1
@label L1
assignw T0 STACK
add STACK STACK 28
add T1 BASE 0
assignw T1[0] T0
assignw T1[4] 25
assignb T2 'D'
add T3 T0 0
# Copy from "T2" to "T3"
assignb T3[0] T2
assignb T4 'E'
add T5 T0 1
# Copy from "T4" to "T5"
assignb T5[0] T4
assignb T6 ' '
add T7 T0 2
# Copy from "T6" to "T7"
assignb T7[0] T6
assignb T8 'E'
add T9 T0 3
# Copy from "T8" to "T9"
assignb T9[0] T8
assignb T10 'L'
add T11 T0 4
# Copy from "T10" to "T11"
assignb T11[0] T10
assignb T12 ' '
add T13 T0 5
# Copy from "T12" to "T13"
assignb T13[0] T12
assignb T14 'T'
add T15 T0 6
# Copy from "T14" to "T15"
assignb T15[0] T14
assignb T16 'A'
add T17 T0 7
# Copy from "T16" to "T17"
assignb T17[0] T16
assignb T18 'M'
add T19 T0 8
# Copy from "T18" to "T19"
assignb T19[0] T18
assignb T20 'A'
add T21 T0 9
# Copy from "T20" to "T21"
assignb T21[0] T20
assignb T22 'N'
add T23 T0 10
# Copy from "T22" to "T23"
assignb T23[0] T22
assignb T24 'O'
add T25 T0 11
# Copy from "T24" to "T25"
assignb T25[0] T24
assignb T26 ' '
add T27 T0 12
# Copy from "T26" to "T27"
assignb T27[0] T26
assignb T28 'D'
add T29 T0 13
# Copy from "T28" to "T29"
assignb T29[0] T28
assignb T30 'E'
add T31 T0 14
# Copy from "T30" to "T31"
assignb T31[0] T30
assignb T32 'L'
add T33 T0 15
# Copy from "T32" to "T33"
assignb T33[0] T32
assignb T34 ' '
add T35 T0 16
# Copy from "T34" to "T35"
assignb T35[0] T34
assignb T36 'P'
add T37 T0 17
# Copy from "T36" to "T37"
assignb T37[0] T36
assignb T38 'A'
add T39 T0 18
# Copy from "T38" to "T39"
assignb T39[0] T38
assignb T40 'T'
add T41 T0 19
# Copy from "T40" to "T41"
assignb T41[0] T40
assignb T42 'R'
add T43 T0 20
# Copy from "T42" to "T43"
assignb T43[0] T42
assignb T44 'O'
add T45 T0 21
# Copy from "T44" to "T45"
assignb T45[0] T44
assignb T46 'N'
add T47 T0 22
# Copy from "T46" to "T47"
assignb T47[0] T46
assignb T48 '\n'
add T49 T0 23
# Copy from "T48" to "T49"
assignb T49[0] T48
assignb T50 ' '
add T51 T0 24
# Copy from "T50" to "T51"
assignb T51[0] T50
assignw T52 T1[0]
print T52
readi T53
add _n__T54 BASE 8
# Copy from "T53" to "_n__T54"
assignw _n__T54[0] T53
assignw T55 STACK
add STACK STACK 16
add T56 BASE 12
assignw T56[0] T55
assignw T56[4] 14
assignb T57 'D'
add T58 T55 0
# Copy from "T57" to "T58"
assignb T58[0] T57
assignb T59 'E'
add T60 T55 1
# Copy from "T59" to "T60"
assignb T60[0] T59
assignb T61 ' '
add T62 T55 2
# Copy from "T61" to "T62"
assignb T62[0] T61
assignb T63 'E'
add T64 T55 3
# Copy from "T63" to "T64"
assignb T64[0] T63
assignb T65 'L'
add T66 T55 4
# Copy from "T65" to "T66"
assignb T66[0] T65
assignb T67 ' '
add T68 T55 5
# Copy from "T67" to "T68"
assignb T68[0] T67
assignb T69 'P'
add T70 T55 6
# Copy from "T69" to "T70"
assignb T70[0] T69
assignb T71 'A'
add T72 T55 7
# Copy from "T71" to "T72"
assignb T72[0] T71
assignb T73 'T'
add T74 T55 8
# Copy from "T73" to "T74"
assignb T74[0] T73
assignb T75 'R'
add T76 T55 9
# Copy from "T75" to "T76"
assignb T76[0] T75
assignb T77 'O'
add T78 T55 10
# Copy from "T77" to "T78"
assignb T78[0] T77
assignb T79 'N'
add T80 T55 11
# Copy from "T79" to "T80"
assignb T80[0] T79
assignb T81 '\n'
add T82 T55 12
# Copy from "T81" to "T82"
assignb T82[0] T81
assignb T83 ' '
add T84 T55 13
# Copy from "T83" to "T84"
assignb T84[0] T83
assignw T85 T56[0]
print T85
add _pattern__T86 BASE 20
assignw _pattern__T86[0] STACK
add _n__T87 BASE 8
assignw T88 _n__T87[0]
assignw T89 1
add T90 T88 T89
assignw _pattern__T86[4] T90
mult T90 T90 1
add T90 T90 3
div T90 T90 4
mult T90 T90 4
add STACK STACK T90
add _pattern__T91 BASE 20
assignw T92 _pattern__T91[0]
read T92
add _pattern__T93 BASE 20
add _n__T94 BASE 8
assignw T95 _n__T94[0]
assignb T96 '$'
assignw T97 _pattern__T93[0]
assignw T98 _pattern__T93[4]
lt T100 T95 0
geq T101 T95 T98
or T102 T100 T101
goifnot L2 T102
# EXIT POR OUT OF BOUNDS
assignw T103 ___OUT_OF_BOUNDS
print T103
exit 1
@label L2
mult T99 T95 1
add T99 T99 T97
# Copy from "T96" to "T99"
assignb T99[0] T96
assignw T104 STACK
add STACK STACK 24
add T105 BASE 28
assignw T105[0] T104
assignw T105[4] 24
assignb T106 'D'
add T107 T104 0
# Copy from "T106" to "T107"
assignb T107[0] T106
assignb T108 'E'
add T109 T104 1
# Copy from "T108" to "T109"
assignb T109[0] T108
assignb T110 ' '
add T111 T104 2
# Copy from "T110" to "T111"
assignb T111[0] T110
assignb T112 'E'
add T113 T104 3
# Copy from "T112" to "T113"
assignb T113[0] T112
assignb T114 'L'
add T115 T104 4
# Copy from "T114" to "T115"
assignb T115[0] T114
assignb T116 ' '
add T117 T104 5
# Copy from "T116" to "T117"
assignb T117[0] T116
assignb T118 'T'
add T119 T104 6
# Copy from "T118" to "T119"
assignb T119[0] T118
assignb T120 'A'
add T121 T104 7
# Copy from "T120" to "T121"
assignb T121[0] T120
assignb T122 'M'
add T123 T104 8
# Copy from "T122" to "T123"
assignb T123[0] T122
assignb T124 'A'
add T125 T104 9
# Copy from "T124" to "T125"
assignb T125[0] T124
assignb T126 'N'
add T127 T104 10
# Copy from "T126" to "T127"
assignb T127[0] T126
assignb T128 'O'
add T129 T104 11
# Copy from "T128" to "T129"
assignb T129[0] T128
assignb T130 ' '
add T131 T104 12
# Copy from "T130" to "T131"
assignb T131[0] T130
assignb T132 'D'
add T133 T104 13
# Copy from "T132" to "T133"
assignb T133[0] T132
assignb T134 'E'
add T135 T104 14
# Copy from "T134" to "T135"
assignb T135[0] T134
assignb T136 'L'
add T137 T104 15
# Copy from "T136" to "T137"
assignb T137[0] T136
assignb T138 ' '
add T139 T104 16
# Copy from "T138" to "T139"
assignb T139[0] T138
assignb T140 'T'
add T141 T104 17
# Copy from "T140" to "T141"
assignb T141[0] T140
assignb T142 'E'
add T143 T104 18
# Copy from "T142" to "T143"
assignb T143[0] T142
assignb T144 'X'
add T145 T104 19
# Copy from "T144" to "T145"
assignb T145[0] T144
assignb T146 'T'
add T147 T104 20
# Copy from "T146" to "T147"
assignb T147[0] T146
assignb T148 'O'
add T149 T104 21
# Copy from "T148" to "T149"
assignb T149[0] T148
assignb T150 '\n'
add T151 T104 22
# Copy from "T150" to "T151"
assignb T151[0] T150
assignb T152 ' '
add T153 T104 23
# Copy from "T152" to "T153"
assignb T153[0] T152
assignw T154 T105[0]
print T154
readi T155
add _m__T156 BASE 36
# Copy from "T155" to "_m__T156"
assignw _m__T156[0] T155
assignw T157 STACK
add STACK STACK 16
add T158 BASE 40
assignw T158[0] T157
assignw T158[4] 13
assignb T159 'D'
add T160 T157 0
# Copy from "T159" to "T160"
assignb T160[0] T159
assignb T161 'E'
add T162 T157 1
# Copy from "T161" to "T162"
assignb T162[0] T161
assignb T163 ' '
add T164 T157 2
# Copy from "T163" to "T164"
assignb T164[0] T163
assignb T165 'E'
add T166 T157 3
# Copy from "T165" to "T166"
assignb T166[0] T165
assignb T167 'L'
add T168 T157 4
# Copy from "T167" to "T168"
assignb T168[0] T167
assignb T169 ' '
add T170 T157 5
# Copy from "T169" to "T170"
assignb T170[0] T169
assignb T171 'T'
add T172 T157 6
# Copy from "T171" to "T172"
assignb T172[0] T171
assignb T173 'E'
add T174 T157 7
# Copy from "T173" to "T174"
assignb T174[0] T173
assignb T175 'X'
add T176 T157 8
# Copy from "T175" to "T176"
assignb T176[0] T175
assignb T177 'T'
add T178 T157 9
# Copy from "T177" to "T178"
assignb T178[0] T177
assignb T179 'O'
add T180 T157 10
# Copy from "T179" to "T180"
assignb T180[0] T179
assignb T181 '\n'
add T182 T157 11
# Copy from "T181" to "T182"
assignb T182[0] T181
assignb T183 ' '
add T184 T157 12
# Copy from "T183" to "T184"
assignb T184[0] T183
assignw T185 T158[0]
print T185
add _text__T186 BASE 48
assignw _text__T186[0] STACK
add _m__T187 BASE 36
assignw T188 _m__T187[0]
assignw _text__T186[4] T188
mult T188 T188 1
add T188 T188 3
div T188 T188 4
mult T188 T188 4
add STACK STACK T188
add _text__T189 BASE 48
assignw T190 _text__T189[0]
read T190
add _pi__T191 BASE 56
assignw _pi__T191[0] STACK
add _n__T192 BASE 8
assignw T193 _n__T192[0]
assignw T194 1
add T195 T193 T194
assignw _pi__T191[4] T195
mult T195 T195 4
add T195 T195 3
div T195 T195 4
mult T195 T195 4
add STACK STACK T195
add _pi__T196 BASE 56
assignw T197 0
assignw T198 0
assignw T199 _pi__T196[0]
assignw T200 _pi__T196[4]
lt T202 T197 0
geq T203 T197 T200
or T204 T202 T203
goifnot L3 T204
# EXIT POR OUT OF BOUNDS
assignw T205 ___OUT_OF_BOUNDS
print T205
exit 1
@label L3
mult T201 T197 4
add T201 T201 T199
# Copy from "T198" to "T201"
assignw T201[0] T198
add _pi__T206 BASE 56
add _n__T207 BASE 8
assignw T208 _n__T207[0]
assignw T209 0
assignw T210 _pi__T206[0]
assignw T211 _pi__T206[4]
lt T213 T208 0
geq T214 T208 T211
or T215 T213 T214
goifnot L4 T215
# EXIT POR OUT OF BOUNDS
assignw T216 ___OUT_OF_BOUNDS
print T216
exit 1
@label L4
mult T212 T208 4
add T212 T212 T210
# Copy from "T209" to "T212"
assignw T212[0] T209
add _n__T217 BASE 8
assignw T218 _n__T217[0]
add _no_existo__T219 BASE 64
# Copy from "T218" to "_no_existo__T219"
assignw _no_existo__T219[0] T218
assignw _for_result__T220 0
assignw T221 1
add _no_existo__T222 BASE 64
assignw T223 _no_existo__T222[0]
assignw T224 1
# FOR BEGIN
assignw BASE[68] T221
@label _for_start__L5
assignw _i__T226 BASE[68]
geq T225 _i__T226 T223
goif _for_end__L7 T225
# FOR BODY BEGIN
add _pi__T227 BASE 56
add _i__T228 BASE 68
assignw T229 _i__T228[0]
assignw T230 1
sub T231 T229 T230
assignw T232 _pi__T227[0]
assignw T233 _pi__T227[4]
lt T235 T231 0
geq T236 T231 T233
or T237 T235 T236
goifnot L8 T237
# EXIT POR OUT OF BOUNDS
assignw T238 ___OUT_OF_BOUNDS
print T238
exit 1
@label L8
mult T234 T231 4
add T234 T234 T232
assignw T239 T234[0]
add _j__T240 BASE 72
# Copy from "T239" to "_j__T240"
assignw _j__T240[0] T239
assignw T241 0
@label _while_start__L9
add _j__T242 BASE 72
assignw T243 _j__T242[0]
assignw T244 0
gt T245 T243 T244
add _pattern__T246 BASE 20
add _i__T247 BASE 68
assignw T248 _i__T247[0]
assignw T249 _pattern__T246[0]
assignw T250 _pattern__T246[4]
lt T252 T248 0
geq T253 T248 T250
or T254 T252 T253
goifnot L11 T254
# EXIT POR OUT OF BOUNDS
assignw T255 ___OUT_OF_BOUNDS
print T255
exit 1
@label L11
mult T251 T248 1
add T251 T251 T249
assignb T256 T251[0]
add _pattern__T257 BASE 20
add _j__T258 BASE 72
assignw T259 _j__T258[0]
assignw T260 _pattern__T257[0]
assignw T261 _pattern__T257[4]
lt T263 T259 0
geq T264 T259 T261
or T265 T263 T264
goifnot L12 T265
# EXIT POR OUT OF BOUNDS
assignw T266 ___OUT_OF_BOUNDS
print T266
exit 1
@label L12
mult T262 T259 1
add T262 T262 T260
assignb T267 T262[0]
neq T268 T256 T267
and T269 T245 T268
goifnot _while_out__L10 T269
add _pi__T270 BASE 56
add _j__T271 BASE 72
assignw T272 _j__T271[0]
assignw T273 1
sub T274 T272 T273
assignw T275 _pi__T270[0]
assignw T276 _pi__T270[4]
lt T278 T274 0
geq T279 T274 T276
or T280 T278 T279
goifnot L13 T280
# EXIT POR OUT OF BOUNDS
assignw T281 ___OUT_OF_BOUNDS
print T281
exit 1
@label L13
mult T277 T274 4
add T277 T277 T275
assignw T282 T277[0]
add _j__T283 BASE 72
# Copy from "T282" to "_j__T283"
assignw _j__T283[0] T282
assignw T241 T282
goto _while_start__L9
@label _while_out__L10
add _pattern__T285 BASE 20
add _i__T286 BASE 68
assignw T287 _i__T286[0]
assignw T288 _pattern__T285[0]
assignw T289 _pattern__T285[4]
lt T291 T287 0
geq T292 T287 T289
or T293 T291 T292
goifnot L16 T293
# EXIT POR OUT OF BOUNDS
assignw T294 ___OUT_OF_BOUNDS
print T294
exit 1
@label L16
mult T290 T287 1
add T290 T290 T288
assignb T295 T290[0]
add _pattern__T296 BASE 20
add _j__T297 BASE 72
assignw T298 _j__T297[0]
assignw T299 _pattern__T296[0]
assignw T300 _pattern__T296[4]
lt T302 T298 0
geq T303 T298 T300
or T304 T302 T303
goifnot L17 T304
# EXIT POR OUT OF BOUNDS
assignw T305 ___OUT_OF_BOUNDS
print T305
exit 1
@label L17
mult T301 T298 1
add T301 T301 T299
assignb T306 T301[0]
eq T307 T295 T306
goifnot _if_else__L14 T307
# INICIO IF
add _pi__T308 BASE 56
add _i__T309 BASE 68
assignw T310 _i__T309[0]
add _j__T311 BASE 72
assignw T312 _j__T311[0]
assignw T313 1
add T314 T312 T313
assignw T315 _pi__T308[0]
assignw T316 _pi__T308[4]
lt T318 T310 0
geq T319 T310 T316
or T320 T318 T319
goifnot L18 T320
# EXIT POR OUT OF BOUNDS
assignw T321 ___OUT_OF_BOUNDS
print T321
exit 1
@label L18
mult T317 T310 4
add T317 T317 T315
# Copy from "T314" to "T317"
assignw T317[0] T314
assignw T284 T314
goto _if_out__L15
@label _if_else__L14
# INICIO ELSE
add _pi__T322 BASE 56
add _i__T323 BASE 68
assignw T324 _i__T323[0]
assignw T325 0
assignw T326 _pi__T322[0]
assignw T327 _pi__T322[4]
lt T329 T324 0
geq T330 T324 T327
or T331 T329 T330
goifnot L19 T331
# EXIT POR OUT OF BOUNDS
assignw T332 ___OUT_OF_BOUNDS
print T332
exit 1
@label L19
mult T328 T324 4
add T328 T328 T326
# Copy from "T325" to "T328"
assignw T328[0] T325
assignw T284 T325
@label _if_out__L15
# FOR BODY END
@label _for_step__L6
add _i__T226 _i__T226 T224
assignw BASE[68] _i__T226
assignw _for_result__T220 T284
# FOR END
goto _for_start__L5
@label _for_end__L7
assignw T333 0
add _last__T334 BASE 76
# Copy from "T333" to "_last__T334"
assignw _last__T334[0] T333
assignw T336 0
add _m__T337 BASE 36
assignw T338 _m__T337[0]
assignw T339 1
# FOR BEGIN
assignw BASE[80] T336
@label _for_start__L20
assignw _i__T341 BASE[80]
geq T340 _i__T341 T338
goif _for_end__L22 T340
# FOR BODY BEGIN
add _last__T342 BASE 76
assignw T343 _last__T342[0]
add _j__T344 BASE 84
# Copy from "T343" to "_j__T344"
assignw _j__T344[0] T343
assignw T345 0
add _curr__T346 BASE 88
# Copy from "T345" to "_curr__T346"
assignw _curr__T346[0] T345
assignw T347 0
@label _while_start__L23
add _j__T348 BASE 84
assignw T349 _j__T348[0]
assignw T350 0
gt T351 T349 T350
add _text__T352 BASE 48
add _i__T353 BASE 80
assignw T354 _i__T353[0]
assignw T355 _text__T352[0]
assignw T356 _text__T352[4]
lt T358 T354 0
geq T359 T354 T356
or T360 T358 T359
goifnot L25 T360
# EXIT POR OUT OF BOUNDS
assignw T361 ___OUT_OF_BOUNDS
print T361
exit 1
@label L25
mult T357 T354 1
add T357 T357 T355
assignb T362 T357[0]
add _pattern__T363 BASE 20
add _j__T364 BASE 84
assignw T365 _j__T364[0]
assignw T366 _pattern__T363[0]
assignw T367 _pattern__T363[4]
lt T369 T365 0
geq T370 T365 T367
or T371 T369 T370
goifnot L26 T371
# EXIT POR OUT OF BOUNDS
assignw T372 ___OUT_OF_BOUNDS
print T372
exit 1
@label L26
mult T368 T365 1
add T368 T368 T366
assignb T373 T368[0]
neq T374 T362 T373
and T375 T351 T374
goifnot _while_out__L24 T375
add _pi__T376 BASE 56
add _j__T377 BASE 84
assignw T378 _j__T377[0]
assignw T379 1
sub T380 T378 T379
assignw T381 _pi__T376[0]
assignw T382 _pi__T376[4]
lt T384 T380 0
geq T385 T380 T382
or T386 T384 T385
goifnot L27 T386
# EXIT POR OUT OF BOUNDS
assignw T387 ___OUT_OF_BOUNDS
print T387
exit 1
@label L27
mult T383 T380 4
add T383 T383 T381
assignw T388 T383[0]
add _j__T389 BASE 84
# Copy from "T388" to "_j__T389"
assignw _j__T389[0] T388
assignw T347 T388
goto _while_start__L23
@label _while_out__L24
add _text__T391 BASE 48
add _i__T392 BASE 80
assignw T393 _i__T392[0]
assignw T394 _text__T391[0]
assignw T395 _text__T391[4]
lt T397 T393 0
geq T398 T393 T395
or T399 T397 T398
goifnot L30 T399
# EXIT POR OUT OF BOUNDS
assignw T400 ___OUT_OF_BOUNDS
print T400
exit 1
@label L30
mult T396 T393 1
add T396 T396 T394
assignb T401 T396[0]
add _pattern__T402 BASE 20
add _j__T403 BASE 84
assignw T404 _j__T403[0]
assignw T405 _pattern__T402[0]
assignw T406 _pattern__T402[4]
lt T408 T404 0
geq T409 T404 T406
or T410 T408 T409
goifnot L31 T410
# EXIT POR OUT OF BOUNDS
assignw T411 ___OUT_OF_BOUNDS
print T411
exit 1
@label L31
mult T407 T404 1
add T407 T407 T405
assignb T412 T407[0]
eq T413 T401 T412
goifnot _if_else__L28 T413
# INICIO IF
add _j__T414 BASE 84
assignw T415 _j__T414[0]
assignw T416 1
add T417 T415 T416
add _curr__T418 BASE 88
# Copy from "T417" to "_curr__T418"
assignw _curr__T418[0] T417
assignw T390 T417
goto _if_out__L29
@label _if_else__L28
# INICIO ELSE
assignw T419 0
add _curr__T420 BASE 88
# Copy from "T419" to "_curr__T420"
assignw _curr__T420[0] T419
assignw T390 T419
@label _if_out__L29
add _curr__T421 BASE 88
assignw T422 _curr__T421[0]
add _last__T423 BASE 76
# Copy from "T422" to "_last__T423"
assignw _last__T423[0] T422
add _curr__T425 BASE 88
assignw T426 _curr__T425[0]
add _n__T427 BASE 8
assignw T428 _n__T427[0]
eq T429 T426 T428
goifnot _if_else__L32 T429
# INICIO IF
assignw T430 STACK
add STACK STACK 28
add T431 BASE 92
assignw T431[0] T430
assignw T431[4] 27
assignb T432 'H'
add T433 T430 0
# Copy from "T432" to "T433"
assignb T433[0] T432
assignb T434 'A'
add T435 T430 1
# Copy from "T434" to "T435"
assignb T435[0] T434
assignb T436 'Y'
add T437 T430 2
# Copy from "T436" to "T437"
assignb T437[0] T436
assignb T438 ' '
add T439 T430 3
# Copy from "T438" to "T439"
assignb T439[0] T438
assignb T440 'M'
add T441 T430 4
# Copy from "T440" to "T441"
assignb T441[0] T440
assignb T442 'A'
add T443 T430 5
# Copy from "T442" to "T443"
assignb T443[0] T442
assignb T444 'T'
add T445 T430 6
# Copy from "T444" to "T445"
assignb T445[0] T444
assignb T446 'C'
add T447 T430 7
# Copy from "T446" to "T447"
assignb T447[0] T446
assignb T448 'H'
add T449 T430 8
# Copy from "T448" to "T449"
assignb T449[0] T448
assignb T450 ' '
add T451 T430 9
# Copy from "T450" to "T451"
assignb T451[0] T450
assignb T452 'E'
add T453 T430 10
# Copy from "T452" to "T453"
assignb T453[0] T452
assignb T454 'N'
add T455 T430 11
# Copy from "T454" to "T455"
assignb T455[0] T454
assignb T456 ' '
add T457 T430 12
# Copy from "T456" to "T457"
assignb T457[0] T456
assignb T458 'L'
add T459 T430 13
# Copy from "T458" to "T459"
assignb T459[0] T458
assignb T460 'A'
add T461 T430 14
# Copy from "T460" to "T461"
assignb T461[0] T460
assignb T462 ' '
add T463 T430 15
# Copy from "T462" to "T463"
assignb T463[0] T462
assignb T464 'P'
add T465 T430 16
# Copy from "T464" to "T465"
assignb T465[0] T464
assignb T466 'O'
add T467 T430 17
# Copy from "T466" to "T467"
assignb T467[0] T466
assignb T468 'S'
add T469 T430 18
# Copy from "T468" to "T469"
assignb T469[0] T468
assignb T470 'I'
add T471 T430 19
# Copy from "T470" to "T471"
assignb T471[0] T470
assignb T472 'C'
add T473 T430 20
# Copy from "T472" to "T473"
assignb T473[0] T472
assignb T474 'I'
add T475 T430 21
# Copy from "T474" to "T475"
assignb T475[0] T474
assignb T476 'O'
add T477 T430 22
# Copy from "T476" to "T477"
assignb T477[0] T476
assignb T478 'N'
add T479 T430 23
# Copy from "T478" to "T479"
assignb T479[0] T478
assignb T480 ':'
add T481 T430 24
# Copy from "T480" to "T481"
assignb T481[0] T480
assignb T482 '\n'
add T483 T430 25
# Copy from "T482" to "T483"
assignb T483[0] T482
assignb T484 ' '
add T485 T430 26
# Copy from "T484" to "T485"
assignb T485[0] T484
assignw T486 T431[0]
print T486
add _i__T487 BASE 80
assignw T488 _i__T487[0]
add _n__T489 BASE 8
assignw T490 _n__T489[0]
assignw T491 1
sub T492 T490 T491
sub T493 T488 T492
printi T493
assignb T494 '\n'
printc T494
goto _if_out__L33
@label _if_else__L32
# INICIO ELSE
@label _if_out__L33
# FOR BODY END
@label _for_step__L21
add _i__T341 _i__T341 T339
assignw BASE[80] _i__T341
# FOR END
goto _for_start__L20
@label _for_end__L22
@label _kmp_end__L0
@endfunction 100
@function main__0 0
goto L35
@label L35
# Code to calculate parameters
# Push parameters
call _freturn__T495 kmp__0
@label _main_end__L34
@endfunction 0
@label endProgram
