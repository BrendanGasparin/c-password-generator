#include <stdbool.h>
#include <stdio.h>

typedef struct Input {
    int n;
    Input* next;
} Input;

int* get_input(char *prompt);

int main(void) {
    bool valid = true;
    do {
        struct Input *chars = get_int("Enter integer for password length. (Minimum 8): ");
        struct Input *temp = chars;
        int char_count = 0;

        if (chars->next == NULL)
            valid = false;
        else {
            // Get character count
            while(temp->next != NULL) {
                char_count++;
                temp = temp->next;
            }
            char_count++;

            // Assign to an array
            int input[char_count];
            for (int i = 0; i < char_count; i++) {
                input[i] = chars->n;
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
        }

    } while (valid == false);
}

int* get_input(char *prompt) {
    struct Input* input = (struct Input*)malloc(sizeof(struct Input));
    struct Input* temp = input;
    int c;
    printf("%s", prompt);

    // Create a linked list of user input in order of characters typed
    while ((c = getchar()) != EOF && c != '\n') {
        if (input == NULL) {
            input->n = c;
            input->next = NULL;
        }
        else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            input->n = c;
            input->next = NULL;
            temp->next = input;
        }
    }

    return input;
}