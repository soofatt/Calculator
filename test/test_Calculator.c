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

void test_evaluate_should_evaluate_3_plus_4_plus_5_minus_6(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken plus1 = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	NumberToken num3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken num4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken num5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken num6 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken result7 = {.type = NUMBER_TOKEN, .value = 7};
	NumberToken result12 = {.type = NUMBER_TOKEN, .value = 12};
	NumberToken result6 = {.type = NUMBER_TOKEN, .value = 6};

	//3 + 4 + 5 - 6 = 6
	tokenizerNew_ExpectAndReturn("3 + 4 + 5 - 6", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num3);
	push_Expect(&dataStack, &num3);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num4);
	push_Expect(&dataStack, &num4);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus1);
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &num4);
	pop_ExpectAndReturn(&dataStack, &num3);
	createNumberToken_ExpectAndReturn(7, &result7);
	push_Expect(&dataStack, &result7);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus1);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num5);
	push_Expect(&dataStack, &num5);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&minus);
	pop_ExpectAndReturn(&operatorStack, &plus1);
	pop_ExpectAndReturn(&dataStack, &num5);
	pop_ExpectAndReturn(&dataStack, &result7);
	createNumberToken_ExpectAndReturn(12, &result12);
	push_Expect(&dataStack, &result12);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &minus);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num6);
	push_Expect(&dataStack, &num6);
	
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&operatorStack, &minus);
	pop_ExpectAndReturn(&dataStack, &num6);
	pop_ExpectAndReturn(&dataStack, &result12);
	createNumberToken_ExpectAndReturn(6, &result6);
	push_Expect(&dataStack, &result6);
	pop_ExpectAndReturn(&operatorStack, NULL);
	
	pop_ExpectAndReturn(&dataStack, &result6);
	
	Try{
		result = evaluate("3 + 4 + 5 - 6", &operatorStack, &dataStack);
	}Catch(e){
		TEST_FAIL_MESSAGE("Exception thrown");
	}
	
	TEST_ASSERT_EQUAL(6, result);
}

void test_evaluate_should_evaluate_111_divide_12_plus_13_and_14(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken divide = {.type = OPERATOR_TOKEN, .name = "/", .precedence = 100};
	OperatorToken and = {.type = OPERATOR_TOKEN, .name = "&", .precedence = 20};
	NumberToken num111 = {.type = NUMBER_TOKEN, .value = 111};
	NumberToken num12 = {.type = NUMBER_TOKEN, .value = 12};
	NumberToken num13 = {.type = NUMBER_TOKEN, .value = 13};
	NumberToken num14 = {.type = NUMBER_TOKEN, .value = 14};
	NumberToken result9 = {.type = NUMBER_TOKEN, .value = 9};
	NumberToken result22 = {.type = NUMBER_TOKEN, .value = 22};
	NumberToken result6 = {.type = NUMBER_TOKEN, .value = 6};

	//111 / 12 + 13 & 14
	tokenizerNew_ExpectAndReturn("111 / 12 + 13 & 14", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num111);
	push_Expect(&dataStack, &num111);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&divide);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &divide);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num12);
	push_Expect(&dataStack, &num12);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, &divide);
	pop_ExpectAndReturn(&dataStack, &num12);
	pop_ExpectAndReturn(&dataStack, &num111);
	createNumberToken_ExpectAndReturn(9, &result9);
	push_Expect(&dataStack, &result9);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num13);
	push_Expect(&dataStack, &num13);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&and);
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &num13);
	pop_ExpectAndReturn(&dataStack, &result9);
	createNumberToken_ExpectAndReturn(22, &result22);
	push_Expect(&dataStack, &result22);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &and);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num14);
	push_Expect(&dataStack, &num14);
	
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&operatorStack, &and);
	pop_ExpectAndReturn(&dataStack, &num14);
	pop_ExpectAndReturn(&dataStack, &result22);
	createNumberToken_ExpectAndReturn(6, &result6);
	push_Expect(&dataStack, &result6);
	pop_ExpectAndReturn(&operatorStack, NULL);
	
	pop_ExpectAndReturn(&dataStack, &result6);
	
	Try{
		result = evaluate("111 / 12 + 13 & 14", &operatorStack, &dataStack);
	}Catch(e){
		TEST_FAIL_MESSAGE("Exception thrown");
	}
	
	TEST_ASSERT_EQUAL(6, result);
}

