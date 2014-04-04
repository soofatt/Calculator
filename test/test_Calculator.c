#include "unity.h"
#include "CException.h"
#include "mock_Token.h"
#include "mock_Stack.h"
#include "Error.h"
#include "Calculator.h"
#include <stdio.h>

void setUp(){}
void tearDown(){}

void test_evaluate_should_evaluate_1_plus_2_return_3(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken num1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};

	//1 + 2 = 3
	tokenizerNew_ExpectAndReturn("1 + 2", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num1);
	push_Expect(&dataStack, &num1);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num2);
	push_Expect(&dataStack, &num2);
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &num1);
	pop_ExpectAndReturn(&dataStack, &num2);
	createNumberToken_ExpectAndReturn(3, &num3);
	push_Expect(&dataStack, &num3);
	pop_ExpectAndReturn(&operatorStack, NULL);
	pop_ExpectAndReturn(&dataStack, &num3);
	
	Try{
		result = evaluate("1 + 2", &operatorStack, &dataStack);
	}Catch(e){
		TEST_FAIL_MESSAGE("Exception thrown");
	}
	
	TEST_ASSERT_EQUAL(3, result);
}

void test_evaluate_should_evaluate_4_mul_3_return_12(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	OperatorToken mul = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken num12 = {.type = NUMBER_TOKEN, .value = 12};

	//4 * 3 = 12
	tokenizerNew_ExpectAndReturn("4 * 3", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num4);
	push_Expect(&dataStack, &num4);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&mul);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &mul);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num3);
	push_Expect(&dataStack, &num3);
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&operatorStack, &mul);
	pop_ExpectAndReturn(&dataStack, &num4);
	pop_ExpectAndReturn(&dataStack, &num3);
	createNumberToken_ExpectAndReturn(12, &num12);
	push_Expect(&dataStack, &num12);
	pop_ExpectAndReturn(&operatorStack, NULL);
	pop_ExpectAndReturn(&dataStack, &num12);
	
	Try{
		result = evaluate("4 * 3", &operatorStack, &dataStack);
	}Catch(e){
		TEST_FAIL_MESSAGE("Exception thrown");
	}
	
	TEST_ASSERT_EQUAL(12, result);
}

// void test_evaluate_should_evaluate_3_plus_4_plus_5_minus_6(){
// Test fixture
	// CEXCEPTION_T e;
	// Tokenizer tokenizer;
	// Stack dataStack;
	// Stack operatorStack;
	// int result;
	
	// OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	// OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	// OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	// NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	// NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	// NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	// NumberToken num6 = {.type = NUMBER_TOKEN, .value = 6};
	// NumberToken num7 = {.type = NUMBER_TOKEN, .value = 7};
	// NumberToken num12 = {.type = NUMBER_TOKEN, .value = 12};
	// NumberToken number6 = {.type = NUMBER_TOKEN, .value = 6};

	// 4 * 3 = 12
	// tokenizerNew_ExpectAndReturn("3 + 4 + 5 - 6", &tokenizer);
	// nextToken_ExpectAndReturn(&tokenizer, (Token *)&num3);
	// push_Expect(&dataStack, &num3);
	// nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	// pop_ExpectAndReturn(&operatorStack, NULL);
	// push_Expect(&operatorStack, &plus);
	// nextToken_ExpectAndReturn(&tokenizer, (Token *)&num4);
	// push_Expect(&dataStack, &num4);
	// nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	// pop_ExpectAndReturn(&operatorStack, &plus);
	// push_Expect(&operatorStack, &plus);
	// nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	// pop_ExpectAndReturn(&operatorStack, &mul);
	// pop_ExpectAndReturn(&dataStack, &num4);
	// pop_ExpectAndReturn(&dataStack, &num3);
	// createNumberToken_ExpectAndReturn(12, &num12);
	// push_Expect(&dataStack, &num12);
	// pop_ExpectAndReturn(&operatorStack, NULL);
	// pop_ExpectAndReturn(&dataStack, &num12);
	
	// Try{
		// result = evaluate("4 * 3", &operatorStack, &dataStack);
	// }Catch(e){
		// TEST_FAIL_MESSAGE("Exception thrown");
	// }
	
	// TEST_ASSERT_EQUAL(12, result);
// }

void test_evaluate_should_throw_exception_given_plus(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};

	//+
	tokenizerNew_ExpectAndReturn("+", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	
	Try{
		result = evaluate("+", &operatorStack, &dataStack);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_NOT_DATA, e);
	}
}

void test_evaluate_should_throw_exception_given_38_39(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	NumberToken num38 = {.type = NUMBER_TOKEN, .value = 38};
	NumberToken num39 = {.type = NUMBER_TOKEN, .value = 39};

	//+
	tokenizerNew_ExpectAndReturn("38 39", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num38);
	push_Expect(&dataStack, &num38);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num39);
	
	Try{
		result = evaluate("38 39", &operatorStack, &dataStack);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR, e);
	}
}

