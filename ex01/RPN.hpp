#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>

class RPN 
{
    private:
        std::string input;
        
    public:
        RPN(void);
        RPN(const std::string &input);
        RPN(RPN const &copy);
        RPN &operator=(RPN const &copy);
        ~RPN(void);

        int evaluate(void);
};

#endif
