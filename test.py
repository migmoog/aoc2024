import subprocess
import os
import sys

testdir = "tests"
def load_test(filename):
    return os.path.join(testdir, filename)

# decorators :-)
tests=[]
def aoc_test(day_index, tfilename):
    daystr = f"Day {day_index}"
    def wrapper(func):
        def test():
            with open(load_test(tfilename)) as t:
                print(f"=======Running {daystr}=======")
                process = subprocess.run(["./aoc", str(day_index)], stdin=t, 
                                         check=True, capture_output=True)
                output = process.stdout.decode()
                try:
                    func(output)
                    print(daystr + " successful")
                except AssertionError:
                    print(f"❌Failed test, output was:❌\n{output}")
                print("===========================")
        tests.append(test)
        return test
    return wrapper 

@aoc_test(1, "d1t")
def d1(output):
    assert "Day 1 part 1: 11" in output 
    assert "Day 1 part 2: 31" in output

@aoc_test(2, "d2t")
def d2(output):
    assert "part 1: 2" in output
    assert "part 2: 4" in output

@aoc_test(3, "d3t")
def d3(output):
    assert "part 1: 161" in output

@aoc_test(3, "d3t2")
def d3t2(output):
    assert "part 2: 48" in output

@aoc_test(3, "d3gpt")
def d3gpt(output):
    assert f"part 2: {123 * 456}" in output

@aoc_test(4, "d4t")
def d4(output):
    assert """....XXMAS.
.SAMXMS...
...S..A...
..A.A.MS.X
XMASAMX.MM
X.....XA.A
S.S.S.S.SS
.A.A.A.A.A
..M.M.M.MM
.X.X.XMASX""" in output
    assert "part 1: 18" in output

    #part 2 junk
    assert """
.M.S......
..A..MSMS.
.M.S.MAA..
..A.ASMSM.
.M.S.M....
..........
S.S.S.S.S.
.A.A.A.A..
M.M.M.M.M.
..........
    """ 
    assert "part 2: 9" in output

# running tests
if len(sys.argv) > 1:
    day_index = int(sys.argv[1]) 
    print("Running specific Day: " + day_index)
    tests[day_index-1]()    
else:
    for t in tests: t()