#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct input {
    int n;
    struct input *next;
} input;

struct input* get_input(char *prompt);

int main(void) {
    // TODO: Prevent integer overflow
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

    printf("You entered %d.\n", final_int);
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