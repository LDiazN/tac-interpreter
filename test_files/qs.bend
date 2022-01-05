call ___main main__0
exit 0
@function swapi__0 12
add a__T0 BASE 0
assignw T1 a__T0[0]
add tmp__T2 BASE 8
# Copy from "T1" to "tmp__T2"
assignw tmp__T2[0] T1
add b__T3 BASE 4
assignw T4 b__T3[0]
add a__T5 BASE 0
# Copy from "T4" to "a__T5"
# Copy from "T4" to "a__T5"
assignw a__T5[0] T4
add tmp__T6 BASE 8
assignw T7 tmp__T6[0]
add b__T8 BASE 4
# Copy from "T7" to "b__T8"
# Copy from "T7" to "b__T8"
assignw b__T8[0] T7
@label swapi_end__L0
@endfunction 12
@function quickSort__0 20
add low__T10 BASE 0
assignw T11 low__T10[0]
add high__T12 BASE 4
assignw T13 high__T12[0]
lt T14 T11 T13
goifnot if_else__L2 T14
# INICIO IF
# Code to calculate parameters
add low__T15 BASE 0
assignw T16 low__T15[0]
add high__T17 BASE 4
assignw T18 high__T17[0]
add ARR__T19 BASE 8
# Push parameters
param T21 0
# Copy from "T16" to "T21"
assignw T21[0] T16
param T22 4
# Copy from "T18" to "T22"
assignw T22[0] T18
param T23 8
# Copy from "ARR__T19" to "T23"
memcpy T23 ARR__T19 8
call freturn__T20 partition__0
add pi__T24 BASE 16
# Copy from "freturn__T20" to "pi__T24"
assignw pi__T24[0] freturn__T20
# Code to calculate parameters
add low__T25 BASE 0
assignw T26 low__T25[0]
add pi__T27 BASE 16
assignw T28 pi__T27[0]
assignw T29 1
sub T30 T28 T29
add ARR__T31 BASE 8
# Push parameters
param T33 0
# Copy from "T26" to "T33"
assignw T33[0] T26
param T34 4
# Copy from "T30" to "T34"
assignw T34[0] T30
param T35 8
# Copy from "ARR__T31" to "T35"
memcpy T35 ARR__T31 8
call freturn__T32 quickSort__0
# Code to calculate parameters
add pi__T36 BASE 16
assignw T37 pi__T36[0]
assignw T38 1
add T39 T37 T38
add high__T40 BASE 4
assignw T41 high__T40[0]
add ARR__T42 BASE 8
# Push parameters
param T44 0
# Copy from "T39" to "T44"
assignw T44[0] T39
param T45 4
# Copy from "T41" to "T45"
assignw T45[0] T41
param T46 8
# Copy from "ARR__T42" to "T46"
memcpy T46 ARR__T42 8
call freturn__T43 quickSort__0
goto if_out__L3
@label if_else__L2
# INICIO ELSE
@label if_out__L3
@label quickSort_end__L1
@endfunction 20
@function partition__0 28
add ARR__T47 BASE 8
add high__T48 BASE 4
assignw T49 high__T48[0]
assignw T50 ARR__T47[0]
assignw T51 ARR__T47[4]
mult T52 T49 4
add T52 T52 T50
assignw T56 T52[0]
add pivot__T57 BASE 16
# Copy from "T56" to "pivot__T57"
assignw pivot__T57[0] T56
add low__T58 BASE 0
assignw T59 low__T58[0]
assignw T60 1
sub T61 T59 T60
add i__T62 BASE 20
# Copy from "T61" to "i__T62"
assignw i__T62[0] T61
add low__T64 BASE 0
assignw T65 low__T64[0]
add high__T66 BASE 4
assignw T67 high__T66[0]
assignw T68 1
# FOR BEGIN
assignw BASE[24] T65
@label for_start__L6
assignw j__T70 BASE[24]
geq T69 j__T70 T67
goif for_end__L8 T69
# FOR BODY BEGIN
add ARR__T72 BASE 8
add j__T73 BASE 24
assignw T74 j__T73[0]
assignw T75 ARR__T72[0]
assignw T76 ARR__T72[4]
mult T77 T74 4
add T77 T77 T75
assignw T81 T77[0]
add pivot__T82 BASE 16
assignw T83 pivot__T82[0]
lt T84 T81 T83
goifnot if_else__L9 T84
# INICIO IF
add i__T85 BASE 20
assignw T86 i__T85[0]
assignw T87 1
add T88 T86 T87
add i__T89 BASE 20
# Copy from "T88" to "i__T89"
assignw i__T89[0] T88
# Code to calculate parameters
add ARR__T90 BASE 8
add i__T91 BASE 20
assignw T92 i__T91[0]
assignw T93 ARR__T90[0]
assignw T94 ARR__T90[4]
mult T95 T92 4
add T95 T95 T93
assignw T99 T95[0]
add ARR__T100 BASE 8
add j__T101 BASE 24
assignw T102 j__T101[0]
assignw T103 ARR__T100[0]
assignw T104 ARR__T100[4]
mult T105 T102 4
add T105 T105 T103
assignw T109 T105[0]
# Push parameters
param T111 0
# Copy from "T99" to "T111"
# Copy from "T99" to "T111"
assignw T111[0] T99
param T112 4
# Copy from "T109" to "T112"
# Copy from "T109" to "T112"
assignw T112[0] T109
call freturn__T110 swapi__0
# Assign reference of array access
add ARR__T113 BASE 8
add i__T114 BASE 20
assignw T115 i__T114[0]
assignw ARR__T113 ARR__T113[0]
mult T115 T115 4
add ARR__T113 ARR__T113 T115
assignw T111 T111[0]
# Copy from "T111" to "ARR__T113"
assignw ARR__T113[0] T111
# Assign reference of array access
add ARR__T116 BASE 8
add j__T117 BASE 24
assignw T118 j__T117[0]
assignw ARR__T116 ARR__T116[0]
mult T118 T118 4
add ARR__T116 ARR__T116 T118
assignw T112 T112[0]
# Copy from "T112" to "ARR__T116"
assignw ARR__T116[0] T112
goto if_out__L10
@label if_else__L9
# INICIO ELSE
@label if_out__L10
# FOR BODY END
@label for_step__L7
add j__T70 j__T70 T68
assignw BASE[24] j__T70
# FOR END
goto for_start__L6
@label for_end__L8
# Code to calculate parameters
add ARR__T119 BASE 8
add i__T120 BASE 20
assignw T121 i__T120[0]
assignw T122 1
add T123 T121 T122
assignw T124 ARR__T119[0]
assignw T125 ARR__T119[4]
mult T126 T123 4
add T126 T126 T124
assignw T130 T126[0]
add ARR__T131 BASE 8
add high__T132 BASE 4
assignw T133 high__T132[0]
assignw T134 ARR__T131[0]
assignw T135 ARR__T131[4]
mult T136 T133 4
add T136 T136 T134
assignw T140 T136[0]
# Push parameters
param T142 0
# Copy from "T130" to "T142"
# Copy from "T130" to "T142"
assignw T142[0] T130
param T143 4
# Copy from "T140" to "T143"
# Copy from "T140" to "T143"
assignw T143[0] T140
call freturn__T141 swapi__0
# Assign reference of array access
add ARR__T144 BASE 8
add i__T145 BASE 20
assignw T146 i__T145[0]
assignw T147 1
add T148 T146 T147
assignw ARR__T144 ARR__T144[0]
mult T148 T148 4
add ARR__T144 ARR__T144 T148
assignw T142 T142[0]
# Copy from "T142" to "ARR__T144"
assignw ARR__T144[0] T142
# Assign reference of array access
add ARR__T149 BASE 8
add high__T150 BASE 4
assignw T151 high__T150[0]
assignw ARR__T149 ARR__T149[0]
mult T151 T151 4
add ARR__T149 ARR__T149 T151
assignw T143 T143[0]
# Copy from "T143" to "ARR__T149"
assignw ARR__T149[0] T143
add i__T152 BASE 20
assignw T153 i__T152[0]
assignw T154 1
add T155 T153 T154
return T155
@label partition_end__L4
@endfunction 28
@function main__0 40
assignw BASE[0] STACK
assignw T156 50
assignw BASE[4] T156
mult T156 T156 4
add STACK STACK T156
@label while_start__L17
assignb T158 True
goifnot while_out__L18 T158
assignw T159 STACK
add STACK STACK 32
add T160 BASE 8
assignw T160[0] T159
assignw T160[4] 32
assignb T161 'D'
add T162 T159 0
# Copy from "T161" to "T162"
assignb T162[0] T161
assignb T163 'E'
add T164 T159 1
# Copy from "T163" to "T164"
assignb T164[0] T163
assignb T165 ' '
add T166 T159 2
# Copy from "T165" to "T166"
assignb T166[0] T165
assignb T167 '0'
add T168 T159 3
# Copy from "T167" to "T168"
assignb T168[0] T167
assignb T169 ' '
add T170 T159 4
# Copy from "T169" to "T170"
assignb T170[0] T169
assignb T171 'P'
add T172 T159 5
# Copy from "T171" to "T172"
assignb T172[0] T171
assignb T173 'A'
add T174 T159 6
# Copy from "T173" to "T174"
assignb T174[0] T173
assignb T175 'R'
add T176 T159 7
# Copy from "T175" to "T176"
assignb T176[0] T175
assignb T177 'A'
add T178 T159 8
# Copy from "T177" to "T178"
assignb T178[0] T177
assignb T179 ' '
add T180 T159 9
# Copy from "T179" to "T180"
assignb T180[0] T179
assignb T181 'T'
add T182 T159 10
# Copy from "T181" to "T182"
assignb T182[0] T181
assignb T183 'E'
add T184 T159 11
# Copy from "T183" to "T184"
assignb T184[0] T183
assignb T185 'R'
add T186 T159 12
# Copy from "T185" to "T186"
assignb T186[0] T185
assignb T187 'M'
add T188 T159 13
# Copy from "T187" to "T188"
assignb T188[0] T187
assignb T189 'I'
add T190 T159 14
# Copy from "T189" to "T190"
assignb T190[0] T189
assignb T191 'N'
add T192 T159 15
# Copy from "T191" to "T192"
assignb T192[0] T191
assignb T193 'A'
add T194 T159 16
# Copy from "T193" to "T194"
assignb T194[0] T193
assignb T195 'R'
add T196 T159 17
# Copy from "T195" to "T196"
assignb T196[0] T195
assignb T197 ' '
add T198 T159 18
# Copy from "T197" to "T198"
assignb T198[0] T197
assignb T199 'O'
add T200 T159 19
# Copy from "T199" to "T200"
assignb T200[0] T199
assignb T201 ' '
add T202 T159 20
# Copy from "T201" to "T202"
assignb T202[0] T201
assignb T203 '1'
add T204 T159 21
# Copy from "T203" to "T204"
assignb T204[0] T203
assignb T205 ' '
add T206 T159 22
# Copy from "T205" to "T206"
assignb T206[0] T205
assignb T207 'C'
add T208 T159 23
# Copy from "T207" to "T208"
assignb T208[0] T207
assignb T209 'O'
add T210 T159 24
# Copy from "T209" to "T210"
assignb T210[0] T209
assignb T211 'N'
add T212 T159 25
# Copy from "T211" to "T212"
assignb T212[0] T211
assignb T213 'T'
add T214 T159 26
# Copy from "T213" to "T214"
assignb T214[0] T213
assignb T215 'I'
add T216 T159 27
# Copy from "T215" to "T216"
assignb T216[0] T215
assignb T217 'N'
add T218 T159 28
# Copy from "T217" to "T218"
assignb T218[0] T217
assignb T219 'U'
add T220 T159 29
# Copy from "T219" to "T220"
assignb T220[0] T219
assignb T221 'A'
add T222 T159 30
# Copy from "T221" to "T222"
assignb T222[0] T221
assignb T223 'R'
add T224 T159 31
# Copy from "T223" to "T224"
assignb T224[0] T223
assignw T225 T160[0]
print T225
readi T226
add finish__T227 BASE 16
# Copy from "T226" to "finish__T227"
assignw finish__T227[0] T226
add finish__T229 BASE 16
assignw T230 finish__T229[0]
assignw T231 0
eq T232 T230 T231
goifnot if_else__L19 T232
# INICIO IF
goto while_out__L18
goto if_out__L20
@label if_else__L19
# INICIO ELSE
assignw T233 STACK
add STACK STACK 33
add T234 BASE 20
assignw T234[0] T233
assignw T234[4] 33
assignb T235 'I'
add T236 T233 0
# Copy from "T235" to "T236"
assignb T236[0] T235
assignb T237 'N'
add T238 T233 1
# Copy from "T237" to "T238"
assignb T238[0] T237
assignb T239 'T'
add T240 T233 2
# Copy from "T239" to "T240"
assignb T240[0] T239
assignb T241 'R'
add T242 T233 3
# Copy from "T241" to "T242"
assignb T242[0] T241
assignb T243 'O'
add T244 T233 4
# Copy from "T243" to "T244"
assignb T244[0] T243
assignb T245 'D'
add T246 T233 5
# Copy from "T245" to "T246"
assignb T246[0] T245
assignb T247 'U'
add T248 T233 6
# Copy from "T247" to "T248"
assignb T248[0] T247
assignb T249 'Z'
add T250 T233 7
# Copy from "T249" to "T250"
assignb T250[0] T249
assignb T251 'C'
add T252 T233 8
# Copy from "T251" to "T252"
assignb T252[0] T251
assignb T253 'A'
add T254 T233 9
# Copy from "T253" to "T254"
assignb T254[0] T253
assignb T255 ' '
add T256 T233 10
# Copy from "T255" to "T256"
assignb T256[0] T255
assignb T257 'L'
add T258 T233 11
# Copy from "T257" to "T258"
assignb T258[0] T257
assignb T259 'A'
add T260 T233 12
# Copy from "T259" to "T260"
assignb T260[0] T259
assignb T261 ' '
add T262 T233 13
# Copy from "T261" to "T262"
assignb T262[0] T261
assignb T263 'C'
add T264 T233 14
# Copy from "T263" to "T264"
assignb T264[0] T263
assignb T265 'A'
add T266 T233 15
# Copy from "T265" to "T266"
assignb T266[0] T265
assignb T267 'N'
add T268 T233 16
# Copy from "T267" to "T268"
assignb T268[0] T267
assignb T269 'T'
add T270 T233 17
# Copy from "T269" to "T270"
assignb T270[0] T269
assignb T271 'I'
add T272 T233 18
# Copy from "T271" to "T272"
assignb T272[0] T271
assignb T273 'D'
add T274 T233 19
# Copy from "T273" to "T274"
assignb T274[0] T273
assignb T275 'A'
add T276 T233 20
# Copy from "T275" to "T276"
assignb T276[0] T275
assignb T277 'D'
add T278 T233 21
# Copy from "T277" to "T278"
assignb T278[0] T277
assignb T279 ' '
add T280 T233 22
# Copy from "T279" to "T280"
assignb T280[0] T279
assignb T281 'D'
add T282 T233 23
# Copy from "T281" to "T282"
assignb T282[0] T281
assignb T283 'E'
add T284 T233 24
# Copy from "T283" to "T284"
assignb T284[0] T283
assignb T285 ' '
add T286 T233 25
# Copy from "T285" to "T286"
assignb T286[0] T285
assignb T287 'E'
add T288 T233 26
# Copy from "T287" to "T288"
assignb T288[0] T287
assignb T289 'N'
add T290 T233 27
# Copy from "T289" to "T290"
assignb T290[0] T289
assignb T291 'T'
add T292 T233 28
# Copy from "T291" to "T292"
assignb T292[0] T291
assignb T293 'E'
add T294 T233 29
# Copy from "T293" to "T294"
assignb T294[0] T293
assignb T295 'R'
add T296 T233 30
# Copy from "T295" to "T296"
assignb T296[0] T295
assignb T297 'O'
add T298 T233 31
# Copy from "T297" to "T298"
assignb T298[0] T297
assignb T299 'S'
add T300 T233 32
# Copy from "T299" to "T300"
assignb T300[0] T299
assignw T301 T234[0]
print T301
readi T302
add n__T303 BASE 28
# Copy from "T302" to "n__T303"
assignw n__T303[0] T302
assignw T305 1
add n__T306 BASE 28
assignw T307 n__T306[0]
assignw T308 1
add T309 T307 T308
assignw T310 1
# FOR BEGIN
assignw BASE[32] T305
@label for_start__L21
assignw i__T312 BASE[32]
geq T311 i__T312 T309
goif for_end__L23 T311
# FOR BODY BEGIN
readi T313
add ARR__T314 BASE 0
add i__T315 BASE 32
assignw T316 i__T315[0]
assignw ARR__T314 ARR__T314[0]
mult T316 T316 4
add ARR__T314 ARR__T314 T316
# Copy from "T313" to "ARR__T314"
assignw ARR__T314[0] T313
# FOR BODY END
@label for_step__L22
add i__T312 i__T312 T310
assignw BASE[32] i__T312
# FOR END
goto for_start__L21
@label for_end__L23
# Code to calculate parameters
assignw T317 1
add n__T318 BASE 28
assignw T319 n__T318[0]
add ARR__T320 BASE 0
# Push parameters
param T322 0
# Copy from "T317" to "T322"
assignw T322[0] T317
param T323 4
# Copy from "T319" to "T323"
assignw T323[0] T319
param T324 8
# Copy from "ARR__T320" to "T324"
memcpy T324 ARR__T320 8
call freturn__T321 quickSort__0
assignw T326 1
add n__T327 BASE 28
assignw T328 n__T327[0]
assignw T329 1
add T330 T328 T329
assignw T331 1
# FOR BEGIN
assignw BASE[36] T326
@label for_start__L24
assignw i__T333 BASE[36]
geq T332 i__T333 T330
goif for_end__L26 T332
# FOR BODY BEGIN
# INICIO PRINT
add ARR__T334 BASE 0
add i__T335 BASE 36
assignw T336 i__T335[0]
assignw T337 ARR__T334[0]
assignw T338 ARR__T334[4]
mult T339 T336 4
add T339 T339 T337
assignw T343 T339[0]
printi T343
# FINAL PRINT
# FOR BODY END
@label for_step__L25
add i__T333 i__T333 T331
assignw BASE[36] i__T333
# FOR END
goto for_start__L24
@label for_end__L26
@label if_out__L20
goto while_start__L17
@label while_out__L18
@label main_end__L16
@endfunction 40
@label endProgram
