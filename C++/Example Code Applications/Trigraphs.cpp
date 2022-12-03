/*
 * Trigraphs (removed in C++17)
 *
 * The following three-character groups (trigraphs) are parsed
 * before comments and string literals are recognized, and each appearance
 * of a trigraph is replaced by the corresponding primary character:
 *   
 *   ------------------
 *   |Primary|Trigraph|
 *   |   { 	 |   ??<  |
 *   |   } 	 |   ??>  |
 *   |   [ 	 |   ??(  |
 *   |   ] 	 |   ??)  |
 *   |   # 	 |   ??=  |
 *   |   \ 	 |   ??/  |
 *   |   ^ 	 |   ??'  |
 *   |   | 	 |   ??!  |
 *   |   ~ 	 |   ??-  |
 *   ------------------
 *
 * Because trigraphs are processed early, a comment such as // Will the next line
 * be executed?????/ will effectively comment out the following line,
 * and the string literal such as "Enter date ??/??/??" is parsed as "Enter date \\??".
 */

#include <iostream>

int main()
{
    int ival = 0; // ??/
    ival = 1;
    std::cout << ival;
}