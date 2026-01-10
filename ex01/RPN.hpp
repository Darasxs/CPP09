#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <cctype>
# include <stdexcept>

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
