#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/*
 * c_string_manip.c
 *
 * An implementation of five functions that manipulates C strings for ISSE assignment #3:
 *
 * 1. bool is_prefix(const char *prefix, const char *str)
 * 2. void reverse_in_place(char *str)
 * 3. bool is_prefix(const char *prefix, const char *str)
 * 4. int remove_last_substr(char *str, const char *substr)
 * 5. int first_word(const char *input, char *word, int word_len)
 *
 * Author: Niyomwungeri Parmenide ISHIMWE <parmenin@andrew.cmu.edu>
 */

bool is_prefix(const char *prefix, const char *str)
{
    // IF THE PREFIX IS END OF STRING, RETURN TRUE
    if (*prefix == '\0')
        return true;

    // MOVE BOTH POINTERS WHILE COMPARING THE VALUES
    while (*str != '\0' && *prefix != '\0')
    {
        // WHEN THE CHARACTERS DO NOT MATCH, RETURN false
        if (*prefix != *str) {
            return false;
        }

        // ELSE MOVE POINTERS
        prefix++;
        str++;
    }

    // CHECK IF STR FINISH BEFORE PREFIX - PREF LONGER THAN STR
    if(*str == '\0' && *prefix != '\0')
        return false;

    // IF PREFIX FINISHED BEFORE STRING
    return true;
}

bool test_is_prefix_once(const char *prefix, const char *str, bool expected)
{
    if (is_prefix(prefix, str) != expected)
    {
        printf("\nTest error: Checking the prefix '%s' in '%s', Result: '%d', Expected: '%d'\n", prefix, str, is_prefix(prefix, str), expected);
        return false;
    }
    else
        return true;
}

bool test_is_prefix()
{
    bool result = true;

    if (!test_is_prefix_once("C", "Carnegie Mellon", true))
        result = false;

    if (!test_is_prefix_once("Carnegie", "Carnegie Mellon", true))
        result = false;

    if (!test_is_prefix_once("Carnegie Mellon", "Carnegie Mellon", true))
        result = false;

    if (!test_is_prefix_once("Carnegie Mellon University", "Carnegie Mellon", false))
        result = false;

    if (!test_is_prefix_once("Cab", "Carnegie Mellon", false))
        result = false;

    if (!test_is_prefix_once("car", "Carnegie Mellon", false))
        result = false;

    if (!test_is_prefix_once("0", "0Carnegie", true))
        result = false;

    if (!test_is_prefix_once("", "Carnegie", true))
        result = false;

    if (!test_is_prefix_once(" ", "Carnegie", false))
        result = false;

    if (!test_is_prefix_once("", " Carnegie", true))
        result = false;

    return result;
}

void reverse_in_place(char *str)
{
    // POINTER THAT POINTS TO THE FIRST CHAR
    char *ptr_start = str;
    char *ptr_end = str;

    // MOVING THE END POINTER TO THE LAST CHAR
    while (*ptr_end != '\0')
        ptr_end++;

    // POINTING IT BACK TO THE LAST CHAR FROM '\0'
    ptr_end--;

    // USING TEMP, SWAP CHARS FROM EXTREMITIES
    while (ptr_end > ptr_start)
    {
        // SWAPPING CHARS
        char temp = *ptr_start;
        *ptr_start = *ptr_end;
        *ptr_end = temp;

        // MOVING THE POINTERS TOWARDS THE MIDDLE
        ptr_start++;
        ptr_end--;
    }

    // CONVERTING TO LOWERCASE
    ptr_start = str; // POINTING IT BACK TO THE FIRST CHAR
    while (*ptr_start != '\0')
    {
        *ptr_start = (char)tolower(*ptr_start);
        ptr_start++; // MOVING THE POINTER TO THE NEXT CHAR
    }
}

bool test_reverse_in_place_once(char *str, char *expected)
{
    char temp[256];

    strcpy(temp, str);      // SAVING str TO temp
    reverse_in_place(temp); // REVERSING temp IN PLACE

    // CHECKING IF THE REVERSE IS CORRECT
    if (strcmp(temp, expected) != 0)
    {
        printf("Test error: Reversing '%s', Result: '%s', Expected: '%s'\n", str, temp, expected);
        return false;
    }

    else
        return true;
}

bool test_reverse_in_place()
{
    bool result = true;

    if (!test_reverse_in_place_once("Carnegie Mellon", "nollem eigenrac"))
        result = false;

    if (!test_reverse_in_place_once("Four", "ruof"))
        result = false;

    if (!test_reverse_in_place_once("One", "eno"))
        result = false;

    if (!test_reverse_in_place_once(" ", " "))
        result = false;

    if (!test_reverse_in_place_once("", ""))
        result = false;

    if (!test_reverse_in_place_once("15", "51"))
        result = false;

    if (!test_reverse_in_place_once("15 fifteen quinze", "ezniuq neetfif 51"))
        result = false;

    return result;
}

