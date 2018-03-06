% Load data for the stock indices

data =[0	0	0
0	0	2
3	4	5
3	4	7
4	5	9
5	11	11
9	15	14
12	17	16
15	18	18
17	19	20
17	24	23
19	24	25
19	24	27
20	24	29
20	25	32
21	27	34
23	28	36
24	29	39
24	30	41
24	30	43
24	31	45
27	34	48
29	37	50
29	37	52
29	37	54
32	40	57
34	42	59
35	49	61
35	49	63
38	59	66
39	63	68
39	64	70
39	64	72
40	67	75
40	67	77
42	67	79
42	67	81
42	67	84
42	68	86
42	68	88
42	68	90
43	68	93
43	68	95
44	71	97
47	73	99
55	77	102
55	82	104
55	84	106
55	85	109
57	86	111
57	87	113
57	88	115
57	92	118
57	95	120
61	96	122
61	98	124
63	99	127
63	102	129
63	104	131
63	104	133
63	106	136
63	107	138
63	108	140
63	109	142
63	110	145
63	110	147
66	111	149
66	112	151
67	117	154
67	118	156
67	120	158
67	122	160
67	123	163
67	124	165
68	127	167
70	128	169
70	132	172
71	137	174
72	140	176
74	143	178
74	145	181
76	148	183
77	152	185
77	153	187
77	156	190
78	158	192
78	160	194
79	161	197
79	164	199
80	166	201
82	166	203
83	168	206
85	168	208
85	168	210
88	173	212
88	175	215
90	175	217
92	177	219
92	177	221
93	181	224
94	182	226
94	183	228
94	183	230
94	186	233
94	186	235
95	187	237
96	187	239
96	189	242
96	189	244
96	190	246
96	190	248
98	191	251
98	191	253
98	191	255
102	194	258
105	195	260
106	195	262
106	196	264
106	197	267
106	200	269
106	202	271
106	204	273
109	206	276
109	206	278
112	207	280
113	209	282
113	210	285
118	213	287
118	213	289
118	218	291
118	219	294
120	221	296
120	222	298
121	223	300
121	223	303
121	227	305
121	227	307
124	231	309
124	233	312
124	233	314
126	236	316
126	239	319
127	244	321
127	247	323
128	247	325
128	247	328
128	249	330
132	252	332
132	253	334
136	262	337
137	262	339
137	262	341
140	266	343
140	267	346
141	269	348
142	270	350
145	270	352
146	270	355
149	274	357
149	274	359
149	275	361
152	280	364
152	280	366
152	280	368
153	284	370
155	287	373
155	287	375
155	289	377
156	289	379
157	289	382
157	289	384
157	290	386
157	294	388
159	300	391
161	300	393
162	301	395
162	303	398
162	305	400
162	307	402
162	308	404
165	310	407
167	312	409
168	314	411
168	314	413
170	318	416
170	319	418
173	319	420
173	321	422
174	324	425
175	324	427
176	324	429
176	329	431
178	329	434
178	329	436
178	331	438
178	331	440
178	333	443
178	333	445
178	333	447
181	333	449
];

time = [0
2
12
14
18
27
38
45
51
56
64
68
70
73
77
82
87
92
95
97
100
109
116
118
120
129
135
145
147
163
170
173
175
182
184
188
190
193
196
198
200
204
206
212
219
234
241
245
249
254
257
260
267
272
279
283
289
294
298
300
305
308
311
314
318
320
326
329
338
341
345
349
353
356
362
367
374
382
388
395
400
407
414
417
423
428
432
437
442
447
451
457
461
463
473
478
482
488
490
498
502
505
507
513
515
519
522
527
529
532
534
540
542
544
554
560
563
566
570
575
579
583
591
593
599
604
608
618
620
627
631
637
640
644
647
653
655
664
669
671
678
684
692
697
700
703
707
716
719
735
738
740
749
753
758
762
767
771
780
782
785
796
798
800
807
815
817
821
824
828
830
833
839
850
854
858
863
867
871
874
882
888
893
895
904
907
912
916
923
926
929
936
941
943
947
949
954
956
958
963
];

% Plot the stock index values versus time
figure
plot(time, data)

% Use dateticks for the x axis
%datetick('x')

% Add title and axis labels
xlabel('Total Number of Ticks')
ylabel('Number of Ticks')
title('Number of Ticks Given to Processes with Different Tickets')

% Add a legend in the top, left corner
legend('A: 10 tickets', 'B: 20 tickets', 'C: 30 tickets')