void test_evaluate_should_throw_exception_given_40_plus_mul(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	NumberToken num40 = {.type = NUMBER_TOKEN, .value = 40};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken mul = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};

	//+
	tokenizerNew_ExpectAndReturn("40 + *", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num40);
	push_Expect(&dataStack, &num40);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&mul);
	
	Try{
		result = evaluate("40 + *", &operatorStack, &dataStack);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_NOT_DATA, e);
	}
}

void test_evaluate_should_throw_exception_given_40_xor_2_minus(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	NumberToken num42 = {.type = NUMBER_TOKEN, .value = 42};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};

	//+
	tokenizerNew_ExpectAndReturn("42 ^ 2 -  ", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num42);
	push_Expect(&dataStack, &num42);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&xor);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &xor);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num2);
	push_Expect(&dataStack, &num2);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&minus);
	pop_ExpectAndReturn(&operatorStack, &xor);
	push_Expect(&operatorStack, &xor);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &minus);
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	Try{
		result = evaluate("42 ^ 2 -  ", &operatorStack, &dataStack);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_EXPRESSION, e);
	}
}

void test_evaluate_should_throw_exception_given_43_hash(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	NumberToken num43 = {.type = NUMBER_TOKEN, .value = 43};

	//+
	tokenizerNew_ExpectAndReturn("43 #", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num43);
	push_Expect(&dataStack, &num43);
	nextToken_ExpectAndThrow(&tokenizer, ERR_INVALID_TOKEN);
	
	Try{
		result = evaluate("43 #", &operatorStack, &dataStack);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_TOKEN, e);
	}
}

void test_tryEvaluateOperatorsOnStackThenPush_should_evaluate_mul_first_then_push_minus(){
//Test fixture
	Stack dataStack;
	Stack operatorStack;
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken num10 = {.type = NUMBER_TOKEN, .value = 10};
	NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken num20 = {.type = NUMBER_TOKEN, .value = 20};
	NumberToken num16 = {.type = NUMBER_TOKEN, .value = 16};
	
	//2 * 10 - 4 = 16
	pop_ExpectAndReturn(&operatorStack, &multiply);
	pop_ExpectAndReturn(&dataStack, &num2);
	pop_ExpectAndReturn(&dataStack, &num10);
	createNumberToken_ExpectAndReturn(20, &num20);
	push_Expect(&dataStack, &num20);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &minus);
	
	tryEvaluateOperatorsOnStackThenPush(&operatorStack, &dataStack, &minus);
	
}

void test_tryEvaluateOperatorsOnStackThenPush_should_just_push_mul_if_minus_first(){
//Test fixture
	Stack dataStack;
	Stack operatorStack;
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken num10 = {.type = NUMBER_TOKEN, .value = 10};
	NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken num20 = {.type = NUMBER_TOKEN, .value = 20};
	NumberToken num16 = {.type = NUMBER_TOKEN, .value = 16};
	
	//2 - 10 * 4 = 16
	pop_ExpectAndReturn(&operatorStack, &minus);
	push_Expect(&operatorStack, &minus);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &multiply);
	
	tryEvaluateOperatorsOnStackThenPush(&operatorStack, &dataStack, &multiply);
	
}

void test_evaluateAllOperatorsOnStack_should_evaluate_mul_and_plus(){
//Test fixture
	Stack dataStack;
	Stack operatorStack;
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken num15 = {.type = NUMBER_TOKEN, .value = 15};
	NumberToken num17 = {.type = NUMBER_TOKEN, .value = 17};
	
	//2 + 3 * 5 = 17
	pop_ExpectAndReturn(&operatorStack, &multiply);
	pop_ExpectAndReturn(&dataStack, &num3);
	pop_ExpectAndReturn(&dataStack, &num5);
	createNumberToken_ExpectAndReturn(15, &num15);
	push_Expect(&dataStack, &num15);
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &num15);
	pop_ExpectAndReturn(&dataStack, &num2);
	createNumberToken_ExpectAndReturn(17, &num17);
	push_Expect(&dataStack, &num17);
	pop_ExpectAndReturn(&operatorStack, NULL);
	
	evaluateAllOperatorsOnStack(&operatorStack, &dataStack);
	
}

void test_evaluateAllOperatorsOnStack_should_evaluate_xor_and_or(){
//Test fixture
	Stack dataStack;
	Stack operatorStack;
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};
	OperatorToken or = {.type = OPERATOR_TOKEN, .name = "|", .precedence = 10};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken num6 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken num7 = {.type = NUMBER_TOKEN, .value = 7};
	
	//5 ^ 6 | 4 = 7
	pop_ExpectAndReturn(&operatorStack, &xor);
	pop_ExpectAndReturn(&dataStack, &num5);
	pop_ExpectAndReturn(&dataStack, &num6);
	createNumberToken_ExpectAndReturn(3, &num3);
	push_Expect(&dataStack, &num3);
	pop_ExpectAndReturn(&operatorStack, &or);
	pop_ExpectAndReturn(&dataStack, &num3);
	pop_ExpectAndReturn(&dataStack, &num4);
	createNumberToken_ExpectAndReturn(7, &num7);
	push_Expect(&dataStack, &num7);
	pop_ExpectAndReturn(&operatorStack, NULL);
	
	evaluateAllOperatorsOnStack(&operatorStack, &dataStack);
	
}

