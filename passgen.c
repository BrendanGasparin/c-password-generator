#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct input {
    int n;
    struct input *next;
} input;

struct input* get_input(char *prompt);
int get_int(char *prompt);
bool is_password_secure(char pass[], int length);
void print_banner();
void print_password(char password[], int length);

int main(void) {
    print_banner();

    int num_chars = get_int("Enter integer for password length. (Minimum 8): ");
    char password[num_chars];
    bool valid = false;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate passwords until a valid strong one is generated
    while (!valid) {
        for (int i = 0; i < num_chars; i++) {
            // Uppercase characters, lowercase characters, digits, and special characters
            // should each have an equal chance of being used
            int char_type = (rand() % 4);

            // Uppercase characters
            if (char_type == 0)
                password[i] = (char)((rand() % 26) + 65);
            // Lowercase characters
            else if (char_type == 1)
                password[i] = (char)((rand() % 26) + 97);
            // Numbers
            else if (char_type == 2)
                password[i] = (char)((rand() % 10) + 48);
            // Special characters
            else if (char_type == 3) {
                // Special ASCII characters are scattered around the ASCII chart
                // Each should have equal chance of being used
                int random = rand() % 32;
                if (random <= 14)
                    password[i] = (char)(random + 33);
                else if (random <= 21)
                    password[i] = (char)(random + 58);
                else if (random <= 27)
                    password[i] = (char)(random + 91);
                else
                    password[i] = (char)(random + 123);
            }
        }

        // Verify the password uses uppercase, lowercase, numeric, and special characters
        if (is_password_secure(password, num_chars))
            valid = true;
    }

    print_password(password, num_chars);

    return 0;
}

struct input* get_input(char *prompt) {
    int c;
    printf("%s", prompt);

    struct input *input = NULL;

    // Create a linked list of user input in order of characters typed
    while ((c = getchar()) != EOF && c != '\n') {
        struct input *temp = (struct input*)malloc(sizeof(struct input));
        if (!temp) {
            exit(EXIT_FAILURE);
        }

        temp->n = c;
        temp->next = input;
        input = temp;
    }

    return input;
}

int get_int(char *prompt) {
    bool valid;
    int final_int;
    do {
        struct input *chars = get_input("Enter integer for password length. (Minimum 8): ");
        struct input *temp = chars;
        int char_count = 0;
        final_int = 0;
        valid = true;

        if (chars == NULL) {
            printf("Chars is NULL.\n");
            valid = false;
        }
        else {
            while (temp != NULL) {
                // Get character count
                char_count++;
                //if (temp->next != NULL)
                temp = temp->next;
            }

            // Assign to an array
            int input[char_count];
            temp = chars;
            for (int i = char_count - 1; i >= 0; i--) {
                input[i] = temp->n - 48;
                if (temp->next != NULL)
                    temp = temp->next;
            }

            // Free input linked list
            while (chars != NULL) {
                temp = chars;
                chars = chars->next;
                free(temp);
            }

            // Check all characters are ints
            for (int i = 0; i < char_count; i++) {
                if (input[i] < 0 || input[i] > 9) {
                    valid = false;
                }
            }

            // convert the array of single-digit ints into one multi-digit int
            for (int i = 0; i < char_count; i++) {
                final_int += input[char_count - i - 1] * (int)pow(10.0, (double)i);
            }

            // Input must be >= 8
            if (final_int < 8)
                valid = false;
        }

    } while (valid == false);

    return final_int;
}

bool is_password_secure(char pass[], int length) {
    int uppercase_count = 0;
    int lowercase_count = 0;
    int numeric_count = 0;
    int special_count = 0;
    for (int i = 0; i < length; i++) {
        if (pass[i] >= 65 && pass[i] <= 90)
            uppercase_count++;
        if (pass[i] >= 97 & pass[i] <= 122)
            lowercase_count++;
        if (pass[i] >= 48 && pass[i] <= 57)
            numeric_count++;
        else
            special_count++;
    }
    if (uppercase_count > 0 && lowercase_count > 0 && numeric_count > 0 && special_count > 0)
        return true;
    return false;
}

void print_banner() {
    printf("*************************\n");
    printf("STRONG PASSWORD GENERATOR\n");
    printf("*************************\n\n");
}

void print_password(char pass[], int length) {
    printf("PASSWORD: ");
    for (int i = 0; i < length; i++)
        printf("%c", pass[i]);
    printf("\n\n");
}