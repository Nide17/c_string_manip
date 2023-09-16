/*
 * c_string_manip.c
 *
 * An implementation of five functions that manipulates C strings for ISSE assignment #3:
 *
 * 1. bool is_prefix(const char *prefix, const char *str)
 * 2. void reverse_in_place(char *str)
 * 3. void reverse_by_word(char *str)
 * 4. int remove_last_substr(char *str, const char *substr)
 * 5. void strip_chars(char *str, const char *remove_chars)
 *
 * Author: Niyomwungeri Parmenide ISHIMWE <parmenin@andrew.cmu.edu>
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/*
 * Determine if one string is a prefix of another string.
 *
 * Parameters:
 * prefix:  A null-terminated string to represent string's prefix.
 * str:     Actual string, that is a null-terminated string.
 *
 * Returns:
 * true if str begins with prefix, and false otherwise.
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
        if (*prefix != *str)
        {
            return false;
        }

        // ELSE MOVE POINTERS
        prefix++;
        str++;
    }

    // CHECK IF STR FINISH BEFORE PREFIX - PREF LONGER THAN STR
    if (*str == '\0' && *prefix != '\0')
        return false;

    // IF PREFIX FINISHED BEFORE STRING
    return true;
}

/*
 * Tests the is_prefix function, for one test case
 *
 * Parameters:
 *   prefix     The prefix of the string
 *   str        The actual string
 *   expected   The expected bool result of the function
 *
 * Returns:
 *   true if the test passes, false otherwise
 */
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

/*
 * Performs unit tests of the is_prefix function by running test_is_prefix_once on each test case.
 *
 * Returns:
 *   true if all tests succeed, false otherwise.
 */
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

/*
 * Reverses a null-terminated string in place, converting it to all lower case in the process
 *
 * Parameters:
 *   str   A null terminated string to be reversed.
 *
 * Returns:
 *   None
 */
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
        // SWAPPING CHARACTERS UNTIL THE MIDDLE
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

/*
 * Tests the reverse_in_place function, for one test case
 *
 * Parameters:
 *   str        The string to pass to reverse_in_place function to be reversed.
 *   expected   The expected char type result of the reverse_in_place function.
 *
 * Returns:
 *   true if the test passes, false otherwise.
 */
