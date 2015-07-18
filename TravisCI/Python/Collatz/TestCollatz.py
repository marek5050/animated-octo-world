#!/usr/bin/env python3

# -------------------------------
# projects/collatz/TestCollatz.py
# Copyright (C) 2015
# Glenn P. Downing
# -------------------------------

# https://docs.python.org/3.4/reference/simple_stmts.html#grammar-token-assert_stmt

# -------
# imports
# -------

from io       import StringIO
from unittest import main, TestCase

from Collatz import collatz_read, collatz_eval, collatz_print, collatz_solve, Cache

# -----------
# TestCollatz
# -----------

class TestCollatz (TestCase) :
    # ----
    # read
    # ----

    def test_read_1 (self) :
        s    = "1 10\n"
        i, j = collatz_read(s)
        self.assertEqual(i,  1)
        self.assertEqual(j, 10)

    def test_read_2 (self) :
        s    = "10 12\n"
        i, j = collatz_read(s)
        self.assertEqual(i,  10)
        self.assertEqual(j, 12)

    def test_read_3 (self) :
        s    = "15 20\n"
        i, j = collatz_read(s)
        self.assertEqual(i, 15)
        self.assertEqual(j, 20)

    # ----
    # eval
    # ----

    def test_eval_1 (self) :
        v = collatz_eval(1, 10)
        self.assertEqual(v, 20)

    def test_eval_2 (self) :
        v = collatz_eval(100, 200)
        self.assertEqual(v, 125)

    def test_eval_3 (self) :
        v = collatz_eval(201, 210)
        self.assertEqual(v, 89)

    def test_eval_4 (self) :
        v = collatz_eval(900, 1000)
        self.assertEqual(v, 174)

    def test_eval_5 (self) :
        v = collatz_eval(48501, 49500)
        self.assertEqual(v, 296)
    # -----
    # print
    # -----

    def test_print_1 (self) :
        w = StringIO()
        collatz_print(w, 1, 10, 20)
        self.assertEqual(w.getvalue(), "1 10 20\n")

    def test_print_2 (self) :
        w = StringIO()
        collatz_print(w, 2, 20, 30)
        self.assertEqual(w.getvalue(), "2 20 30\n")

    def test_print_3 (self) :
        w = StringIO()
        collatz_print(w, 10, 25, 30)
        self.assertEqual(w.getvalue(), "10 25 30\n")
    # -----
    # solve
    # -----

    def test_solve_1 (self) :
        r = StringIO("1 10\n100 200\n201 210\n900 1000\n")
        w = StringIO()
        collatz_solve(r, w)
        self.assertEqual(w.getvalue(), "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n")

    def test_solve_2 (self) :
        r = StringIO("10001 19000\n 10001 20000\n 12001 24000\n")
        w = StringIO()
        collatz_solve(r, w)
        self.assertEqual(w.getvalue(), "10001 19000 279\n10001 20000 279\n12001 24000 282\n")

    def test_solve_3 (self) :
        r = StringIO("46001 46500\n 46001 47000\n46001 47500\n")
        w = StringIO()
        collatz_solve(r, w)
        self.assertEqual(w.getvalue(), "46001 46500 283\n46001 47000 283\n46001 47500 314\n")

    def test_solve_4 (self) :
        r = StringIO("46001 52000\n 1 52000\n")
        w = StringIO()
        collatz_solve(r, w)
        self.assertEqual(w.getvalue(), "46001 52000 314\n1 52000 324\n")

    def test_cache_1 (self) :
        cache = Cache()
        self.assertEqual(cache.check(1,100), (100,119))

    def test_cache_2 (self) :
        cache = Cache()
        self.assertEqual(cache.check(301,400), (400,144))

    def test_cache_3 (self) :
        cache = Cache()
        self.assertEqual(cache.check(401,501), (500,142))


# ----
# main
# ----

if __name__ == "__main__" :
    main()

"""
% coverage3 run --branch TestCollatz.py >  TestCollatz.out 2>&1



% coverage3 report -m                   >> TestCollatz.out



% cat TestCollatz.out
.......
----------------------------------------------------------------------
Ran 7 tests in 0.001s

OK
Name          Stmts   Miss Branch BrMiss  Cover   Missing
---------------------------------------------------------
Collatz          18      0      6      0   100%
TestCollatz      33      1      2      1    94%   79
---------------------------------------------------------
TOTAL            51      1      8      1    97%
"""
