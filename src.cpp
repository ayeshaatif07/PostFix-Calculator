#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
using namespace std;

/*
 * PostfixCalculator - A class that evaluates postfix expressions
 * 
 * This calculator supports:
 * - Basic arithmetic operations (+, -, *, /)
 * - Variable assignment and retrieval (using uppercase letters A-Z)
 * - Stack-based calculation with real numbers
 * - Error handling for invalid expressions and operations
 * 
 *  Example usage:
 * "5 3 +" -> [8]        // Basic arithmetic
 * "A 10 =" -> []        // Assign 10 to variable A
 * "A 5 *" -> [50]       // Use variable in calculation
 */

class PostfixCalculator 
{
    private:
        stack<double> calculationStack;
        map<char, double> symbolTable;

        //Checks if the given token is a valid arithmetic operator (+, -, *, /, =)
        bool isOperator(const string& token) 
        {
            return token == "+" || token == "-" || token == "*" || token == "/" || token == "=";
        }

        //Checks if the given token is a valid variable name (A-Z)
        bool isVariable(const string& token) 
        {
            return token.length() == 1 && token[0] >= 'A' && token[0] <= 'Z';
        }

        //Performs the arithmetic operation specified by the given operator
        //Throws an error if there are not enough operands for the operation
        double performOperation(const string& op) 
        {
            if (calculationStack.size() < 2)
                throw runtime_error("Not enough operands for operation");

            double b = calculationStack.top(); calculationStack.pop();
            double a = calculationStack.top(); calculationStack.pop();

            if (op == "+") return a + b;
            if (op == "-") return a - b;
            if (op == "*") return a * b;
            if (op == "/") 
            {
                if (b == 0) throw runtime_error("Division by zero");
                return a / b;
            }
            throw runtime_error("Unknown operator");
        }

    public:
        //Processes a single token and performs the appropriate action
        //Throws an error if the token is invalid or if there is an error during processing
        void processToken(const string& token) 
        {
            try 
            {
                if (isVariable(token)) 
                {
                    // If variable exists, push its value; if not, push the variable itself
                    auto it = symbolTable.find(token[0]);
                    if (it != symbolTable.end())
                        calculationStack.push(it->second);
                    else
                        calculationStack.push(token[0]);
                }
                else if (isOperator(token)) 
                {
                    if (token == "=") 
                    {
                        if (calculationStack.size() < 2)
                            throw runtime_error("Invalid assignment operation");
                        double value = calculationStack.top(); calculationStack.pop();
                        double var = calculationStack.top(); calculationStack.pop();
                        char varName = static_cast<char>(var);
                        if (varName >= 'A' && varName <= 'Z')
                            symbolTable[varName] = value;
                        else
                            throw runtime_error("Invalid variable name");
                    } 
                    else 
                    {
                        double result = performOperation(token);
                        calculationStack.push(result);
                    }
                }
                else 
                {  // Must be a number
                    try 
                    {
                        double value = stod(token);
                        calculationStack.push(value);
                    }
                    catch (const invalid_argument&) 
                    {
                        throw runtime_error("Invalid token: " + token);
                    }
                }
            }
            catch (const exception& e) 
            {
                while (!calculationStack.empty()) calculationStack.pop();
                throw;
            }
        }

        //Processes a line of input and evaluates the postfix expression
        void processLine(const string& line) 
        {
            // Clear stack before processing new line
            while (!calculationStack.empty()) 
                calculationStack.pop();

            istringstream iss(line);
            string token;
            
            while (iss >> token)
                processToken(token);
        }

        //Prints the current state of the calculation stack
        //If the stack is empty, prints an empty bracket pair
        void printStack() const 
        {
            if (calculationStack.empty()) 
            {
                cout << "> []" << endl;
                return;
            }

            stack<double> temp = calculationStack;
            cout << "> [";
            bool first = true;
            string output;
            while (!temp.empty()) 
            {
                if (!first) output = " " + output;
                output = to_string(temp.top()) + output;
                first = false;
                temp.pop();
            }
            // Remove trailing zeros and decimal point if not needed
            for (size_t i = 0; i < output.length(); i++) 
            {
                if (output[i] == '.') 
                {
                    size_t j = output.length() - 1;
                    while (j > i && output[j] == '0') j--;
                    if (j == i) j--;
                    output = output.substr(0, j + 1);
                    break;
                }
            }
            cout << output << "]" << endl;
        }
};

//Main function to run the calculator
int main() 
{
    PostfixCalculator calc;
    string line;

    cout << "Postfix++ Calculator (enter expressions, 'q' to quit)" << endl;
    while (true) {
        cout << ">> ";
        getline(cin, line);

        if (line == "q") break;

        try 
        {
            calc.processLine(line);
            calc.printStack();
        }
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }
    return 0;
}