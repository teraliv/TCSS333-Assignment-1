/*
 * TCSS 333 - Autumn 2015
 *
 * Assignment 1 - Bitmap image manipulation.
 * Alex Terikov
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Functions prototypes
void calculateBinary();
double binaryToDouble(char str[]);
void doubleToBinary(double num);

int main(int argc, const char * argv[]) {
    
    while (1) {
        calculateBinary();
    }
    
    return 0;
}

/***************************************************
 calculateBinary
 
 This is the main function to output
 binary arithmetics.
 
 */
void calculateBinary() {
    
    char *line = malloc (256); // Allocate memory for input array
    int count = 0;
    char *separator;
    char *tokens[4];
    char operator;
    
    double num1;
    double num2;
    double numTotal = 0.00;
    
    printf("Enter an expression using binary numbers or Q to quit: ");
    
    // Get the name, with size limit.
    fgets (line, 256, stdin);
    
    
    // Remove trailing newline, if there.
    if ((strlen(line)>0) && (line[strlen (line) - 1] == '\n'))
        line[strlen (line) - 1] = '\0';
    
    // Break a line into string tokens
    // in our case tokens are: [operand] [operator] [operand]
    separator = strtok(line," ");
    
    // Fill in tokens array
    while (separator != NULL) {
        tokens[count++] = separator;
        separator = strtok(NULL, " ");
    }
    
    
    num1 = binaryToDouble(tokens[0]); // operand 1
    num2 = binaryToDouble(tokens[2]); // operand 2
    operator = *tokens[1]; // operator
    
    // Do arithmetic operations
    if (operator == '+') {
        numTotal = num1 + num2;
    } else if (operator == '-') {
        numTotal = num1 - num2;
    } else if (operator == '*') {
        numTotal = num1 * num2;
    } else if (operator == '/') {
        numTotal = num1 / num2;
    }
    
    // Print arithmetic results.
    printf("%.10f %c %.10f = %.10f\n", num1, operator, num2, numTotal);
    printf("%s %c %s = ", tokens[0], operator, tokens[2]);
    doubleToBinary(numTotal);
    
    free (line); // Free memory from array
    
}

/***************************************************
 binaryToDouble
 
 Converts a binary number to a double.
 
 */
double binaryToDouble(char str[]) {
    
    int length = (int) strlen(str);
    int indexOfPoint = 0;
    int numSum = 0;
    int i;
    
    double decSum = 0.00;
    double power = 0.00;
    double total = 0.00;
    
    // Find the index of point
    for (i = 0; i < length; i++) {
        if (str[i] == '.') {
            indexOfPoint = i;
        }
    }
    
    // Calculate the real part of a decimal number
    for (i = indexOfPoint - 1; i >= 0; i--) {
        numSum += ((str[i] - 48) * pow(2, power++));
    }
    
    power = 0.5; // start with power of .5
    
    // Calculate fractional part of decimal number
    for (i = indexOfPoint + 1; i < length; i++) {
        decSum += ((str[i] - 48) * power);
        power /= 2;
    }
    
    return total = numSum + decSum;
}

/***************************************************
 binaryToDouble
 
 Converts a double number to a binary representation
 of this number.
 
 */
void doubleToBinary(double numberToConvert) {
    
    int power = 0;
    int counter, i;
    double originalNum = numberToConvert;
    
    // Find the right power
    while ((pow(2, power)) < numberToConvert) {
        power++;
    }
    
    counter = power;
    power = (pow(2, power)/2); // find the right power
    
    /* If the number to convert is < 1
     add leading 0 before point. */
    if (numberToConvert < 1) {
        printf("0");
    }
    
    /* Print the binary representation of
     the real part of a double number. */
    for (i = 0; i < counter; i++) {
        
        if ((numberToConvert - power) >= 0) {
            printf("1");
            
            numberToConvert -= power;
            power /= 2;
            
        } else if ((numberToConvert - power) < 0) {
            
            printf("0");
            power /= 2;
        }
    }
    
    printf(".");
    
    int decimalCounter = 0;
    double decimalPower = 0.5;
    double decimalNum;
    
    // get the fractional part of a double
    decimalNum = fmod(originalNum, 1.0);
    
    /* Print the binary representation of
     the fractional part of a double number. */
    while ((decimalNum != 0) && (decimalCounter < 20)) {
        
        decimalCounter++;
        
        if ((decimalNum - decimalPower) >= 0) {
            printf("1");
            decimalNum -= decimalPower;
            decimalPower /= 2;
        } else if ((decimalNum - decimalPower) < 0) {
            printf("0");
            decimalPower /= 2;
        }
    }
    
    printf("\n");
}