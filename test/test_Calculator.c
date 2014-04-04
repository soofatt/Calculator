#include "unity.h"
#include "CException.h"
#include "mock_Token.h"
#include "mock_Stack.h"
#include "Error.h"
#include "Calculator.h"
#include <stdio.h>

void setUp(){}
void tearDown(){}

void test_tryEvaluateOperatorsOnStackThenPush_should_evaluate_mul_first_then_push_minus(){
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
	push_Expect(&operatorStack, &multiply);
	
	tryEvaluateOperatorsOnStackThenPush(&operatorStack, &dataStack, &multiply);
	
}

void test_tryEvaluateOperatorsOnStackThenPush_should_evaluate_mul_first_then_push_minus_due_to_next_operator_is_or(){
	Stack dataStack;
	Stack operatorStack;
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	OperatorToken or = {.type = OPERATOR_TOKEN, .name = "|", .precedence = 10};
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken num2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken num10 = {.type = NUMBER_TOKEN, .value = 10};
	
	//3 | 2 * 5 - 4 = 7
	pop_ExpectAndReturn(&operatorStack, &multiply);
	pop_ExpectAndReturn(&dataStack, &num2);
	pop_ExpectAndReturn(&dataStack, &num5);
	createNumberToken_ExpectAndReturn(10, &num10);
	push_Expect(&dataStack, &num10);
	pop_ExpectAndReturn(&operatorStack, &or);
	push_Expect(&operatorStack, &or);
	push_Expect(&operatorStack, &minus);
	
	tryEvaluateOperatorsOnStackThenPush(&operatorStack, &dataStack, &minus);
	
}

void test_evaluateAllOperatorsOnStack_should_evaluate_mul_and_plus(){
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