#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Return 1 for a line, 0 at EOF, and -1 for an oversized line. */
static int read_line(const char *prompt, char *line, size_t size)
{
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(line, (int)size, stdin) == NULL) {
        putchar('\n');
        return 0;
    }
    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        puts("Invalid input: input is too long.");
        return -1;
    }
    return 1;
}

static int read_temperature(double *temperature)
{
    char line[256];
    for (;;) {
        int status = read_line("Enter the temperature value: ", line, sizeof line);
        if (status == 0) return 0;
        if (status < 0) continue;
        char *end;
        errno = 0;
        double value = strtod(line, &end);
        int has_number = end != line;
        while (isspace((unsigned char)*end)) ++end;
        if (!has_number || *end != '\0' || errno == ERANGE || !isfinite(value)) {
            puts("Invalid temperature: enter a finite number.");
            continue;
        }
        *temperature = value;
        return 1;
    }
}

static int read_scale(const char *prompt, char *scale)
{
    char line[256];
    for (;;) {
        int status = read_line(prompt, line, sizeof line);
        if (status == 0) return 0;
        if (status < 0) continue;
        char *p = line;
        while (isspace((unsigned char)*p)) ++p;
        int choice = toupper((unsigned char)*p);
        if (*p != '\0') ++p;
        while (isspace((unsigned char)*p)) ++p;
        if (*p != '\0' || (choice != 'C' && choice != 'F' && choice != 'K')) {
            puts("Invalid scale: enter C, F, or K.");
            continue;
        }
        *scale = (char)choice;
        return 1;
    }
}

static double to_celsius(double value, char scale)
{
    if (scale == 'F') return (value - 32.0) / 9.0 * 5.0;
    if (scale == 'K') return value - 273.15;
    return value;
}

static double from_celsius(double value, char scale)
{
    if (scale == 'F') return value / 5.0 * 9.0 + 32.0;
    if (scale == 'K') return value + 273.15;
    return value;
}

static void print_advisory(double celsius)
{
    const char *category;
    const char *advisory;
    if (celsius < 0.0) {
        category = "Freezing";
        advisory = "Bundle up and watch for ice!";
    } else if (celsius < 10.0) {
        category = "Cold";
        advisory = "Wear a jacket!";
    } else if (celsius < 25.0) {
        category = "Comfortable";
        advisory = "Enjoy the weather!";
    } else if (celsius < 35.0) {
        category = "Hot";
        advisory = "Drink lots of water!";
    } else {
        category = "Extreme Heat";
        advisory = "Stay indoors and stay hydrated!";
    }
    printf("Temperature category: %s\nWeather advisory: %s\n", category, advisory);
}

int main(void)
{
    double temperature;
    char original, target;
    for (;;) {
        if (!read_temperature(&temperature) ||
            !read_scale("Enter the original scale (C, F, or K): ", &original)) {
            return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        }
        double minimum = original == 'K' ? 0.0 : (original == 'C' ? -273.15 : -459.67);
        if (temperature < minimum) {
            puts("Invalid temperature: value is below absolute zero. Please try again.");
            continue;
        }
        break;
    }
    if (!read_scale("Enter the scale to convert to (C, F, or K): ", &target)) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }
    double celsius = to_celsius(temperature, original);
    double converted = original == target ? temperature : from_celsius(celsius, target);
    if (!isfinite(converted)) {
        fputs("Conversion error: result is outside the supported numeric range.\n", stderr);
        return EXIT_FAILURE;
    }
    /* Avoid displaying negative zero at absolute zero or after rounding. */
    if (fabs(converted) < 0.005) converted = 0.0;
    printf("Converted temperature: %.2f %c\n", converted, target);
    print_advisory(celsius);
    return EXIT_SUCCESS;
}
