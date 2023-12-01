#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define MAX_CALIBRATION_SIZE 1024

typedef struct REQUIRED_INFO_T {
  char ** calibrations_amended;
  char ** calibrations_correrct;
  int qty_of_calibrations;
  int sum_of_calibration_values;
} * required_information;

void solve_problem(char * input_file_name,
    char first_number(char *, char(int, char, ...), int),
    char last_number(char *, char(int, char, ...), int), int strings_on);

void setup_calibrations_amended(required_information ri,
    char * input_file_name);

char determine_first_number(char * string, char validator(int, char, ...),
    int strings_on);
char determine_last_number(char * string, char validator(int, char, ...),
    int strings_on);
char is_valid_number(int strings_on, char c, ...);

char string_to_int(char * string);

void free_required_information(required_information ri);

int main(int argc, char *argv[]) {
  if(argc != 2) {
    fprintf(stderr, "Please Provide the Input File as a CLA\n");
    exit(1);
  }

  solve_problem(argv[1], determine_first_number, determine_last_number, 0);
  solve_problem(argv[1], determine_first_number, determine_last_number, 1);

  return 0;
}

void solve_problem(char * input_file_name,
    char first_number(char *, char(int, char, ...), int),
    char last_number(char *, char(int, char, ...), int), int strings_on) {
  required_information ri = calloc(1, sizeof(struct REQUIRED_INFO_T));

  setup_calibrations_amended(ri, input_file_name);

  ri->calibrations_correrct = calloc(ri->qty_of_calibrations, sizeof(char *));
  for(int i = 0; i < ri->qty_of_calibrations; i++) {
    ri->calibrations_correrct[i] = calloc(3, sizeof(char));
    ri->calibrations_correrct[i][0] = first_number(ri->calibrations_amended[i],
        is_valid_number, strings_on);
    ri->calibrations_correrct[i][1] = last_number(ri->calibrations_amended[i],
          is_valid_number, strings_on);
    ri->calibrations_correrct[i][2] = '\0';
  }

  for(int i = 0; i < ri->qty_of_calibrations; i++)
    ri->sum_of_calibration_values += (int)atoi(ri->calibrations_correrct[i]);
  printf("[RESULTING_SUM]: %d\n", ri->sum_of_calibration_values);

  free_required_information(ri);
}

void setup_calibrations_amended(required_information ri,
    char * input_file_name) {
  char tmp_buf[MAX_CALIBRATION_SIZE] = {0};

  FILE * input_file = fopen(input_file_name, "r");

  while(fgets(tmp_buf, MAX_CALIBRATION_SIZE, input_file)) {
    ri->qty_of_calibrations++;
    if(!(ri->calibrations_amended)) {
      ri->calibrations_amended = calloc(1, sizeof(char *));
    } else {
      ri->calibrations_amended = realloc(ri->calibrations_amended,
          ri->qty_of_calibrations * sizeof(char *));
    }

    size_t tmp_buf_len = strnlen(tmp_buf, MAX_CALIBRATION_SIZE);
    ri->calibrations_amended[ri->qty_of_calibrations - 1] = calloc(tmp_buf_len,
        sizeof(char));

    strncpy(ri->calibrations_amended[ri->qty_of_calibrations - 1], tmp_buf,
        tmp_buf_len);
    // We want '\n' => '\0' for str* functions
    ri->calibrations_amended[ri->qty_of_calibrations - 1][tmp_buf_len - 1] = '\0';
  }

  fclose(input_file);
}

char is_valid_number(int strings_on, char c, ...) {
  va_list args;
  va_start(args, c);

  char * maybe_string = va_arg(args, char *);

  // ascii for '0' is 48 and ascii for '9' is 57
  if((int)c >= 48 && (int)c <= 57) {
    return c;
  } else if(strings_on) {
    if(string_to_int(maybe_string) != '\0')
      return string_to_int(maybe_string);
  }
  va_end(args);
  return 0;
}

char determine_first_number(char * string, char validator(int, char, ...),
    int strings_on) {
  for(int i = 0; i < (int)strnlen(string, MAX_CALIBRATION_SIZE); i++) {
    if(strings_on) {
      if(validator(strings_on, string[i], string + i))
        return validator(strings_on, string[i], string + i);
    } else {
      if(validator(strings_on, string[i]))
        return validator(strings_on, string[i]);
    }
  }
  fprintf(stderr, "[DETERMINE_FIRST_NUMBER]: No Number for Calibration "
      "Code\n");
  exit(1);
}

char determine_last_number(char * string, char validator(int, char, ...),
    int strings_on) {
  for(int i = (int)strnlen(string, MAX_CALIBRATION_SIZE) - 1; i >= 0; i--) {
    if(strings_on) {
      if(validator(strings_on, string[i], string + i))
        return validator(strings_on, string[i], string + i);
    } else {
      if(validator(strings_on, string[i]))
        return validator(strings_on, string[i]);
    }
  }
  fprintf(stderr, "[DETERMINE_LAST_NUMBER]: No Number for Calibration "
      "Code\n");
  exit(1);
}

char string_to_int(char * string) {
  if(!strncmp(string, "zero", 4))       return '0';
  else if(!strncmp(string, "one", 3))   return '1';
  else if(!strncmp(string, "two", 3))   return '2';
  else if(!strncmp(string, "three", 5)) return '3';
  else if(!strncmp(string, "four", 4))  return '4';
  else if(!strncmp(string, "five", 4))  return '5';
  else if(!strncmp(string, "six", 3))   return '6';
  else if(!strncmp(string, "seven", 5)) return '7';
  else if(!strncmp(string, "eight", 5)) return '8';
  else if(!strncmp(string, "nine", 4))  return '9';
  return '\0';
}

void free_required_information(required_information ri) {
  for(int i = 0; i < ri->qty_of_calibrations; i++) {
    free(ri->calibrations_amended[i]);
    free(ri->calibrations_correrct[i]);
  }
  free(ri->calibrations_amended);
  free(ri->calibrations_correrct);
  free(ri);
}
