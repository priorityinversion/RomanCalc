#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "romancalc.h"

int main (int argc, char *argv[])
{
    int i = 0;
    int result = 0;
    int d1 = 0, d2 = 0;
    
    if (argc < 4) {
//      printf("usage: ./romancal2 <romanval1>\n");
        printf("usage: ./romancal2 <romanval1> <operator> <romanval2>\n");
        return 0;
    }
    
    
    while (argv[1][i] != '\0')
    {
        if (!isalpha(argv[1][i++]))
        {
            printf("Numeral-1 is not a Roman alphabet\n");
            return 0;
        }            
    }
    i = 0;
    
    while (argv[1][i] != '\0')
    {
        if (!isupper(argv[1][i++]))
        {
            printf("Numeral-1 is not Uppercase Roman alphabet\n");
            return 0;
        }            
    }
    i = 0;
       
    while (argv[3][i] != '\0')
    {
        if (!isalpha(argv[3][i++]))
        {
            printf("Numeral-2 is not a Roman alphabet\n");
            return 0;
        }            
    }
    i = 0;
    
    while (argv[3][i] != '\0')
    {
        if (!isupper(argv[3][i++]))
        {
            printf("Numeral-2 is not Uppercase Roman alphabet\n");
            return 0;
        }            
    }
    i = 0;    
    
           
    printf("Roman Calculator.\n");

    printf("Roman value 1: %s\n", argv[1]);
    d1 = romantodecimal(argv[1]);
    
    printf("Math Operator: %s\n", argv[2]);    
    
    printf("Roman value 2: %s\n", argv[3]);
    d2 = romantodecimal(argv[3]);
   
    result = calculator(argv[2], d1, d2);
    printf("Decimal Result : %s %s %s = %d\n", argv[1], argv[2], argv[3], result);
    
    printf("Roman Result : %s %s %s = %s\n", argv[1], argv[2], argv[3], decimaltoroman(result));
    return 0;
}
