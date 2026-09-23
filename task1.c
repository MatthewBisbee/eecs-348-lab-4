#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Each loop chooses one play count; the remaining points determine safeties. */
static void print_combinations(int score)
{
    printf("Possible combinations of scoring plays if a team's score is %d:\n", score);
    for (int td2 = 0; td2 <= score / 8; ++td2) {
        int after8 = score - td2 * 8;
        for (int td1 = 0; td1 <= after8 / 7; ++td1) {
            int after7 = after8 - td1 * 7;
            for (int td = 0; td <= after7 / 6; ++td) {
                int after6 = after7 - td * 6;
                for (int fg = 0; fg <= after6 / 3; ++fg) {
                    int remaining = after6 - fg * 3;
                    if (remaining % 2 == 0) {
                        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                               td2, td1, td, fg, remaining / 2);
                    }
                }
            }
        }
    }
}

int main(void)
{
    char line[256];
    for (;;) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        fflush(stdout);
        if (fgets(line, sizeof line, stdin) == NULL) {
            putchar('\n');
            return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        }
        /* Discard oversized input so its tail cannot become another score. */
        if (strchr(line, '\n') == NULL && !feof(stdin)) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            puts("Invalid score: input is too long.");
            continue;
        }
        char *end;
        errno = 0;
        long score = strtol(line, &end, 10);
        int has_number = end != line;
        while (isspace((unsigned char)*end)) {
            ++end;
        }
        if (!has_number || *end != '\0' || errno == ERANGE || score < 0 || score > INT_MAX) {
            printf("Invalid score: enter a whole number from 0 to %d.\n", INT_MAX);
            continue;
        }
        if (score == 1) {
            return EXIT_SUCCESS;
        }
        print_combinations((int)score);
    }
}
