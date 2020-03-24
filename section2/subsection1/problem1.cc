/************************************************************
 *This program takes in an arithmetic expression, converts
 *it into postfix notation and then evaluates the expression.
 *This program can evaluate expressions that contain only the
 *following operators: +, -, *, /. Parenthesis are also taken
 *into account with the correct order of precedence.
 *
 *The following program WILL crash when an invalid infix
 *expression is given to it. Spaces in the input are ignored.
 ************************************************************/

#include<bits/stdc++.h>

namespace expression_evaluator
{
  std::string InfixToPostfix(std::string);
  int PostfixEvaluator(std::string);
  int Precedence(char);
  
  /************************************************************
   *std::string InfixToPostfix(std::string) :
   *Converts the input from infix notation to postfix notation.
   *
   *Input: expression in infix notation.
   *Output: expression in postfix notation.
   *
   *Additional comments:
   *The code for this function was
   *conceived after analysing the example given in the
   *following site:
   *https://scanftree.com/Data_Structure/infix-to-postfix
   *When an invalid infix expression in sent to this function,
   *it WILL crash. That is because this function cannot
   *verify whether the given infix expression is valid or not.
   ************************************************************/

  std::string InfixToPostfix(std::string input)
  {
    std::stack <char> operators;
    /*input_to_PostfixEvaluator has been initialized with a 
      size which is equal to the size of the input. This is
      because a string can't be initialized with a preallocated
      size.
    */
    std::string input_to_PostfixEvaluator (input.length(), 'x');
    int j = 0;

    /*The following code stores the operators in a stack and 
      stores in the operands in input_to_PostfixEvaluator.
      The operators are added to input_to_PostfixEvaluator
      once the order of precedence is taken care of.
    */

    for(int i = 0; i < input.length(); i++)
      {
	char element = input[i];

	if(element == ' ')
	  continue;

	if((int(element) >= 48)&&(int(element) <= 57))
	  {
	    input_to_PostfixEvaluator[j] = element;
	    j++;
	    continue;
	  }

	if(operators.empty())
	  operators.push(element);
	else
	  {
	    switch(element)
	      {
	      case '(':
		operators.push(element);
		break;
	      case ')':
		while(operators.top() != '(')
		  {
		    input_to_PostfixEvaluator[j] = operators.top();
		    operators.pop();
		    j++;
		  }
		operators.pop();
		break;
	      default:
		if(operators.top() == '(')
		  operators.push(element);
		else if(Precedence(element) < Precedence(operators.top()))
		  {
		    input_to_PostfixEvaluator[j] = operators.top();
		    j++;
		    operators.pop();
		    operators.push(element);
		  }
		else
		  operators.push(element);
	      }
	  }
      }

    while(!operators.empty())
      {
	input_to_PostfixEvaluator[j] = operators.top();
	j++;
	operators.pop();
      }
  
    return input_to_PostfixEvaluator;
  }      

  /************************************************************
   *int PostfixEvaluator(std::string) :
   *Evaluates a postfix expression.
   *
   *Input: An expression in postfix notation.
   *Output: The result obtained by evaluating the expression.
   *
   *Additional comments:
   *The exit function is invoked in this function when it
   *detects that the given postfix expression is invalid. But
   *this functionality is unused since the InfixToPostfix
   *function gives a valid postfix expression.
   ************************************************************/

  int PostfixEvaluator(std::string input)
  {
    std::stack <int> result;
    int input_size = input.length();
    for(int i = 0; i < input.length(); i++)
      if(input[i] == 'x')
	{
	  input_size = i;
	  break;
	}
  
    for(int i = 0; i < input_size; i++)
      {
	char element = input[i];

	if(int(element) == 32)
	  continue;
      
	if((int(element) >= 48)&&(int(element) <= 57))
	  result.push(element-48);
      
	else
	  {
	    if(result.empty())
	      {
		std::cout << "nan" << std::endl;
		exit;
	      }
	  
	    int b = result.top();
	    result.pop();
	  
	    if(result.empty())
	      {
		std::cout << "nan" << std::endl;
		exit;
	      }
	  
	    int a = result.top();
	    result.pop();
	  
	    switch(element)
	      {
	      case 43:
		a = a + b;
		break;
	      case 45:
		a = a - b;
		break;
	      case 42:
		a = a * b;
		break;
	      case 47:
		a = a / b;
		break;
	      }
	  
	    result.push(a);	  
	  }
      }

    int output = result.top();
    result.pop();

    if(result.empty())
      return output;
    else
      {
	std::cout << "nan" << std::endl;
	exit;
      }
  }
  /************************************************************
   *int Precedence(char) :
   *Gives the precedence of the given operator.
   *
   *Input: an operator.
   *Output: the precedence of the operator quantified into a
   *number.
   *
   *Additional comments:
   *The precedence of '+' and '-' is less than the precedence
   *of '*' and '/'. The precedence of '+' is equal to the 
   *precedence of '-'. And it the case with '*' and '/' too.
   *So any set of numbers can be used to quantify the 
   *precedence of these operators, given that the above rules
   *are satisfied.
   ************************************************************/

  int Precedence(char symbol)
  {
    switch(symbol)
      {
      case '+':
	return 1;
	break;
      case '-':
	return 1;
	break;
      case '*':
	return 2;
	break;
      case '/':
	return 2;
	break;
      }
  }

} // namespace expression_evaluator

/************************************************************
 *int main() :
 *Calls the required functions InfixToPostfix and 
 *PostfixEvaluator and also print the output.
 ************************************************************/

int main()
{
  std::string input;
  std::cout << "Enter the arithmetic expression to be evaluated:" << std::endl;
  std::getline(std::cin, input);

  std::string input_to_PostfixEvaluator = expression_evaluator::InfixToPostfix(input);

  int output = expression_evaluator::PostfixEvaluator(input_to_PostfixEvaluator);

  std::cout << "The result is: " << output << std::endl;

  return 0;
}
