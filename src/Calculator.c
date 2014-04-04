#include <stdio.h>
#include <String.h>
#include "CException.h"
#include "Token.h"
#include "Stack.h"
#include "Error.h"
#include "Calculator.h"

void tryEvaluateOperatorsOnStackThenPush(Stack *operatorStack, Stack *dataStack, OperatorToken *operator){
	
}

void evaluateOperator(Stack *dataStack, OperatorToken *operator){
	NumberToken *result;
	NumberToken *left = pop(dataStack);
	NumberToken *right = pop(dataStack);
	
	if(strcmp(operator->name, "+") == 0){
		result = createNumberToken(left->value + right->value);
	}
	else if(strcmp(operator->name, "-") == 0){
		result = createNumberToken(left->value - right->value);
	}
	else if(strcmp(operator->name, "*") == 0){
		result = createNumberToken(left->value * right->value);
	}
	else if(strcmp(operator->name, "/") == 0){
		result = createNumberToken(left->value / right->value);
	}
	else if(strcmp(operator->name, "%") == 0){
		result = createNumberToken(left->value % right->value);
	}
	else if(strcmp(operator->name, "^") == 0){
		result = createNumberToken(left->value ^ right->value);
	}
	else if(strcmp(operator->name, "&") == 0){
		result = createNumberToken(left->value & right->value);
	}
	else if(strcmp(operator->name, "|") == 0){
		result = createNumberToken(left->value | right->value);
	}
	
	push(dataStack, result);
}