#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int ValueFigure(const char Figure, int base) {
    if (Figure >= '0' && Figure <= '9') {
        return Figure - '0';
    }else if (Figure >= 'a' && Figure <= 'z') {
        return 10 + Figure - 'a';
    } else {
        printf("Caractère invalide : %c\n", Figure);
        exit(1);
    }
}

char FigureValue(int Value, int base) {
    if (Value >= 0 && Value <= 9) {
        return '0' + Value;
    } else if (Value >= 10 && Value <= 35) {
        return 'a' + Value - 10;
    } else {
        printf("Value invalide : %d\n", Value);
        exit(1);
    }
}

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "add: entering function\n");
  }
  int size2 = strlen(lhs);
    int Size2 = strlen(rhs);
    int size_max = (size2 > Size2) ? size2 : Size2;

    // Allouer de la mémoire pour la chaîne de caractères résultante
    char* Result = (char*)malloc((size_max + 2) * sizeof(char));
    if (Result == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(1);
    }

    int SizeResult = 0;
    int retention = 0;

    // Additionner les Figures des deux Values
    for (int i = 0; i < size_max; i++) {
        int sum = retention;

        if (i < size2) {
            sum += ValueFigure(lhs[size2 - 1 - i], base);
        }
        if (i < Size2) {
            sum += ValueFigure(rhs[Size2 - 1 - i], base);
        }

        Result[size_max - i] = FigureValue(sum % base, base);
        retention = sum / base;
        SizeResult++;
    }

    if (retention > 0) {
        Result[0] = FigureValue(retention, base);
        SizeResult++;
    } else {
        for (int i = 0; i < SizeResult; i++) {
            Result[i] = Result[i + 1];
        }
    }
    Result[SizeResult] = '\0';
    if (base == 2){
      
      char * string = malloc(sizeof(Result)+1);
      int i = 0;
      int index = 0;
      char c = '0';
      char * p = Result;
      while (*p==c){
        p++;
        i++;
      }
      for (i;i<=strlen(Result)-1;i++){
        string[index] = Result[i];
        index++;
      }
      string[index]='\0';
      return string;
    }

    return Result;
  // Fill the function, the goal is to compute lhs + rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
}

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "sub: entering function\n");
  }
  int size2 = strlen(lhs);
    int Size2 = strlen(rhs);
    int size_max = (size2 > Size2) ? size2 : Size2;

    // Allouer de la mémoire pour la chaîne de caractères résultante
    char* Result = (char*)malloc((size_max + 1) * sizeof(char));
    if (Result == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(1);
    }

    int SizeResult = 0;
    int retention = 0;

    // Soustraire les Figures des deux Values
    for (int i = 0; i < size_max; i++) {
        int difference = retention;

        if (i < size2) {
            difference += ValueFigure(lhs[size2 - 1 - i], base);
        }
        if (i < Size2) {
            difference -= ValueFigure(rhs[Size2 - 1 - i], base);
        }

        if (difference < 0) {
            difference += base;
            retention = -1;
        } else {
            retention = 0;
        }

        Result[size_max - i - 1] = FigureValue(difference, base);
        SizeResult++;
    }

    // Supprimer les zéros non significatifs en tête de la chaîne de caractères
    int index = 0;
    while (Result[index] == '0' && index < SizeResult - 1) {
        index++;
    }

    // Décaler la chaîne de caractères pour enlever les zéros non significatifs
    for (int i = index; i < SizeResult; i++) {
        Result[i - index] = Result[i];
    }

    SizeResult -= index;

    // Terminer la chaîne avec un caractère nul
    Result[SizeResult] = '\0';

    return Result;
  // Fill the function, the goal is to compute lhs - rhs (assuming lhs > rhs)
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
}

char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }
  if (strlen(rhs)==1 && *rhs=="0"){return "0";}
  int size2 = strlen(lhs);
    int Size2 = strlen(rhs);

    // Allouer de la mémoire pour la chaîne de caractères résultante
    char* Result = (char*)malloc((size2 + Size2 + 1) * sizeof(char));
    if (Result == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(1);
    }

    // Initialiser le résultat à zéro
    for (int i = 0; i < size2 + Size2; i++) {
        Result[i] = '0';
    }
    Result[size2 + Size2] = '\0';

    // Effectuer la multiplication
    for (int i = 0; i < size2; i++) {
        int Figure1 = ValueFigure(lhs[size2 - 1 - i], base);
        int retention = 0;

        for (int j = 0; j < Size2; j++) {
            int Figure2 = ValueFigure(rhs[Size2 - 1 - j], base);
            int product = Figure1 * Figure2 + retention + ValueFigure(Result[i + j], base);

            Result[i + j] = FigureValue(product % base, base);
            retention = product / base;
        }

        // Ajouter la retention supplémentaire si nécessaire
        int index = i + Size2;
        while (retention > 0) {
            int sum = retention + ValueFigure(Result[index], base);
            Result[index] = FigureValue(sum % base, base);
            retention = sum / base;
            index++;
        }
    }

    // Inverser la chaîne de caractères résultante
    int SizeResult = strlen(Result);
    for (int i = 0; i < SizeResult / 2; i++) {
        char temp = Result[i];
        Result[i] = Result[SizeResult - 1 - i];
        Result[SizeResult - 1 - i] = temp;
    }
    char * string = malloc(sizeof(Result)+1);
    int i = 0;
    int index = 0;
    char c = '0';
    char * p = Result;
    while (*p==c){
      p++;
      i++;
    }
    for (i;i<=strlen(Result)-1;i++){
      string[index] = Result[i];
      index++;
    }
    string[index]='\0';
    if (strlen(string)==0){return "0";}
    return string;
  // Fill the function, the goal is to compute lhs * rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
}

// Here are some utility functions that might be helpful to implement add, sub
// and mul:

unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  // Convert an integer value to a digit from get_all_digits()
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value];
}

char *reverse(char *str) {
  // Reverse a string in place, return the pointer for convenience
  // Might be helpful if you fill your char* buffer from left to right
  const size_t length = strlen(str);
  const size_t bound = length / 2;
  for (size_t i = 0; i < bound; ++i) {
    char tmp = str[i];
    const size_t mirror = length - i - 1;
    str[i] = str[mirror];
    str[mirror] = tmp;
  }
  return str;
}

const char *drop_leading_zeros(const char *number) {
  // If the number has leading zeros, return a pointer past these zeros
  // Might be helpful to avoid computing a result with leading zeros
  if (*number == '\0') {
    return number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return number;
}

void debug_abort(const char *debug_msg) {
  // Print a message and exit
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}
