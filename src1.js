// JavaScript implementation of Postfix Calculator
class PostfixCalculator {
    constructor() {
        // Stack to keep track of numbers and variables during calculation
        this.calculationStack = [];
         // Table to store variable values
        this.symbolTable = {};
    }

    // Check if the token is an operator (+, -, *, /, =)
    isOperator(token) {
        return token === "+" || token === "-" || token === "*" || token === "/" || token === "=";
    }

    // Check if the token is a valid single-letter variable (e.g., A-Z)
    isVariable(token) {
        return token.length === 1 && token >= 'A' && token <= 'Z';
    }

    // Perform basic math operations (+, -, *, /)
    performOperation(op) {
        if (this.calculationStack.length < 2) {
            throw new Error("Not enough operands for operation");
        }

        const b = this.calculationStack.pop();  // Get the second number
        const a = this.calculationStack.pop();  // Get the first number

        if (op === "+") {
            return a + b;
        } else if (op === "-") {
            return a - b;
        } else if (op === "*") {
            return a * b;
        } else if (op === "/") {
            if (b === 0) {
                throw new Error("Division by zero");
            }
            return a / b;
        } else {
            throw new Error("Unknown operator");
        }
    }

    // Handle each token (number, operator, or variable)
    processToken(token) {
        if (this.isVariable(token)) {
             // Push variable value onto stack if it exists
            if (this.symbolTable.hasOwnProperty(token)) {
                this.calculationStack.push(this.symbolTable[token]);
            } else {
                // Push the variable itself if not defined yet
                this.calculationStack.push(token);
            }
        } else if (this.isOperator(token)) {
            if (token === "=") {
                // Assignment operation
                if (this.calculationStack.length < 2) {
                    throw new Error("Invalid assignment operation");
                }

                const value = this.calculationStack.pop();
                const variable = this.calculationStack.pop();

                if (typeof variable === "string" && variable >= 'A' && variable <= 'Z') {
                    this.symbolTable[variable] = value;
                } else {
                    throw new Error("Invalid variable name");
                }
            } else {
                // Perform arithmetic operation
                const result = this.performOperation(token);
                this.calculationStack.push(result);
            }
        } else {
             // Try to parse the token as a number
            const value = parseFloat(token);

            if (isNaN(value)) {
                throw new Error(`Invalid token: ${token}`);
            }

            this.calculationStack.push(value);
        }
    }

    // Process a whole line of input
    processLine(line) {
        this.calculationStack = [];  // Clear stack for new calculation
        const tokens = line.split(" ");  // Split line into tokens

        for (const token of tokens) {
            this.processToken(token);   // Process each token
        }
    }

    // Display the current stack
    printStack() {
        if (this.calculationStack.length === 0) {
            console.log("> []");  // Empty stack
        } else {
            console.log("> [" + this.calculationStack.join(" ") + "]");  // Stack contents
        }
    }
}

// Create readline interface for user input
const readline = require("readline").createInterface({
    input: process.stdin,
    output: process.stdout
});

// Create an instance of the calculator
const calc = new PostfixCalculator();

console.log("Postfix++ Calculator (enter expressions, 'q' to quit)");

const prompt = () => {
    readline.question(">> ", (line) => {
        if (line === "q") {
            readline.close();
            return;
        }

        try {
            calc.processLine(line);  // Process user input
            calc.printStack();   // Show the stack
        } catch (error) {
            console.error("Error:", error.message);
        }

        prompt();  // Keep asking for input
    });
};

prompt();