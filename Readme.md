``` diff
*****************************************************************
- GenerateData: n = 1000 k=1000
NaiveFindIntersection duration: 5174 microsecnds
! Result: Found - false

EffectiveFindIntersection duration: 953 microsecnds
! Result: Found - false

+ Diff between durations[1] and durations[0]: -4221 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 1000 k=500
NaiveFindIntersection duration: 4239 microsecnds
! Result: Found - true Indexes (519, 520)

EffectiveFindIntersection duration: 502 microsecnds
! Result: Found - true Indexes (519, 520)

+ Diff between durations[1] and durations[0]: -3737 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 1000 k=250
NaiveFindIntersection duration: 2890 microsecnds
! Result: Found - true Indexes (300, 301)

EffectiveFindIntersection duration: 350 microsecnds
! Result: Found - true Indexes (300, 301)

+ Diff between durations[1] and durations[0]: -2540 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 1000 k=10
NaiveFindIntersection duration: 410 microsecnds
! Result: Found - true Indexes (37, 38)

EffectiveFindIntersection duration: 222 microsecnds
! Result: Found - true Indexes (37, 38)

+ Diff between durations[1] and durations[0]: -188 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 1000 k=1
NaiveFindIntersection duration: 790 microsecnds
! Result: Found - true Indexes (37, 38)

EffectiveFindIntersection duration: 254 microsecnds
! Result: Found - true Indexes (37, 38)

+ Diff between durations[1] and durations[0]: -536 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 5000 k=5000
NaiveFindIntersection duration: 129960 microsecnds
! Result: Found - false

EffectiveFindIntersection duration: 3730 microsecnds
! Result: Found - false

+ Diff between durations[1] and durations[0]: -126230 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 5000 k=2500
NaiveFindIntersection duration: 90046 microsecnds
! Result: Found - true Indexes (2562, 2563)

EffectiveFindIntersection duration: 2491 microsecnds
! Result: Found - true Indexes (2562, 2563)

+ Diff between durations[1] and durations[0]: -87555 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 5000 k=1250
NaiveFindIntersection duration: 56279 microsecnds
! Result: Found - true Indexes (1256, 1257)

EffectiveFindIntersection duration: 1104 microsecnds
! Result: Found - true Indexes (1256, 1257)

+ Diff between durations[1] and durations[0]: -55175 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 5000 k=50
NaiveFindIntersection duration: 4431 microsecnds
! Result: Found - true Indexes (56, 57)

EffectiveFindIntersection duration: 591 microsecnds
! Result: Found - true Indexes (56, 57)

+ Diff between durations[1] and durations[0]: -3840 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 5000 k=1
NaiveFindIntersection duration: 2434 microsecnds
! Result: Found - true Indexes (37, 38)

EffectiveFindIntersection duration: 653 microsecnds
! Result: Found - true Indexes (37, 38)

+ Diff between durations[1] and durations[0]: -1781 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 20000 k=20000
NaiveFindIntersection duration: 1790714 microsecnds
! Result: Found - false

EffectiveFindIntersection duration: 9973 microsecnds
! Result: Found - false

+ Diff between durations[1] and durations[0]: -1780741 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 20000 k=10000
NaiveFindIntersection duration: 1726046 microsecnds
! Result: Found - true Indexes (10036, 10037)

EffectiveFindIntersection duration: 6336 microsecnds
! Result: Found - true Indexes (10036, 10037)

+ Diff between durations[1] and durations[0]: -1719710 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 20000 k=5000
NaiveFindIntersection duration: 1062647 microsecnds
! Result: Found - true Indexes (5032, 5033)

EffectiveFindIntersection duration: 4049 microsecnds
! Result: Found - true Indexes (5032, 5033)

+ Diff between durations[1] and durations[0]: -1058598 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 20000 k=200
NaiveFindIntersection duration: 56965 microsecnds
! Result: Found - true Indexes (216, 217)

EffectiveFindIntersection duration: 1989 microsecnds
! Result: Found - true Indexes (216, 217)

+ Diff between durations[1] and durations[0]: -54976 microsecnds
*****************************************************************

*****************************************************************
- GenerateData: n = 20000 k=1
NaiveFindIntersection duration: 9722 microsecnds
! Result: Found - true Indexes (37, 38)

EffectiveFindIntersection duration: 1988 microsecnds
! Result: Found - true Indexes (37, 38)

+ Diff between durations[1] and durations[0]: -7734 microsecnds
*****************************************************************


```