void reverse_by_word(char *str)
{
    // POINTER THAT POINTS TO THE FIRST CHAR
    char *start = str;
    char *end = str;

    while (*end != '\0')
    {
        // SKIPPING THE LEADING WHITE SPACES TO PUT THE STARTING POINTER TO THE FIRST CHARACTER
        while (isspace(*start))
            start++;

        end = start; // STARTING AT FIRST CHAR

        // MOVING THE POINTER TO THE LAST LETTER OF THE WORD
        while (*end != '\0' && !isspace(*end))
            end++;

        // REVERSING THE WORD
        char *word_start = start;
        char *word_end = end - 1;

        while (word_start < word_end)
        {
            char temp = *word_start;
            *word_start = *word_end;
            *word_end = temp;
            word_start++;
            word_end--;
        }

        // GOING TO THE NEXT WORD
        start = end;
    }
}

bool test_reverse_by_word_once(char *input, char *expected)
{
    char temp[512];

    strcpy(temp, input);

    reverse_by_word(temp);

    if (strcmp(temp, expected) != 0)
    {
        printf("\nTest error: Reversing '%s', Result: '%s', Expected: '%s'\n", input, temp, expected);
        return false;
    }
    else
        return true;
}

bool test_reverse_by_word()
{
    bool success = true;

    if (!test_reverse_by_word_once("Carnegie Mellon", "eigenraC nolleM"))
        success = false;

    if (!test_reverse_by_word_once("    Carnegie  Mellon", "    eigenraC  nolleM"))
        success = false;

    if (!test_reverse_by_word_once("My heart is in  the work", "yM traeh si ni  eht krow"))
        success = false;

    if (!test_reverse_by_word_once("Four", "ruoF"))
        success = false;

    if (!test_reverse_by_word_once(" One", " enO"))
        success = false;

    return success;
}

int remove_last_substr(char *str, const char *substr)
{
    char *str_ptr = str;          // POINTING TO THE FIRST CHAR OF STR
    const char *sub_ptr = substr; // POINTING TO THE FIRST CHAR OF SUBSTR

    char *char_one_str = str;          // KEEPING THE FIRST CHAR OF STR ADRESS
    const char *char_one_sub = substr; // KEEPING THE FIRST CHAR OF SUBSTR ADRESS
    int position = -1;                 // POSITION OF THE LAST CHAR OF SUBSTR IN STR
    int sub_len = 0;                   // LENGTH OF SUBSTR

    // MOVING THE POINTER TO THE LAST CHAR OF STR
    while (*str_ptr != '\0')
        str_ptr++;

    // POINTING IT BACK TO THE LAST CHAR FROM '\0'
    str_ptr--;

    position = str_ptr - char_one_str; // POSITION OF THE LAST CHAR OF STR IN STR

    // MOVING THE POINTER TO THE LAST CHAR OF SUB AND GETTING THE LENGTH OF SUBSTR
    while (*sub_ptr != '\0')
    {
        sub_ptr++;
        sub_len++;
    }

    // POINTING IT BACK TO THE LAST CHAR FROM '\0'
    sub_ptr--;

    // IF SUB IS EMPTY STRING
    if(*sub_ptr == '\0')
        return position;

    // IF STR IS EMPTY STRING
    if(*str_ptr == '\0')
        return -1;

    // FIND THE LAST SUB STR CHAR'S POSITION IN ORIGINAL STR
    while (*str_ptr != *sub_ptr)
    {
        str_ptr--;
        position--;

        // IF LAST CHAR NOT FOUND
        if (position == -1)
            return -1;
    }

    // MOVE POINTERS BACKWARD FOR BOTH STR AND SUB, CHECKING IF CHARS ARE EQUAL, UNTIL SUB IS FINISHED
    while (position > -1)
    {
        // IF CURRENT CHAR ARE DIFFERENT, POINT BACK TO THE END OF SUB AND START FROM THERE WHERE STR IS
        if (*sub_ptr != *str_ptr)
        {

            if (str_ptr == char_one_str)
            {
                position = -1;
                break;
            }
            else
            {
                str_ptr--; // POINTING STR TO THE PREVIOUS CHAR

                // POINT BACK TO THE END OF SUB
                while (*sub_ptr != '\0')
                    sub_ptr++;

                // POINTING IT BACK TO THE LAST CHAR FROM '\0'
                sub_ptr--;
            }
            
        }

        else
        {
            // IF SUBSTR IS FINISHED
            if (sub_ptr == char_one_sub) {
                position = str_ptr - char_one_str;
                break;
            }
            else
            {
                // MOVE POINTERS BACKWARD
                sub_ptr--;
                str_ptr--;
            }
        }
    }

    // REMOVING THE SUB STR FROM THE STR
    if (position != -1)
    {
        // START FROM CURRENT POSITION, PUTTING REMAINING LETTERS APART FROM SUBSTR
        while (*str_ptr != '\0')
        {
            *str_ptr = *(str_ptr + sub_len);
            str_ptr++;
        }

        *str_ptr = '\0'; // TERMINATING THE STRING
    }

    return position;
}