void test_evaluate_should_evaluate_211_and_22_xor_23_plus_24_mul_25(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	OperatorToken and = {.type = OPERATOR_TOKEN, .name = "&", .precedence = 20};
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken num211 = {.type = NUMBER_TOKEN, .value = 211};
	NumberToken num22 = {.type = NUMBER_TOKEN, .value = 22};
	NumberToken num23 = {.type = NUMBER_TOKEN, .value = 23};
	NumberToken num24 = {.type = NUMBER_TOKEN, .value = 24};
	NumberToken num25 = {.type = NUMBER_TOKEN, .value = 25};
	NumberToken result600 = {.type = NUMBER_TOKEN, .value = 600};
	NumberToken result623 = {.type = NUMBER_TOKEN, .value = 623};
	NumberToken result633 = {.type = NUMBER_TOKEN, .value = 633};
	NumberToken result81 = {.type = NUMBER_TOKEN, .value = 81};

	//211 & 22 ^ 23 + 24 * 25
	tokenizerNew_ExpectAndReturn("211 & 22 ^ 23 + 24 * 25", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num211);
	push_Expect(&dataStack, &num211);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&and);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &and);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num22);
	push_Expect(&dataStack, &num22);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&xor);
	pop_ExpectAndReturn(&operatorStack, &and);
	push_Expect(&operatorStack, &and);
	push_Expect(&operatorStack, &xor);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num23);
	push_Expect(&dataStack, &num23);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, &xor);
	push_Expect(&operatorStack, &xor);
	push_Expect(&operatorStack, &plus);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num24);
	push_Expect(&dataStack, &num24);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&multiply);
	pop_ExpectAndReturn(&operatorStack, &plus);
	push_Expect(&operatorStack, &plus);
	push_Expect(&operatorStack, &multiply);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num25);
	push_Expect(&dataStack, &num25);
	
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&operatorStack, &multiply);
	pop_ExpectAndReturn(&dataStack, &num25);
	pop_ExpectAndReturn(&dataStack, &num24);
	createNumberToken_ExpectAndReturn(600, &result600);
	push_Expect(&dataStack, &result600);
	
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &result600);
	pop_ExpectAndReturn(&dataStack, &num23);
	createNumberToken_ExpectAndReturn(623, &result623);
	push_Expect(&dataStack, &result623);
	
	pop_ExpectAndReturn(&operatorStack, &xor);
	pop_ExpectAndReturn(&dataStack, &result623);
	pop_ExpectAndReturn(&dataStack, &num22);
	createNumberToken_ExpectAndReturn(633, &result633);
	push_Expect(&dataStack, &result633);
	
	pop_ExpectAndReturn(&operatorStack, &and);
	pop_ExpectAndReturn(&dataStack, &result633);
	pop_ExpectAndReturn(&dataStack, &num211);
	createNumberToken_ExpectAndReturn(81, &result81);
	push_Expect(&dataStack, &result81);
	
	pop_ExpectAndReturn(&operatorStack, NULL);
	
	pop_ExpectAndReturn(&dataStack, &result81);
	
	Try{
		result = evaluate("211 & 22 ^ 23 + 24 * 25", &operatorStack, &dataStack);
	}Catch(e){
		TEST_FAIL_MESSAGE("Exception thrown");
	}
	
	TEST_ASSERT_EQUAL(81, result);
}

void test_evaluate_should_evaluate_266_or_27_xor_28_plus_29_and_30(){
//Test fixture
	CEXCEPTION_T e;
	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int result;
	
	OperatorToken or = {.type = OPERATOR_TOKEN, .name = "|", .precedence = 10};
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken and = {.type = OPERATOR_TOKEN, .name = "&", .precedence = 20};
	NumberToken num266 = {.type = NUMBER_TOKEN, .value = 266};
	NumberToken num27 = {.type = NUMBER_TOKEN, .value = 27};
	NumberToken num28 = {.type = NUMBER_TOKEN, .value = 28};
	NumberToken num29 = {.type = NUMBER_TOKEN, .value = 29};
	NumberToken num30 = {.type = NUMBER_TOKEN, .value = 30};
	NumberToken result57 = {.type = NUMBER_TOKEN, .value = 57};
	NumberToken result34 = {.type = NUMBER_TOKEN, .value = 34};
	NumberToken result2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken result266 = {.type = NUMBER_TOKEN, .value = 266};

	//266 | 27 ^ 28 + 29 & 30
	tokenizerNew_ExpectAndReturn("266 | 27 ^ 28 + 29 & 30", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num266);
	push_Expect(&dataStack, &num266);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&or);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &or);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num27);
	push_Expect(&dataStack, &num27);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&xor);
	pop_ExpectAndReturn(&operatorStack, &or);
	push_Expect(&operatorStack, &or);
	push_Expect(&operatorStack, &xor);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num28);
	push_Expect(&dataStack, &num28);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, &xor);
	push_Expect(&operatorStack, &xor);
	push_Expect(&operatorStack, &plus);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num29);
	push_Expect(&dataStack, &num29);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&and);
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &num29);
	pop_ExpectAndReturn(&dataStack, &num28);
	createNumberToken_ExpectAndReturn(57, &result57);
	push_Expect(&dataStack, &result57);
	
	pop_ExpectAndReturn(&operatorStack, &xor);
	pop_ExpectAndReturn(&dataStack, &result57);
	pop_ExpectAndReturn(&dataStack, &num27);
	createNumberToken_ExpectAndReturn(34, &result34);
	push_Expect(&dataStack, &result34);

	pop_ExpectAndReturn(&operatorStack, &or);
	push_Expect(&operatorStack, &or);
	push_Expect(&operatorStack, &and);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&num30);
	push_Expect(&dataStack, &num30);
	
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	
	pop_ExpectAndReturn(&operatorStack, &and);
	pop_ExpectAndReturn(&dataStack, &num30);
	pop_ExpectAndReturn(&dataStack, &result34);
	createNumberToken_ExpectAndReturn(2, &result2);
	push_Expect(&dataStack, &result2);
	
	pop_ExpectAndReturn(&operatorStack, &or);
	pop_ExpectAndReturn(&dataStack, &result2);
	pop_ExpectAndReturn(&dataStack, &num266);
	createNumberToken_ExpectAndReturn(266, &result266);
	push_Expect(&dataStack, &result266);
	
	pop_ExpectAndReturn(&operatorStack, NULL);
	
	pop_ExpectAndReturn(&dataStack, &result266);
	
	Try{
		result = evaluate("266 | 27 ^ 28 + 29 & 30", &operatorStack, &dataStack);
	}Catch(e){
		TEST_FAIL_MESSAGE("Exception thrown");
	}
	
	TEST_ASSERT_EQUAL(266, result);
}

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
	
	pop_ExpectAndReturn(&dataStack, &num1);
	pop_ExpectAndReturn(&dataStack, &num3);
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
	
	pop_ExpectAndReturn(&dataStack, &num2);
	pop_ExpectAndReturn(&dataStack, &num10);
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
	
	pop_ExpectAndReturn(&dataStack, &num3);
	pop_ExpectAndReturn(&dataStack, &num10);
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