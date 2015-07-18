#!/usr/bin/env python3

# ---------------------------
# projects/collatz/Collatz.py
# Copyright (C) 2015
# Marek Bejda
# ---------------------------

import sys
# ------------
# Cache class
# ------------
class Cache:
    """
	Starts of as a static array, but lazily gains more key/value pairs.
	At 1000 number interval it'll have about 1000 keys.
        cache dictionary, lazy cache, 100 and 1000 number intervals are stored.
     """
    cache = {1: (100,119),
            101: (200,125),
            201: (300,128),
            301: (400,144),
            401: (500,142),
            501: (600,137),
            601: (700,145),
            701: (800,171),
            801: (900,179),
            901: (1000,174),
            1001: (1100,169),
            1101: (1200,182),
            1201: (1300,177),
            1301: (1400,177),
            1401: (1500,172),
            1501: (1600,167),
            1601: (1700,180),
            1701: (1800,180),
            1801: (1900,175),
            1901: (2000,175),
            2001: (2100,157),
            2101: (2200,170),
            2201: (2300,183),
            2301: (2400,183),
            2401: (2500,209),
            2501: (2600,178),
            2601: (2700,191),
            2701: (2800,173),
            2801: (2900,173),
            2901: (3000,217),
            3001: (3100,186),
            3101: (3200,199),
            3201: (3300,168),
            3301: (3400,181),
            3401: (3500,181),
            3501: (3600,194),
            3601: (3700,207),
            3701: (3800,238),
            3801: (3900,176),
            3901: (4000,189),
            4001: (4100,189),
            4101: (4200,189),
            4201: (4300,202),
            4301: (4400,215),
            4401: (4500,184),
            4501: (4600,184),
            4601: (4700,184),
            4701: (4800,197),
            4801: (4900,179),
            4901: (5000,210),
            5001: (5100,179),
            5101: (5200,179),
            5201: (5300,192),
            5301: (5400,192),
            5401: (5500,192),
            5501: (5600,236),
            5601: (5700,205),
            5701: (5800,205),
            5801: (5900,218),
            5901: (6000,187),
            6001: (6100,187),
            6101: (6200,262),
            6201: (6300,187),
            6301: (6400,200),
            6401: (6500,169),
            6501: (6600,244),
            6601: (6700,182),
            6701: (6800,182),
            6801: (6900,182),
            6901: (7000,257),
            7001: (7100,195),
            7101: (7200,195),
            7201: (7300,177),
            7301: (7400,208),
            7401: (7500,239),
            7501: (7600,208),
            7601: (7700,177),
            7701: (7800,221),
            7801: (7900,190),
            7901: (8000,252),
            8001: (8100,190),
            8101: (8200,190),
            8201: (8300,190),
            8301: (8400,234),
            8401: (8500,203),
            8501: (8600,203),
            8601: (8700,203),
            8701: (8800,216),
            8801: (8900,185),
            8901: (9000,247),
            9001: (9100,185),
            9101: (9200,198),
            9201: (9300,260),
            9301: (9400,198),
            9401: (9500,198),
            9501: (9600,198),
            9601: (9700,185),
            9701: (9800,198),
            9801: (9900,242)}

    def check(self,min, max):
        if min in self.cache:
            values = self.cache[min]
            return values
        return (min,0)

cache = Cache()

# ------------
# collatz_read
# ------------

def collatz_read (s) :
    """
    read two ints
    s a string
    return a list of two ints, representing the beginning and end of a range, [i, j]
    """
    a = s.split()
    return [int(a[0]), int(a[1])]

# ------------
# collatz_eval
# ------------
"""
   This part actually evaluates the largest cycle between the two numbers.
   We check for the 1001 boundary and store the interval we're caching.
   When we hit the next boundary we store the local maximum.
   We keep evaluating until everything is built, this way we create
   our cache 'database'

   Added the couple of improvements we discussed in class.
	"""
def collatz_eval (i, j) :
    assert (i > 0)
    assert (j > 0)

    maxCycleLength = 0
    minValue = min(i,j)
    maxValue = max(i,j)
    m = maxValue // 2
    if m > minValue:
        minValue = m
    currentValue = minValue
    _cache_value = 0
    _cache_max = 0

    while (currentValue in range(minValue,maxValue+1)):
            if( (currentValue < 1000 and currentValue % 100 == 1) or currentValue % 1000 == 1):
                res = cache.check(currentValue, maxValue)

                if (res[0] > currentValue and res[0] <= maxValue):
                    # print("Cache hit at: ", currentValue,  " ", res[0], res[1])
                   currentValue = res[0]
               	   if (res[1] > maxCycleLength):
                        maxCycleLength = res[1]
                        _cache_value = 0
                        _cache_max   = 0
                        continue

                if(currentValue % 1000 == 1):

                    if( _cache_value != 0 and currentValue - _cache_value >= 1000):
                        cache.cache[_cache_value]=(currentValue-1, _cache_max)
                        _cache_value = 0

                    if( _cache_value == 0 and maxValue - currentValue > 1000):
                        _cache_max   = 0
                        _cache_value = currentValue

            value = currentValue
            cycleLength = 1
            while value != 1:
              if(value % 2 == 0):
                        value //= 2
                        cycleLength+=1
              else:
                        value = value + (value>>1) + 1
                        cycleLength+=2

            if cycleLength > maxCycleLength:
                maxCycleLength = cycleLength
            if(_cache_value != 0 and _cache_max < cycleLength):
                    _cache_max = cycleLength


            currentValue=currentValue + 1
    assert (maxCycleLength > 0)
    return maxCycleLength

# -------------
# collatz_print
# -------------

def collatz_print (w, i, j, v) :
    """
    print three ints
    w a writer
    i the beginning of the range, inclusive
    j the end       of the range, inclusive
    v the max cycle length
    """
    assert (i > 0)
    assert (j > 0)
    assert (v > 0)
    w.write(str(i) + " " + str(j) + " " + str(v) + "\n")

# -------------
# collatz_solve
# -------------

def collatz_solve (r, w) :
    """
    r a reader
    w a writer
    """
    for s in r :
        i, j = collatz_read(s)
        v    = collatz_eval(i, j)
        collatz_print(w, i, j, v)

if __name__ == "__main__" :
    collatz_solve(sys.stdin, sys.stdout)
