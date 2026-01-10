/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:42:32 by dpaluszk          #+#    #+#             */
/*   Updated: 2026/01/10 13:53:13 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
 
RPN::RPN(void)
{}

RPN::RPN(const std::string &input) : input(input)
{}

RPN::RPN(RPN const &copy)
{
    *this = copy;
}

RPN &RPN::operator=(RPN const &copy)
{
    if (this != &copy)
    {
        this->input = copy.input;
    }
    return *this;
}

RPN::~RPN(void)
{}

int RPN::evaluate(void)
{
    std::istringstream iss(input);
    std::stack<int> stack;
    std::string token;

    while(iss >> token)
    {
        if (token.length() == 1 && isdigit(token[0]))
        {
            stack.push(token[0] - '0');
        }
        else if (token.length() == 1 && (token[0] == '+' || token[0] == '-' ||
                  token[0] == '*' || token[0] == '/'))
        {
            if (stack.size() < 2)
            {
                throw std::runtime_error("Invalid expression: not enough operands");
            }
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            switch (token[0])
            {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    if (b == 0)
                    {
                        throw std::runtime_error("Division by zero");
                    }
                    stack.push(a / b);
                    break;
            }
        }
        else
        {
            throw std::runtime_error("Invalid token: " + token);
        }
    }

    if stack.size() != 1
    {
        throw std::runtime_error("Invalid expression: too many operands");
    }
    return stack.top();
}
