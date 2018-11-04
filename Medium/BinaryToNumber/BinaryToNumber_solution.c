#include <stdio.h>
#include <stddef.h>

int binary_array_to_numbers(int bits[], size_t array_lenght)
{
  int result = 0;

  for (int i = 0; i < array_lenght; i++)
    result = result << 1 | bits[i];

  return result;
}

int main()
{
  int integer_value = 0;
  int binary_value[] = { 1, 0, 1, 0 };
  size_t n = sizeof(binary_value)/sizeof(binary_value[0]);

  integer_value = binary_array_to_numbers(binary_value, n);

  printf("The integer value is: %d\n", integer_value);

  return 0;
}