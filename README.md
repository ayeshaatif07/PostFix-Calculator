# Postfix Calculator

A stack-based calculator that evaluates postfix (reverse Polish) expressions, with support for variables. It is implemented twice: in **JavaScript** (Node.js) and in **C++**.

## Features

- Arithmetic operators: `+`, `-`, `*`, `/` on real numbers.
- Variables named `A` to `Z`, assigned with `=` and reused in later expressions.
- Shows the current stack after every line.
- Error handling for not enough operands, division by zero, invalid assignments and invalid tokens.
- Interactive prompt that runs until you enter `q`.

## How It Works

Each line is split into tokens separated by single spaces and processed left to right. Numbers are pushed onto the stack. An operator pops the top two values, applies the operation and pushes the result. A variable pushes its stored value, or the variable name itself if it has no value yet. `=` pops a value and a variable name and stores the value in the variable.

## Examples

```
>> 5 3 +
> [8]
>> A 10 =
> []
>> A 5 *
> [50]
>> 4 0 /
Error: Division by zero
>> q
```

## Project Structure

| File | Purpose |
|------|---------|
| `src1.js` | JavaScript implementation (Node.js, uses `readline` for input) |
| `src.cpp` | C++ implementation |
| `Answers_PostFixCalc.pdf` | Written answers for the assignment |
| `VideoTest.mp4` | Recorded test of the calculator |

## Run the JavaScript Version

Requires [Node.js](https://nodejs.org/).

```bash
git clone https://github.com/ayeshaatif07/PostFix-Calculator.git
cd PostFix-Calculator
node src1.js
```

## Run the C++ Version

Requires a C++ compiler such as `g++` or `clang++`.

```bash
g++ -std=c++17 -o postfix src.cpp
./postfix
```

On macOS, if the build fails with `'iostream' file not found`, add `-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1` to the `g++` command.

## Usage Notes

- Separate every token with exactly one space, for example `5 3 +`.
- Enter `q` to quit.
