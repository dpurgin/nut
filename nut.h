/*
 * NUT: Nano Unit Tests for CARME
 *
 * Copyright (c) 2018 Dmitriy Purgin
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * = Basic usage
 *
 * Add nut.h and nut.c to your project. External dependency is the PicoGUI library.
 *
 * Whenever you want to run unit tests, call nut_init() once. After that implement the test case
 * and test the conditions with the following calls:
 *  * NUT_COMPARE(expected, actual): tests if two expressions are equal. The name of the test case
 *    is generated automatically.
 *  * NUT_VERIFY(condition): tests if the condition evaluates to true. The name of the test case
 *    is generated automatically.
 *  * NUT_COMPARE_NAMED(testName, expected, actual): like NUT_COMPARE, but you can provide a pretty
 *    test name.
 *  * NUT_VERIFY_NAMED(testName, condition): like NUT_VERIFY, but you can provide a pretty test name.
 *
 * Additionally, if NUT_FP_SUPPORT is defined, the following calls are available:
 *  * NUT_COMPARE_FLOAT(expected, actual): NUT_COMPARE for floats. Checks if two values have the
 *    difference of not more that FLT_EPSILON.
 *  * NUT_COMPARE_DOUBLE(expected, actual): like NUT_COMPARE_FLOAT but for doubles.
 *
 * When you are done with the test cases, call nut_end();
 *
 * If a C++ compiler is available, you can create an object of NutRunner instead of calling
 * nut_init() and nut_end():
 *
 * void run_unit_tests()
 * {
 *     NutRunner runner;
 *     NUT_COMPARE(...);
 *     NUT_VERIFY(...);
 *     ...
 * }
 *
 * = Example
 *
 * void run_unit_tests(void)
 * {
 *     nut_init();
 *
 *     // Compare variable with an expected value
 *     int some_value_should_be_42 = ...;
 *     NUT_COMPARE(some_value_should_be_42, 42);
 *
 *     // Verify if condition holds
 *     NOT_VERIFY(my_condition_should_be_true);
 *
 *     // Same as two above but pretty print test name
 *     NUT_COMPARE_NAMED("This should be 42", some_value_should_be_42, 42);
 *     NOT_VERIFY_NAMED("My awesome condition", my_condition_should_be_true);
 *
 *     // Additionally, if NUT_FP_SUPPORT is defined
 *     NUT_COMPARE_FLOAT(my_float_value, 0.42f);
 *     NUT_COMPARE_DOUBLE(my_double_value, 0.42);
 *     NUT_COMPARE_FLOAT_NAMED("One percent of it", my_float_value, 0.42f);
 *     NUT_COMPARE_DOUBLE_NAMED("Now with double precision", my_double_value, 0.42);
 *
 *     nut_end();
 * }
 *
 * void main(void)
 * {
 *    run_unit_tests();
 *
 *    // starting here do whatever you would normally do
 *
 *    while (1)
 *    {
 *    }
 * }
 *
 */

#ifndef NANO_UNIT_TESTS_H
#define NANO_UNIT_TESTS_H

#ifdef NUT_FP_SUPPORT
	#include <float.h>
	#include <math.h>
#endif

#define NUT_COMPARE_NAMED(testName, actual, expected) \
	nut_next_test(testName); \
	if ((actual) == (expected)) \
		nut_test_passes(); \
	else \
	    nut_test_fails();

#define NUT_VERIFY_NAMED(testName, condition) \
	nut_next_test(testName); \
	if (condition) \
	    nut_test_passes(); \
	else \
        nut_test_fails();

#define NUT_COMPARE(actual, expected) \
	NUT_COMPARE_NAMED(#actual " is " #expected, actual, expected)

#define NUT_VERIFY(condition) \
	NUT_VERIFY_NAMED(#condition " holds", condition)

#ifdef NUT_FP_SUPPORT
	#define NUT_COMPARE_FLOAT_NAMED(testName, actual, expected) \
		NUT_VERIFY_NAMED(testName, fabsf(actual - expected) <= FLT_EPSILON)

	#define NUT_COMPARE_DOUBLE_NAMED(testName, actual, expected) \
		NUT_VERIFY_NAMED(testName, fabs(actual - expected) <= DBL_EPSILON)

	#define NUT_COMPARE_FLOAT(actual, expected) \
		NUT_COMPARE_FLOAT_NAMED(#actual " is " #expected, actual, expected)

	#define NUT_COMPARE_DOUBLE(actual, expected) \
		NUT_COMPARE_DOUBLE_NAMED(#actual " is " #expected, actual, expected)
#endif // NUT_FP_SUPPORT

#ifdef __cplusplus
extern "C" {
#endif
	void nut_init(void);
	void nut_end(void);

	/* The following functions should be considered private API
	 * and shouldn't be called from the client code directly.
	 * Use NUT_COMPARE.. and NUT_VERIFY.. instead
	 */
	void nut_next_test(const char* test);
	void nut_test_passes(void);
	void nut_test_fails(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
	struct NutRunner
	{
		NutRunner()
		{
			nut_init();
		}
		~NutRunner()
		{
			nut_end();
		}
	};
#endif

#endif /* NUT_H_ */
