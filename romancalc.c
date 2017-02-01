/*
 * romancalc: A Roman numeral calculator for Addition and Substraction.
 * Copyright (C) 2017 Amol Sawant
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdlib.h>
#include <string.h>
#include "romancalc.h"

/* File-scope global variables */
static int gr0 = 0;            // temp variable to hold reduction operation.
static int grule_3eq = 1;      // check for 3 identical characters.
static int grule_rdu = 0;      // check for 'IVI' = V redundancy.
static char romanval[50] = {0};// char buffer for output.
    
/**
*   @brief: Key-value map.
*   @description: This function creates a map between roman numerals and its
*                 decimal equivalent.
*   @inputs: char argument, Roman numeral {I, V, X, L, C, D, M}, {\0}
*   @output: integer, decimal equivalent.
**/
    
int mapromandigit(char c)
{
    int d = -1;
    
//  printf("%c ", c);
    switch (c)
    {
        case 'I':
            d = 1; break;
        case 'V':
            d = 5; break;
        case 'X':
            d = 10; break;
        case 'L':
            d = 50; break;
        case 'C':
            d = 100; break;
        case 'D':
            d = 500; break;
        case 'M':
            d = 1000; break;
        case '\0':
            d = 0; break;
        default:
        {
            d = -1; 
        //  printf("Invalid character\n");
            break;
        }
    }
//  printf(": %d\n", d);    
    return d;
}

/**
*   @brief: Comparator of 2 Roman numerals.
*   @description: This function compares the sequential, individual roman 
*   numerals and generates the composite value.
*   @inputs: integer r2, Roman numeral at next position.
*            integer r1, Roman numeral at first position. (from Left-to-right)
*   @output: integer, composite value.
**/
int compare(int r2, int r1)
{
    if ((r2 > r1) && ((r2/r1 == 5) || (r2/r1 == 10)))
    {        
        grule_rdu = r1; //check for redundancy
        r1 = r2 - r1;            
    }
    else
    {
        if (r2 == r1)
        {            
            if (grule_3eq == 3) 
            {
//                printf("Malformed Roman number string.\n");
//                printf("Cannot have more than 3 same symbols.\n");            
                return -1;
            }
            else
            {
                grule_3eq++;
            }
            r1 = r1 + r2;       
        }
        else if (r1 > r2)
        {            
            if (((r1-r2) == r2) && (grule_3eq == 2))
            {
                grule_3eq = 3;    
            }
            
            if (grule_rdu)
            {
                if (grule_rdu == r2)
                {
                    grule_rdu = 0;
//                    printf("Malformed Roman number string.\n");
//                    printf("Redundant symbols.\n");
                    return -1;
                }
            }
            gr0 = gr0 + r1;
            r1 = r2;
        }
        else
        {
//            printf("Error: Invalid combination of Roman numeral digits\n");
            return -1;
        }
    }
    return r1;
}

/**
*   @brief: Transform Roman number string to Decimal equivalent
*   @description: This function parses each string character sequentially to  
*   generate the composite decimal equivalent.
*   @inputs: char *str, Roman number string.
*   @output: integer, Decimal equivalent.
**/
int romantodecimal(char *strromannum)
{
    int i = 0;
//  int len = 0;
    int dec = 0;
    int r1 = 0, r2 = 0;
        
//    len = strlen(strromannum);
//    printf("Length of %s = %d\n", strromannum, len);

    r1 = mapromandigit(strromannum[i++]);
    
    if (r1 < 0)
    {
        return -1;    
    }
        
    while ((r2 = mapromandigit(strromannum[i++])) != 0)
    {
        r1 = compare(r2, r1);
        if (r1 == -1) 
        {
//            printf("error\n");
            break;    // error.
        }
    }
    
    if(r1 >= 0)
    {
        dec = gr0 + r1;
//        printf ("decimal value : %d\n", dec);
    }
    else
    {
        dec = -1;
//        printf ("decimal value : %d\n", dec);
    }
    
    gr0 = 0;        // reset
    grule_3eq = 1;  // reset
    grule_rdu = 0;  // reset
        
    return dec;
}

