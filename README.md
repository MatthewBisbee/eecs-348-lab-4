# EECS 348 Lab 4 — C Programming

## Submission files

Submit the public repository URL. The required files are `task1.c`, `task2.c`,
`Makefile` (with `all` and `clean` targets), and `ai_usage_log.md`.
The AI-log guide also asks for submission of the log file itself, so attach it
separately if the course submission page provides that upload.

`README.md`, `.gitignore`, and `tests/` are optional supporting files retained
for reproducible builds, demo instructions, and regression checks. Instructor
handouts and compiled artifacts are not included in the submitted file tree.

## Build and run

```sh
make all
./task1
./task2
make clean
```

The Makefile uses GCC and C11 with `-Wall -Wextra -Wpedantic`. `all` builds
both executables; `clean` removes both. Each program is self-contained in its
required source file, `task1.c` or `task2.c`.

## Task 1: Football score possibilities

Enter a nonnegative integer score. The program lists every distinct combination
of 8-point touchdowns, 7-point touchdowns, 6-point touchdowns, 3-point field
goals, and 2-point safeties, in the order shown in the assignment. It repeats
until you enter `1`. Zero produces the all-zero combination.

Negative scores, fractions, text, trailing junk, oversized lines, and values
outside the C `int` range are rejected and prompted again. End-of-file ends
the program gracefully because no more input is available. Very large valid
scores can generate enormous output; the assignment requires all combinations.

The loops enumerate the first four counts; the remaining points must be even
to form safeties. Each combination is emitted once without storing the list.

## Task 2: Temperature conversion

Enter a numeric temperature, its original scale, and its target scale (`C`,
`F`, or `K`; lowercase also works). The program prints the converted value to
two decimal places and a category and advisory. Same-scale conversion is valid.

Conversion uses Celsius as the intermediate scale:

- Fahrenheit to Celsius: `(F - 32) / 9 * 5`
- Kelvin to Celsius: `K - 273.15`
- Celsius to Fahrenheit: `C / 5 * 9 + 32`
- Celsius to Kelvin: `C + 273.15`

Categories use the unrounded Celsius value regardless of the output scale:

| Celsius range | Category | Advisory |
| --- | --- | --- |
| Below 0 | Freezing | Bundle up and watch for ice! |
| 0 to below 10 | Cold | Wear a jacket! |
| 10 to below 25 | Comfortable | Enjoy the weather! |
| 25 to below 35 | Hot | Drink lots of water! |
| 35 and above | Extreme Heat | Stay indoors and stay hydrated! |

The PDF labels itself “Lab 8” although the current assignment is Lab 4. Its Hot
interval says both “25°C to 35°C” and `[20, 35)`; this implementation uses
`[25, 35)` to avoid overlapping Comfortable. Exactly 35°C is Extreme Heat,
following the PDF's `[35, infinity)` interval.

Malformed numbers, nonfinite values, unsupported scales, and temperatures
below absolute zero are rejected. After a below-absolute-zero value, enter
the temperature and original scale again. A conversion beyond the supported
floating-point range reports an error. End-of-file exits gracefully.

## Tests and demo

Run the standard-library Python test suite with:

```sh
make test
```

The suite checks every score from 0 through 100 (except the stop value) against
an independent dynamic-programming count, checks uniqueness and point totals,
and compares score 25 to all 38 rows extracted from the PDF. It also checks all
nine scale pairs, category boundaries, absolute zero, invalid-input recovery,
long lines, numeric range errors, repeated scores, the stop value, and EOF.

Use Cycle for the live demo to match the environment already verified for this
submission. Local execution is convenient for practice. Unless the TA gives
different directions, first show interactive runs, then the automated tests.

From your Mac terminal, connect to Cycle:

```sh
ssh m755b852@cycle1.eecs.ku.edu
```

Then run these commands on Cycle. This uses a fresh public clone and removes
the temporary demo directory when you leave the SSH session:

```sh
demo_dir=$(mktemp -d /tmp/m755b852-c-test.XXXXXX)
trap 'cd /tmp; rm -rf -- "$demo_dir"' EXIT HUP INT TERM
git clone https://github.com/MatthewBisbee/eecs-348-lab-4.git "$demo_dir/repo"
cd "$demo_dir/repo"
hostname
gcc --version
make clean all
./task1
./task2
make test
make clean
exit
```

For `task1`, enter `25`, `-4`, `abc`, `0`, and `1`, one per prompt. Explain
the combinations, invalid-input recovery, zero score, and stop value.
For `task2`, enter `30`, `C`, and `F`, one per prompt. Run `./task2` again
to show invalid input or a boundary such as `35`, `C`, `C` (Extreme Heat).

For local practice on the Mac, use the existing checkout (a C compiler, Make,
and Python 3 for tests must be installed):

```sh
cd "/Users/matthewbisbee/Documents/EECS 348 Software Engineering/Labs/Lab 04"
make clean all
./task1
./task2
make test
make clean
```

Optional scripted examples, after `make all` on either machine:

```sh
make clean all
printf '25\n-4\n2\n1\n' | ./task1
printf '30\nC\nF\n' | ./task2
printf 'abc\n-1\nK\n0\nC\nK\n' | ./task2
make test
make clean
```

For the temperature example, the result is `86.00 F`, category `Hot`, and
advisory `Drink lots of water!`. Be prepared to explain input validation,
the scoring loops, conversion functions, category boundaries, and Makefile
targets during the live demo.

## AI usage

The required conversation log is in [ai_usage_log.md](ai_usage_log.md).
The instructor's original PDFs and logging instructions are kept locally and
excluded from the repository's current file tree.

## KU Cycle validation

Tested on `cycle1.eecs.ku.edu` on September 23, 2026 with GCC 11.4.0.
`make clean all test` passed all 10 test methods with no compiler warnings.
The score-25 and 30°C-to-Fahrenheit demos also passed. `make clean` removed
both executables, Git remained clean, and the temporary remote testing
directory was removed and its absence verified in a separate SSH check.
