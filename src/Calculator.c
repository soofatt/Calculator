#include <stdio.h>
#include <String.h>
#include "CException.h"
#include "Token.h"
#include "Stack.h"
#include "Error.h"
#include "Calculator.h"

int evaluate(char *expression, Stack *operatorStack, Stack *dataStack){
	Tokenizer *tokenizer;
	NumberToken *number;
	NumberToken *resultNumber;
	OperatorToken *operator;
	
	tokenizer = tokenizerNew(expression);
	
	while(1){
		number = (NumberToken *)nextToken(tokenizer);
		
		if(number != NULL){
			if(number->type != NUMBER_TOKEN){
				Throw(ERR_NOT_DATA);}
			else{
				printf("num: %d\n", number->value);
				push(dataStack, number);}
		}
		
		else if(number == NULL)
			Throw(ERR_INVALID_EXPRESSION);
		
		operator = (OperatorToken *)nextToken(tokenizer);
		
		if(operator != NULL){
			if(operator->type != OPERATOR_TOKEN)
				Throw(ERR_NOT_OPERATOR);
			else{
				printf("op: %s\n", operator->name);
				tryEvaluateOperatorsOnStackThenPush(operatorStack, dataStack, operator);}
		}
		
		else if(operator == NULL)
			break;
	}
	evaluateAllOperatorsOnStack(operatorStack, dataStack);
	resultNumber = pop(dataStack);
	
	return resultNumber->value;
}

void tryEvaluateOperatorsOnStackThenPush(Stack *operatorStack, Stack *dataStack, OperatorToken *operator){
	OperatorToken *opToken;
	
	opToken = pop(operatorStack);
	
	while(opToken != NULL){
		if(opToken->precedence >= operator->precedence){
			evaluateOperator(dataStack, opToken);
		}
		else{
			push(operatorStack, opToken);
			break;
		}
		opToken = pop(operatorStack);	
	}
	push(operatorStack, operator);
}

void evaluateAllOperatorsOnStack(Stack *operatorStack, Stack *dataStack){
	OperatorToken *opToken;
	
	opToken = pop(operatorStack);
	
	while(opToken != NULL){
		evaluateOperator(dataStack, opToken);
		opToken = pop(operatorStack);
	}
}

void evaluateOperator(Stack *dataStack, OperatorToken *operator){
	NumberToken *result;
	NumberToken *right = pop(dataStack);
	NumberToken *left = pop(dataStack);
	
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