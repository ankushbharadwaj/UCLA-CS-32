//
//  eval.cpp
//  hwk 2 part 1
//
//  Created by Ankush Bharadwaj on 4/30/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <cassert>

using namespace std;

//---------------------------------DECLARE ADDITIONAL FUNCTIONS--------------------------------------------------//
string noSpaces(string infix);  // Removes all spaces from the infix
bool isValid(string infix); // Checks if infix is valid
int precedence(char ch); // Assumes valid, and evaluates the precedence of !, & and |
string convertInfixToPostfix(string infix, string& postfix); // Assumes valid and converts from infix to postfix

//--------------------------------------EVALUATE() IMPLEMENTATION------------------------------------------------//
int evaluate(string infix, string& postfix, bool& result)
{
    if (isValid(infix))
    {
        postfix = convertInfixToPostfix(infix, postfix);
        if (postfix.empty())
            return 1;
        stack<bool> operandStack;
        for (int i = 0; i < postfix.length(); i++)
        {
            char ch = postfix[i];
            if (ch == 'T')
                operandStack.push(true);
            else if (ch == 'F')
                operandStack.push(false);
            else if(ch == '!')
            {
                bool temp = operandStack.top();
                operandStack.pop();
                operandStack.push(!temp);
            }
            else
            {
                bool operand2 = operandStack.top();
                operandStack.pop();
                if (operandStack.empty()) {
                    result = operand2;
                    return 0;
                }
                bool operand1 = operandStack.top();
                operandStack.pop();
                if (postfix[i] == '^')
                {
                    if (operand1 ^ operand2)
                        operandStack.push(true);
                    else
                        operandStack.push(false);
                }
                if (postfix[i] == '|')
                {
                    if (operand1 || operand2)
                        operandStack.push(true);
                    else
                        operandStack.push(false);
                }
                if (postfix[i] == '&')
                {
                    if (operand1 && operand2)
                        operandStack.push(true);
                    else
                        operandStack.push(false);
                }
            }
        }
        result = operandStack.top();
        return 0;
    }
    return 1;
}

//----------------------------------IMPLEMENT ADDITIONAL FUNCTIONS-----------------------------------------------//
string noSpaces(string infix)
{
    string infix_nospaces = "";
    for (int i = 0; i < infix.size(); i++)
        if (infix[i] != ' ')
            infix_nospaces += infix[i];
    return infix_nospaces;
}


bool isValid(string infix)
{
    stack<char> parenStack;
    string temp_infix = noSpaces(infix);
    for (int i = 0; i < temp_infix.size(); i++)
    {
        if (temp_infix[temp_infix.size() - 1] == '|' || temp_infix[temp_infix.size() - 1] == '&' || temp_infix[temp_infix.size() - 1] == '^')
            return false;
        if (temp_infix[i] == '|' || temp_infix[i] == '&' || temp_infix[i] == '^')
        {
            
            if ((temp_infix[i-1] != 'T' && temp_infix[i-1] != 'F' && temp_infix[i-1] != ')') || ((temp_infix[i+1]) !='T' && temp_infix[i+1] !='F' && temp_infix[i+1] !='!'&& temp_infix[i+1] !='('))
                return false;
        }
        else if (temp_infix[i] == 'T' || temp_infix[i] == 'F')
        {
            if (temp_infix[i+1] == 'T' || temp_infix[i+1] == 'F' || temp_infix[i+1] == '(' || temp_infix[i+1] == '!')
                return false;
        }
        
        if ( temp_infix[i] == '('){
            parenStack.push('(');
            if (temp_infix[i+1] == ')')
                return false;
        }
        if ( temp_infix[i] == ')' && !parenStack.empty()) {
            parenStack.pop();
        }
        else if (temp_infix[i] == ')' && parenStack.empty())
            return false;
    }
    if (!parenStack.empty())
        return false;
    return true;
}

int precedence(char ch)
{
    switch (ch)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        case '|':
            return 0;
        default:
            return -1;
    }
}


string convertInfixToPostfix(string infix, string& postfix)
{
    postfix = "";
    stack<char> operatorStack;
    string temp_infix = noSpaces(infix);
    for (int i = 0; i < temp_infix.size(); i++)
    {
        char ch = temp_infix[i];
        switch (ch)
        {
            case 'T':
            case 'F':
                postfix += ch;
                break;
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                while (operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '!':
            case '&':
            case '^':
            case '|':
                while (!operatorStack.empty() && operatorStack.top() != '(' &&
                       precedence(ch) <= precedence(operatorStack.top()))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
            default:
                break;
        }
    }
    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return postfix;
}

//------------------------------------------MAIN AND TEST CASES--------------------------------------------------//
int main()  //Test cases
{
    

    
    string pf;
    bool answer;
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|" && answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("T", pf, answer) == 0 && answer);
    assert(evaluate("(F)", pf, answer) == 0 && !answer);
    assert(evaluate("T&(F)", pf, answer) == 0 && !answer);
    assert(evaluate("T & !F", pf, answer) == 0 && answer);
    assert(evaluate("!(F|T)", pf, answer) == 0 && !answer);
    assert(evaluate("!F|T", pf, answer) == 0 && answer);
    assert(evaluate("T|F&F", pf, answer) == 0 && answer);
    assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 && answer);
    assert(evaluate("F!", pf, answer) == 1);
    assert(evaluate("!F", pf, answer) == 0 && answer);
    
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 0);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    
    
    cout << "Passed all tests" << endl;
}