/**
*   @brief: Decimal calculator
*   @description: This function performs addition and substraction of 2 numbers.
*   @inputs: char *opr, Add or Sub operator.
*            integer d1, first decimal number.
*            integer d2, second decimal number.
*   @output: integer, result of add or sub.
**/
int calculator(char *opr, int d1, int d2)
{
    int result = 0;
    
    if ((d1 < 0) || (d2 < 0))
    {
        return -1;        
    }
    
    switch (opr[0])
    {
        case '+':
            result = d1 + d2;
            break;            
        case '-':
            if (d1 > d2)
            {
                result = d1 - d2;
            }
            else
            {
                result = d2 - d1;
            }
            break;
        default:
            result = -1;    // undefined operator
            break;
    }
    return result;
}

/**
*   @brief: Transform Decimal number to Roman number string.
*   @description: This function performs strcat to generate a roman number string.  
*   @inputs: integer result, decimal result of add or sub operation.
*   @output: char *str, Roman string equivalent.
**/
char* decimaltoroman(int result)
{
    int i = 0;
    int quotient = 0;
    int digits = 0;
    int remainder = 0;
    int value[4] = {0};
        
    quotient = result;
    
    do 
    {
        remainder = quotient % 10;
        value[digits++] = remainder; // * pow(10, digits);
        quotient = quotient/10;
    } while ((quotient != 0)); // || (digits < 3)); // MAX DIGITS = 3, 2, 1, 0
    
//    printf("digits : %d\n", digits);
//    printf("value[0] : %d\n", value[0]);
//    printf("value[1] : %d\n", value[1]);
//    printf("value[2] : %d\n", value[2]);
//    printf("value[3] : %d\n", value[3]);

/*    
    if (quotient != 0)
    {
        value[digits] = quotient;
    }    
*/    
    for (i = 0; i < value[3]; i++)
    {
        strcat(romanval, "M");
    }
    
    switch (value[2])
    {
        case 0:
            break;
        case 1:
        {
            strcat(romanval, "C"); break;
        }
        case 2:
        {    
            strcat(romanval, "CC"); break;
        }
        case 3:
        {
            strcat(romanval, "CCC"); break;
        }
        case 4:
        {
            strcat(romanval, "CD"); break;
        }    
        case 5:
        {
            strcat(romanval, "D"); break;
        }    
        case 6:
        {
            strcat(romanval, "DC"); break;
        }    
        case 7:
        {
            strcat(romanval, "DCC"); break;
        }    
        case 8:
        {
            strcat(romanval, "DCCC"); break;
        }    
        case 9:
        {
            strcat(romanval, "CM"); break;
        }    
        default:
            break;
    }
    
    switch (value[1])
    {
        case 0:
            break;
        case 1:
        {
            strcat(romanval, "X"); break;
        }    
        case 2:
        {
            strcat(romanval, "XX"); break;
        }
        case 3:
        {
            strcat(romanval, "XXX"); break;
        }
        case 4:
        {
            strcat(romanval, "XL"); break;
        }    
        case 5:
        {
            strcat(romanval, "L"); break;
        }    
        case 6:
        {
            strcat(romanval, "LX"); break;
        }    
        case 7:
        {
            strcat(romanval, "LXX"); break;
        }    
        case 8:
        {
            strcat(romanval, "LXXX"); break;
        }    
        case 9:
        {
            strcat(romanval, "XC"); break;
        }    
        default:
            break;
    }
    
    switch (value[0])
    {
        case 0:
            break;
        case 1:
        {
            strcat(romanval, "I"); break;
        }    
        case 2:
        {
            strcat(romanval, "II"); break;
        }    
        case 3:
        {
            strcat(romanval, "III"); break;
        }    
        case 4:
        {
            strcat(romanval, "IV"); break;
        }    
        case 5:
        {
            strcat(romanval, "V"); break;
        }    
        case 6:
        {
            strcat(romanval, "VI"); break;
        }    
        case 7:
        {
            strcat(romanval, "VII"); break;
        }    
        case 8:
        {
            strcat(romanval, "VIII"); break;
        }    
        case 9:
        {
            strcat(romanval, "IX"); break;
        }    
        default:
            break;
    }
     
    return romanval;       
}


