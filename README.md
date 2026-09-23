# EECS 348 Lab 4 — C Programming

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

Suggested commands for the required live demo:

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
The instructor's original PDFs and logging instructions are retained here.
