// DS exp3_1.cpp: 定义控制台应用程序的入口点。
//

# include <stdio.h>
# include <iostream>
using namespace std;
#define SIZE 100

int *input(char *str, int *InExp)
{
	int i = 0, j = 0;
	int temp = 0;

	printf("Enter the formula and end with #\n");
	scanf("%s", str);

	for (i = 0;str[i] != 0;i++) {
		if (str[i] >= '0' && str[i] <= '9') { //当数组中当前元素为数字时
			temp = temp * 10 + str[i] - '0';
			if (str[i + 1] < '0' || str[i + 1] > '9') { //如果下一位就不是数字了，就把当前temp里的数字写入
				InExp[j] = temp;
				j++;
				temp = 0; //初始化tmp
			}
		}
		else {
			InExp[j] = str[i] - '0'; //当数组中当前元素是字符时，写入该元素的ACSCII码减去‘0’的，使其为负数
			j++;
		}
	}
	return InExp;
}

int push(int * a, int top, int elem) 
{
	top++;
	a[top] = elem;
	return top;
}

int pop(int * a, int top) 
{
	if (top == -1) {
		printf("Stack is empty");
		return -1;
	}
	top--;
	return top;
}

int push_float(float * a, int top, float elem)
{
	top++;
	a[top] = elem;
	return top;
}

int pop_float(float * a, int top)
{
	if (top == -1) {
		printf("Stack is empty");
		return -1;
	}
	top--;
	return top;
}

int *converse(int *InExp, int *PostExp) //转换函数，将中缀表达式转化为后缀表达式
{
	int stack_cvs[SIZE];
	int top_cvs = -1;
	int i = 0, j = 0;

	for (i = 0; InExp[i] != 0;i++) {

		//当前元素为数字，写入后缀表达式
		if (InExp[i] > 0) {
			PostExp[j] = InExp[i];
			j++;
		}
		//当前元素为'*'，'/'或'('，直接push入操作符栈
		else if (InExp[i] == '*' - '0' || InExp[i] == '/' - '0' || InExp[i] == '(' - '0') {
			top_cvs = push(stack_cvs, top_cvs, InExp[i]);
		}
		//当前元素为')'，依次pop出栈顶操作符，输出到后缀表达式尾端，直至pop得到的是一个'('才停止，并丢弃该'('
		else if (InExp[i] == ')' - '0') {
			while (stack_cvs[top_cvs] != '(' - '0') {
				PostExp[j] = stack_cvs[top_cvs];
				j++;
				top_cvs = pop(stack_cvs, top_cvs);
			}
			top_cvs = pop(stack_cvs, top_cvs); //丢弃该'('
		}
		//当前元素为'+'或'-'，依次pop出栈顶操作符输出到后缀表达式尾端，直至栈空或pop得到了一个'('
		//达到这两个条件之一后，将此操作符入栈
		else if (InExp[i] == '+' - '0' || InExp[i] == '-' - '0') {
			while (top_cvs != -1 && stack_cvs[top_cvs] != '(' - '0') {
				PostExp[j] = stack_cvs[top_cvs];
				j++;
				top_cvs = pop(stack_cvs, top_cvs);
			}
			top_cvs = push(stack_cvs, top_cvs, InExp[i]); //将此操作符（'+'或'-'）入栈
		}
		//如果当前中缀元素为'#'，则依次pop出栈顶操作符输出到后缀表达式尾端，直至栈底（栈空）
		else if (InExp[i] == '#' - '0') {
			while (top_cvs != -1) {
				PostExp[j] = stack_cvs[top_cvs];
				j++;
				top_cvs = pop(stack_cvs, top_cvs);
			}
		}
	}
	return PostExp;
}

float calculate(int *PostExp)
{
	float stack_cal[SIZE];
	int top_cal = -1;
	int i = 0, j = 0;

	for (i = 0; PostExp[i] != 0;i++) {

		//当前元素为数字，入栈
		if (PostExp[i] > 0) {
			top_cal = push_float(stack_cal, top_cal, PostExp[i]);
		}
		//当前元素为符号，将栈顶元素两个出栈计算后将结果入栈
		else {
			if (PostExp[i] == '+' - '0') {
				float a = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				float b = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				top_cal = push_float(stack_cal, top_cal, a + b);
			}
			if (PostExp[i] == '-' - '0') {
				float a = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				float b = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				top_cal = push_float(stack_cal, top_cal, b - a);
			}
			if (PostExp[i] == '*' - '0') {
				float a = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				float b = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				top_cal = push_float(stack_cal, top_cal, a * b);
			}
			if (PostExp[i] == '/' - '0') {
				float a = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				float b = stack_cal[top_cal];
				top_cal = pop_float(stack_cal, top_cal);
				top_cal = push_float(stack_cal, top_cal, b / a);
			}
		}
	}
	return stack_cal[top_cal];
}

int main()
{
	int pInExp[SIZE] = { 0 };
	int pPostExp[SIZE] = { 0 };
	char str[SIZE] = { 0 };

	int *InExp = input(str, pInExp);
	int *PostExp = converse(InExp, pPostExp);
	float answer = calculate(PostExp);
	printf("the answer is:\n");
	cout << answer << endl;

	return 0;
}
