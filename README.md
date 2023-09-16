## c_string_manip

__INTRODUCTION__

This repo contains five functions that manipulates C strings along with their tests.

__DESCRIPTION__

 A code implementation of five functions for ISSE Assignment 3:

1. bool is_prefix(const char *prefix, const char*str)
2. void reverse_in_place(char *str)
3. void reverse_by_word(char *str)
4. int remove_last_substr(char *str, const char*substr)
5. void strip_chars(char *str, const char*remove_chars)

__bool is_prefix(const char *prefix, const char *str)__

A code implementation of the is_prefix function  

* Returns true if str begins with prefix, and false otherwise.
* Both prefix and str are null-terminated strings.
* Empty string "" is also a valid prefix for all strings.

Examples:  
| prefix            | str               | Returns |
|-------------------|-------------------|---------|
| C               | Carnegie Mellon | true    |
| Carnegie        | Carnegie Mellon | true    |
| Carnegie Mellon | Carnegie Mellon | true    |
| Cab             | Carnegie Mellon | false   |
| car             | Carnegie Mellon | false (because of case sensitivity)   |

Parameters:  
   str :                     A null terminated string to examine  
   prefix :                  A null terminated string to check in front of str  

Returns:  
    true if str begins with prefix, and false otherwise.  

__void reverse_in_place(char *str)__

A code implementation of the reverse_in_place function.

* Reverses a null-terminated string in place, converting it to all lower case in the process.

Examples:  
| Input             | Output            |
|-------------------|-------------------|
| Carnegie Mellon | nollem eigenrac |
| Four            | ruof            |
|  One            | eno             |

Parameters:  
  str :                A null terminated string to reverse  

Returns:  
  None  

__void reverse_by_word(char *str)__

A code implementation of the reverse_by_word function

* Individually reverses each word of a null-terminated string in place.
* Whitespace characters (as identified by the C isspace() function) are passed through unchanged.

Examples:  
| Input                      | Output                     |
|----------------------------|----------------------------|
| Carnegie Mellon          | eigenraC nolleM          |
| \tCarnegie  Mellon       | \teigenraC  nolleM       |
| Four                     | ruoF                     |
|  One                     |  enO                     |
| My heart is in  the work | yM traeh si ni  eht krow |

Parameters:  
  str :       A null terminated string to reverse  

Returns:  
  None  

__int remove_last_substr(char *str, const char *substr)__

A code implementation of the remove_last_substr function  

* Removes the last occurrence of substr from str, modifying the result in place.
* Returns the character position where the removal occurred, or -1 if substr was not found in str.
* Note that substr need not be a full word.

Examples:  

| str                   | substr     | Result            | Returns |
|-----------------------|------------|-------------------|---------|
| Carnegie Mellon   | Carnegie | Mellon          | 0       |
| Carnegie Mellon   | Kiltie   | Carnegie Mellon | -1      |
| Carnegie Mellon   |          | Carnegie Mellon | 14      |
| one two one three | one      | one two three   | 8       |
| one two one three | hr       | one two one tee | 13      |

Parameters:  
   str                   A null terminated string to examine  
   substr                A null terminated string to remove  

Returns:  
    Integer, which indicates the position where the substring was removed.

__void strip_chars(char *str, const char *remove_chars)__

A code implementation of the strip_chars function  

* Removes all occurrences of any of the characters in remove_chars from str.
* Modifies the result in place.

Examples:  

| input                  | Result (in word) | Returns |
|------------------------|------------------|---------|
|  Carnegie␣Mellon             | l␣            | CarnegieMeon       |
|  Carnegie␣Mellon             | el␣            | CarngiMon       |
|  Carnegie␣Mellon             | “”             | Carnegie␣Mellon       |
|  one␣two␣three             | thre             | on␣wo␣       |
|  Bananas             | a             | Bnns       |
|  Bananas             | Bnas             | ""       |

Parameters:  
    str                   A null terminated string to strip from
    remove_chars          A null terminated string of characters to strip from str

Returns:  
    None

__IMPORTANCE__

These functions may be very important in C programming language because they can be used in many circumstances. For example, the is_prefix function can be used to check if a string is a prefix of another string that may be useful for searching processes. The reverse_in_place function can be used to reverse a string in place. The reverse_by_word function can be used to reverse each word of a string in place. The remove_last_substr function can be used to remove the last occurrence of a substring from a string. The strip_chars function can also be used to remove all occurrences of any of the specified characters from a string.

__GETTING STARTED__

* Clone this repository to get the c_string_manip.c program.
* In the terminal, navigate inside the program's directory.
* Compile the program by running the command: gcc -Wall -Werror  c_string_manip.c -o c_string_manip
* Run the program using the command: ./c_string_manip
  
__TESTING__

This program is implemented and tested with the functions that have names starting with test string.
  
 __KEYWORDS__

<mark>ISSE</mark>     <mark>CMU</mark>     <mark>Assignment3</mark>     <mark>c_string_manip</mark>     <mark>C Programming</mark>     <mark>Strings</mark>

  __AUTHOR__

 Written by parmenin (Niyomwungeri Parmenide ISHIMWE) at CMU-Africa - MSIT

 __DATE__

 September 16, 2023
