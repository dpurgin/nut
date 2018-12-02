# NUT: Nano Unit Tests
Unit testing library for CARME kit

## Dependencies

NUT requires the PicoGUI library.

## Basic usage

Add `nut.h` and `nut.c` to your project. External dependency is the PicoGUI library.
Whenever you want to run unit tests, call `nut_init()` once. After that implement the test case
and test the conditions with the following calls:
 * `NUT_COMPARE(expected, actual)`: tests if two expressions are equal. The name of the test case
   is generated automatically.
 * `NUT_VERIFY(condition)`: tests if the condition evaluates to true. The name of the test case
   is generated automatically.
 * `NUT_COMPARE_NAMED(testName, expected, actual)`: like `NUT_COMPARE`, but you can provide a pretty
   test name.
 * `NUT_VERIFY_NAMED(testName, condition)`: like `NUT_VERIFY`, but you can provide a pretty test name.
Additionally, if NUT_FP_SUPPORT is defined, the following calls are available:
 * `NUT_COMPARE_FLOAT(expected, actual)`: `NUT_COMPARE` for floats. Checks if two values have the
   difference of not more that FLT_EPSILON.
 * `NUT_COMPARE_DOUBLE(expected, actual)`: like `NUT_COMPARE_FLOAT` but for doubles.

When you are done with the test cases, call nut_end();

If a C++ compiler is available, you can create an object of NutRunner instead of calling
`nut_init()` and `nut_end()`:

```c
void run_unit_tests()
{
    NutRunner runner;
    NUT_COMPARE(...);
    NUT_VERIFY(...);
    ...
}
```

## Example

```c
void run_unit_tests(void)
{
    nut_init();
    /* Compare variable with an expected value */
    int some_value_should_be_42 = ...;
    NUT_COMPARE(some_value_should_be_42, 42);
    / Verify if condition holds */
    NOT_VERIFY(my_condition_should_be_true);
    /* Same as two above but pretty print test name */
    NUT_COMPARE_NAMED("This should be 42", some_value_should_be_42, 42);
    NOT_VERIFY_NAMED("My awesome condition", my_condition_should_be_true);
    /* Additionally, if NUT_FP_SUPPORT is defined */
    NUT_COMPARE_FLOAT(my_float_value, 0.42f);
    NUT_COMPARE_DOUBLE(my_double_value, 0.42);
    NUT_COMPARE_FLOAT_NAMED("One percent of it", my_float_value, 0.42f);
    NUT_COMPARE_DOUBLE_NAMED("Now with double precision", my_double_value, 0.42);
    nut_end();
}
void main(void)
{
   run_unit_tests();

   /* starting here do whatever you would normally do */

   while (1)
   {
   }
}
```