bool test_remove_last_substr_once(char *str, const char *substr, char *expecStr, int expecPos)
{
    char buffer[512];
    strcpy(buffer, str);

    int position = remove_last_substr(buffer, substr);

    if (strcmp(buffer, expecStr) != 0 || position != expecPos)
    {
        printf("\nTest error: removing '%s', from '%s', gives '%s', expected '%s' to be removed at position '%d' instead removed at '%d\n",
               substr, str, buffer, expecStr, expecPos, position);
        return false;
    }
    else
        return true;
}

bool test_remove_last_substr()
{
    bool success = true;
    if (!test_remove_last_substr_once("Carnegie_Mellon", "Carnegie", "_Mellon", 0))
        success = false;

    if (!test_remove_last_substr_once("Carnegie Mellon", "Carnegie", " Mellon", 0))
        success = false;

    if (!test_remove_last_substr_once("one two one three", "hr", "one two one tee", 13))
        success = false;

    if (!test_remove_last_substr_once("Bananas", "a", "Banans", 5))
        success = false;

    if (!test_remove_last_substr_once("Bananas", "nan", "Baas", 2))
        success = false;

    if (!test_remove_last_substr_once("one two one three", "one ", "one two three", 8))
        success = false;

    if (!test_remove_last_substr_once("Carnegie Mellon", "Kiltie", "Carnegie Mellon", -1))
        success = false;

    if (!test_remove_last_substr_once("Carnegie Mellon", "Carnegie Mellon University", "Carnegie Mellon", -1))
        success = false;

    if (!test_remove_last_substr_once("Carnegie Mellon", "", "Carnegie Mellon", 14))
        success = false;

    if (!test_remove_last_substr_once("", "Carnegie", "", -1))
        success = false;

    return success;
}

void strip_chars(char *str, const char *remove_chars)
{
    char *str_ptr = str;               // POINTING TO THE FIRST CHAR OF STR
    const char *rm_ptr = remove_chars; // POINTING TO THE FIRST CHAR OF SUBSTR

    while (*rm_ptr != '\0')
    {
        // printf("at %c\n", *rm_ptr);
        while (*str_ptr != '\0')
        {
            if (*str_ptr == *rm_ptr)
            {
                // printf("%c => %c\n", *str_ptr, *rm_ptr);

                // REMOVE CHAR AND SHIFT THE REST
                while (*str_ptr != '\0')
                {
                    *str_ptr = *(str_ptr + 1);
                    str_ptr++;
                }

                str_ptr = str; // POINTING BACK TO FRONT

                // printf("After removing: %s\n", str);
            }
            else
            {
                str_ptr++;
            }
        }

        str_ptr = str; // POINTING BACK TO FRONT
        rm_ptr++;
    }

    // printf("Final: %s\n", str);
}

bool test_strip_chars_once(char *str, char *chars, char *expected)
{
    char temp[256];

    strcpy(temp, str);      // SAVING str TO temp
    strip_chars(temp, chars); // STRIPING temp IN PLACE

    // CHECKING IF THE STRIPING IS CORRECT
    if (strcmp(temp, expected) != 0)
    {
        printf("Test error: Striping characters in '%s', Result: '%s', Expected: '%s'\n", str, temp, expected);
        return false;
    }

    else
        return true;
}

bool test_strip_chars()
{
    bool result = true;

    if (!test_strip_chars_once("Carnegie Mellon", "l ", "CarnegieMeon"))
        result = false;

    if (!test_strip_chars_once("Carnegie Mellon", "el ", "CarngiMon"))
        result = false;

    if (!test_strip_chars_once("Carnegie Mellon", "", "Carnegie Mellon"))
        result = false;

    if (!test_strip_chars_once("one two three", "thre", "on wo "))
        result = false;

    if (!test_strip_chars_once("Bananas", "a", "Bnns"))
        result = false;

    if (!test_strip_chars_once("Bananas", "Bnas", ""))
        result = false;

    if (!test_strip_chars_once("", "", ""))
        result = false;

    if (!test_strip_chars_once(" ", "", " "))
        result = false;

    if (!test_strip_chars_once("", " ", ""))
        result = false;

    if (!test_strip_chars_once("15 fifteen quinze", "51", " fifteen quinze"))
        result = false;

    return result;
}

int main()
{
    if (test_is_prefix())
        printf("All is_prefix test cases have passed!\n");
    else
        printf("Sorry, some is_prefix tests failed!\n");

    if (test_reverse_in_place())
        printf("All reverse_in_place test cases have passed!\n");
    else
        printf("Sorry, some reverse_in_place tests failed!\n");

    if (test_reverse_by_word())
        printf("All reverse_by_word test cases have passed!\n");
    else
        printf("Sorry, some reverse_by_word tests failed!\n");

    if (test_remove_last_substr())
        printf("All remove_last_substr test cases have passed\n");
    else
        printf("Sorry, some remove_last_substr tests failed\n\n");

    if (test_strip_chars())
        printf("All strip_chars test cases have passed!\n");
    else
        printf("Sorry, some strip_chars tests failed!\n");
}