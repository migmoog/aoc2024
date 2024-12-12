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

# running tests
if len(sys.argv) > 1:
    day_index = int(sys.argv[1]) 
    print("Running specific Day: " + day_index)
    tests[day_index-1]()    
else:
    for t in tests: t()