void test_evaluateOperator_should_add_two_numbers_if_operator_is_plus(){
//Test fixture
	Stack dataStack;
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	
	pop_ExpectAndReturn(&dataStack, &num2);
	pop_ExpectAndReturn(&dataStack, &num3);
	createNumberToken_ExpectAndReturn(5, &num5);
	push_Expect(&dataStack, &num5);
	
	evaluateOperator(&dataStack, &plus);
	
}

void test_evaluateOperator_should_minus_two_numbers_if_operator_is_minus(){
//Test fixture
	Stack dataStack;
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken num1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	
	pop_ExpectAndReturn(&dataStack, &num3);
	pop_ExpectAndReturn(&dataStack, &num1);
	createNumberToken_ExpectAndReturn(2, &num2);
	push_Expect(&dataStack, &num2);
	
	evaluateOperator(&dataStack, &minus);
	
}

void test_evaluateOperator_should_multiply_two_numbers_if_operator_is_multiply(){
//Test fixture
	Stack dataStack;
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken num20 = {.type = NUMBER_TOKEN, .value = 20};
	
	pop_ExpectAndReturn(&dataStack, &num4);
	pop_ExpectAndReturn(&dataStack, &num5);
	createNumberToken_ExpectAndReturn(20, &num20);
	push_Expect(&dataStack, &num20);
	
	evaluateOperator(&dataStack, &multiply);
	
}

void test_evaluateOperator_should_divide_two_numbers_if_operator_is_divide(){
//Test fixture
	Stack dataStack;
	OperatorToken divide = {.type = OPERATOR_TOKEN, .name = "/", .precedence = 100};
	NumberToken num10 = {.type = NUMBER_TOKEN, .value = 10};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	
	pop_ExpectAndReturn(&dataStack, &num10);
	pop_ExpectAndReturn(&dataStack, &num2);
	createNumberToken_ExpectAndReturn(5, &num5);
	push_Expect(&dataStack, &num5);
	
	evaluateOperator(&dataStack, &divide);
	
}

void test_evaluateOperator_should_modulo_two_numbers_if_operator_is_modulo(){
//Test fixture
	Stack dataStack;
	OperatorToken modulo = {.type = OPERATOR_TOKEN, .name = "%", .precedence = 100};
	NumberToken num10 = {.type = NUMBER_TOKEN, .value = 10};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken num1 = {.type = NUMBER_TOKEN, .value = 1};
	
	pop_ExpectAndReturn(&dataStack, &num10);
	pop_ExpectAndReturn(&dataStack, &num3);
	createNumberToken_ExpectAndReturn(1, &num1);
	push_Expect(&dataStack, &num1);
	
	evaluateOperator(&dataStack, &modulo);
	
}

void test_evaluateOperator_should_xor_two_numbers_if_operator_is_xor(){
//Test fixture
	Stack dataStack;
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken num6 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	
	pop_ExpectAndReturn(&dataStack, &num5);
	pop_ExpectAndReturn(&dataStack, &num6);
	createNumberToken_ExpectAndReturn(3, &num3);
	push_Expect(&dataStack, &num3);
	
	evaluateOperator(&dataStack, &xor);
	
}

void test_evaluateOperator_should_and_two_numbers_if_operator_is_and(){
//Test fixture
	Stack dataStack;
	OperatorToken and = {.type = OPERATOR_TOKEN, .name = "&", .precedence = 20};
	NumberToken num7 = {.type = NUMBER_TOKEN, .value = 7};
	NumberToken num17 = {.type = NUMBER_TOKEN, .value = 17};
	NumberToken num1 = {.type = NUMBER_TOKEN, .value = 1};
	
	pop_ExpectAndReturn(&dataStack, &num7);
	pop_ExpectAndReturn(&dataStack, &num17);
	createNumberToken_ExpectAndReturn(1, &num1);
	push_Expect(&dataStack, &num1);
	
	evaluateOperator(&dataStack, &and);
	
}

void test_evaluateOperator_should_or_two_numbers_if_operator_is_or(){
//Test fixture
	Stack dataStack;
	OperatorToken or = {.type = OPERATOR_TOKEN, .name = "|", .precedence = 10};
	NumberToken num6 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken num7 = {.type = NUMBER_TOKEN, .value = 7};
	
	pop_ExpectAndReturn(&dataStack, &num6);
	pop_ExpectAndReturn(&dataStack, &num5);
	createNumberToken_ExpectAndReturn(7, &num7);
	push_Expect(&dataStack, &num7);
	
	evaluateOperator(&dataStack, &or);
	
}