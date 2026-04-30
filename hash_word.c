#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#define DEFAULT_MAX 10

typedef enum
{
    MODE_C1_V2 = 1,
    MODE_C2_V1 = 2,
    MODE_SCRABBLE = 3
} score_mode;

static int is_vowel(char c, int count_y_as_vowel)
{
    c = (char)tolower((unsigned char)c);

    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {
        return 1;
    }

    if (count_y_as_vowel && c == 'y')
    {
        return 1;
    }

    return 0;
}

static int scrabble_score(char c)
{
    c = (char)tolower((unsigned char)c);

    switch (c)
    {
        case 'a': case 'e': case 'i': case 'l': case 'n': case 'o': case 'r': case 's': case 't': case 'u': return 1;
        case 'd': case 'g': return 2;
        case 'b': case 'c': case 'm': case 'p': return 3;
        case 'f': case 'h': case 'v': case 'w': case 'y': return 4;
        case 'k': return 5;
        case 'j': case 'x': return 8;
        case 'q': case 'z': return 10;
        default: return 0;
    }
}

static int compute_score(char c, score_mode mode, int count_y_as_vowel)
{
    if (!isalpha((unsigned char)c))
    {
        return 0;
    }

    int vowel = is_vowel(c, count_y_as_vowel);

    if (mode == MODE_SCRABBLE)
    {
        return scrabble_score(c);
    }
    else if (mode == MODE_C1_V2)
    {
        return vowel ? 2 : 1;
    }
    else if (mode == MODE_C2_V1)
    {
        return vowel ? 1 : 2;
    }

    return 0;
}

static void print_coloured_char(HANDLE h, char c, int is_vowel_char, score_mode mode)
{
    WORD color;

    if (mode == MODE_SCRABBLE)
    {
        /* lime (bright green) */
        color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    }
    else
    {
        color = is_vowel_char ? FOREGROUND_BLUE | FOREGROUND_INTENSITY
                              : FOREGROUND_RED  | FOREGROUND_INTENSITY;
    }

    SetConsoleTextAttribute(h, color);
    putchar(c);

    /* reset to default  */
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main(void)
{
    char word[256];
    int mode_input;
    int max_value = DEFAULT_MAX;
    int count_y_as_vowel;

    printf("Enter word: ");
    if (scanf("%255s", word) != 1)
    {
        return 1;
    }

    printf("Choose mode:\n");
    printf("1) Consonants=1, Vowels=2\n");
    printf("2) Consonants=2, Vowels=1\n");
    printf("3) Scrabble scoring\n");
    printf("Selection: ");
    if (scanf("%d", &mode_input) != 1 || mode_input < 1 || mode_input > 3)
    {
        return 1;
    }

    printf("Enter maximum (default=10, enter 0 to use default): ");
    if (scanf("%d", &max_value) != 1)
    {
        return 1;
    }
    if (max_value <= 0)
    {
        max_value = DEFAULT_MAX;
    }

    printf("Count 'Y' as vowel? (1=yes, 0=no): ");
    if (scanf("%d", &count_y_as_vowel) != 1)
    {
        return 1;
    }

    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

    int total = 0;

    printf("\nOUTPUT: ");

    /* print coloured word */
    for (size_t i = 0; i < strlen(word); i++)
    {
        char c = word[i];

        if (isalpha((unsigned char)c))
        {
            print_coloured_char(h_console, c, is_vowel(c, count_y_as_vowel), (score_mode)mode_input);
        }
        else
        {
            putchar(c);
        }
    }

    printf(" (");

    /* compute and display breakdown */
    for (size_t i = 0; i < strlen(word); i++)
    {
        int s = compute_score(word[i], (score_mode)mode_input, count_y_as_vowel);

        if (i > 0)
        {
            printf("+");
        }

        printf("%d", s);
        total += s;
    }

    int result = total % max_value;

    printf(" = %d %% %d = %d)\n", total, max_value, result);

    return 0;
}