bool test_reverse_in_place_once(char *str, char *expected)
{
    char temp[256];

    strcpy(temp, str);      // COPYING str TO THE temp
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

/*
 * Performs unit tests of the reverse_in_place function by running test_reverse_in_place_once on each test case.
 *
 * Returns:
 *   true if all tests succeed, false otherwise.
 */
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

/*
 * An implementation of the reverse_by_word function
 *
 * Individually reverses each word of a null-terminated string in place.
 * Whitespace characters (as identified by the C isspace() function) are passed through unchanged.
 *
 * Parameters:
 *   str   A null terminated string to be reversed word by word.
 *
 * Returns:
 *   None
 */
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

        // REVERSING THE WORD IN PLACE
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

/*
 * Tests the reverse_by_word function, for one test case
 *
 * Parameters:
 *   str        The string to pass to reverse_by_word function to be reversed.
 *   expected   The expected char type result of the reverse_by_word function.
 *
 * Returns:
 *   true if the test passes, false otherwise.
 */
bool test_reverse_by_word_once(char *str, char *expected)
{
    char temp[512];

    strcpy(temp, str);

    reverse_by_word(temp);

    if (strcmp(temp, expected) != 0)
    {
        printf("\nTest error: Reversing '%s', Result: '%s', Expected: '%s'\n", str, temp, expected);
        return false;
    }
    else
        return true;
}

/*
 * Performs unit tests of the reverse_by_word function by running test_reverse_by_word_once on each test case.
 *
 * Returns:
 *   true if all tests succeed, false otherwise.
 */
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

/*
 * Removes the last occurrence of substr from str, modifying the result in place.
 *
 * Parameters:
 *   str        A null terminated string for which a sub-string will be removed.
 *   substr     A null terminated string to remove from the string.
 *
 * Returns:
 *    int that represnts the position where the sub-string was removed.
 */
int remove_last_substr(char *str, const char *substr)
{
    char *first_str_char = str;          // KEEPING THE FIRST CHAR OF STR ADRESS
    const char *first_sub_char = substr; // KEEPING THE FIRST CHAR OF SUBSTR ADRESS

    int position = -1; // POSITION OF THE LAST CHAR OF SUBSTR IN STR
    int sub_len = 0;   // LENGTH OF SUBSTR

    // MOVING THE POINTER TO THE LAST CHAR OF STR
    while (*str != '\0')
        str++;

    // POINTING IT BACK TO THE LAST CHAR FROM '\0'
    str--;

    position = str - first_str_char; // POSITION OF THE LAST CHAR OF STR IN STR

    // MOVING THE POINTER TO THE LAST CHAR OF SUB AND GETTING THE LENGTH OF SUBSTR
    while (*substr != '\0')
    {
        substr++;
        sub_len++;
    }

    // POINTING IT BACK TO THE LAST CHAR FROM '\0'
    substr--;

    // IF SUB IS EMPTY STRING
    if (*substr == '\0')
        return position;

    // IF STR IS EMPTY STRING
    if (*str == '\0')
        return -1;

    // FIND THE LAST SUB STR CHAR'S POSITION IN ORIGINAL STR
    while (*str != *substr)
    {
        str--;
        position--;

        // IF LAST CHAR NOT FOUND
        if (position == -1)
            return -1;
    }

    // MOVE POINTERS BACKWARD FOR BOTH STR AND SUB, CHECKING IF CHARS ARE EQUAL, UNTIL SUB IS FINISHED
    while (position > -1)
    {
        // IF CURRENT CHAR ARE DIFFERENT, POINT BACK TO THE END OF SUB AND START FROM THERE WHERE STR IS
        if (*substr != *str)
        {

            if (str == first_str_char)
            {
                position = -1;
                break;
            }
            else
            {
                str--; // POINTING STR TO THE PREVIOUS CHAR

                // POINT BACK TO THE END OF SUB
                while (*substr != '\0')
                    substr++;

                // POINTING IT BACK TO THE LAST CHAR FROM '\0'
                substr--;
            }
        }

        else
        {
            // IF SUBSTR IS FINISHED
            if (substr == first_sub_char)
            {
                position = str - first_str_char;
                break;
            }
            else
            {
                // MOVE POINTERS BACKWARD
                substr--;
                str--;
            }
        }
    }

    // REMOVING THE SUB STR FROM THE STR
    if (position != -1)
    {
        // START FROM CURRENT POSITION, PUTTING REMAINING LETTERS APART FROM SUBSTR
        while (*str != '\0')
        {
            *str = *(str + sub_len);
            str++;
        }

        *str = '\0'; // TERMINATING THE NEW STRING
    }

    return position;
}

/*
 * Tests the remove_last_substr function, for one test case
 *
 * Parameters:
 *   str                The string to pass to remove_last_substr function to be reversed.
 *   sub_str            The sub-string to remove from the string.
 *   expected_str       The expected string result after removing the sub-string.
 *   expected_position  The expected position where the sub-string was removed.
 *
 * Returns:
 *   true if the test passes, false otherwise.
 */
bool test_remove_last_substr_once(char *str, const char *sub_str, char *expected_str, int expected_position)
{
    char temp[512];
    strcpy(temp, str);

    int position = remove_last_substr(temp, sub_str);

    if (strcmp(temp, expected_str) != 0 || position != expected_position)
    {
        printf("\nTest error: removing '%s', from '%s', gives '%s', expected '%s' to be removed at position '%d' instead removed at '%d\n",
               sub_str, str, temp, expected_str, expected_position, position);
        return false;
    }
    else
        return true;
}

/*
 * Performs unit tests of the remove_last_substr function by running test_remove_last_substr_once on each test case.
 *
 * Returns:
 *   true if all tests succeed, false otherwise.
 */
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

/*
 * Removes all occurrences of any of the characters in remove_chars from str, modifying the result in place.
 *
 * Parameters:
 *   str            A null terminated string for which characters will be removed.
 *   remove_chars   A null terminated string containing characters to remove from str.
 *
 * Returns:
 *   None
 */
void strip_chars(char *str, const char *remove_chars)
{
    // POINTING TO THE FIRST CHAR OF STR
    char *str_ptr = str;

    while (*remove_chars != '\0')
    {
        while (*str_ptr != '\0')
        {
            if (*str_ptr == *remove_chars)
            {
                // REMOVE CHAR AND SHIFT THE REST
                while (*str_ptr != '\0')
                {
                    *str_ptr = *(str_ptr + 1);
                    str_ptr++;
                }

                str_ptr = str; // POINTING BACK TO FRONT
            }

            else
                str_ptr++;
        }

        // POINTING BACK TO FRONT
        str_ptr = str;

        // POINTING TO THE NEXT CHAR OF SUBSTR
        remove_chars++;
    }
}

/*
 * Tests the strip_chars function, for one test case
 *
 * Parameters:
 *   str            The string to pass to strip_chars function from which characters will be removed.
 *   chars          The characters to remove from the string.
 *   expected       The expected string result after removing the characters.
 *
 * Returns:
 *   true if the test passes, false otherwise.
 */
bool test_strip_chars_once(char *str, char *chars, char *expected)
{
    char temp[256];

    strcpy(temp, str);        // SAVING str TO temp
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

/*
 * Performs unit tests of the strip_chars function by running test_strip_chars_once on each test case.
 *
 * Returns:
 *   true if all tests succeed, false otherwise.
 */
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