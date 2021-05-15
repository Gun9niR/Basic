# Basic Interpreter

A trivial interpreter implemented with AST.

## Installation

- Build within Qt

## Statements, Expressions and Commands

Check the [documentation for version 1](https://github.com/Gun9niR/Basic/blob/master/docs/Basic-doc.pdf) and [document for version 2](https://github.com/Gun9niR/Basic/blob/master/docs/Mini%20Basic%20v2.0.pdf) for valid statements, expressions and commands.

## Behaviour Specification (IMPORTANT)

The documentation describes the fundamental behaviours of the interpreter, but lots of details are neglected. Also, I've made a bit of modification to the interface to make it more usable.

- UI modification: A text browser named “报错、提示信息” is added to display error message and extra information, such as message of successful execution.
- Context system: In my implementation of Basic interpreter, there's no program-specific context. That is to say, all variables are defined in a **global context**, so it's perfectly fine if you define `x` in a program and use it in another. Only by runnning the `CLEAR` command can you clear all variables in the gloabal context.
- Instruction input: Only five statements: `INPUT`, `INPUTS`, `LET`，`PRINT` and `PRINTF` can be entered without a preceding line number **when entered from the console, not from a file**. The rest of the statements require a line number at the beginning, otherwise they cannot be stored in “代码” section.
- Syntax tree visualization: The syntax tree is generated when executing the `RUN` command. All of the statements that is stored in “代码” will be scanned, parsed and visualized in “语句与语法树” section. On encountering any error, an error message will replace the syntax tree, pointing out what exactly is the problem.
- Division: All numbers are treated as integers, so division works like that in C++, where `3/5` produces `0`.
- Variable naming: Variables must start with a letter or underscore.
- Variables display: Variables are displayed in the order of assignment.
- Line number range: Line number falls in the interval of $[1, 1000000]$. Preceding $0$s are allowed.
- Negative sign: `-` doesn't have to be nested in a pair of parentheses. For example, `3 + -5` yields `-2`, not an error.
- Code deletion: To delete a line of code, input the line number in console, without any following statement. Note that the line number must exist.

## Error Handling

This section lists all kinds of errors that the interpreter can detect in each stage of execution.

### Scanning

- Detect invalid character. Valid characters include letters (upper and lower case), mathmatical operands (+ - * / < > =), underscore, parenthesis, space, `\n`, `\t`, `\r`, `\n`.The only exception is the `REM` statement, where you can input anything as its content.

### Parsing

- Detect syntax error.

### Interpreting

- Detect undefined variable.
- Detect invalid jump destination.
- Detect division by zero.
- Detect invalid input in `INPUT` and `INPUTS` statement.
- Detect multiple statements in a line (which is not allowed in my implementation).
- Detect power(0, 0). By mathmatical definitions, power(0, 0) invalid.

## Design notes

### Algorithm to build AST

I use **recursive descent parsing** to build the syntax tree. The grammar is as follows.

```text
expression      ->  addition
addition        ->  multiplication (("+" | "-") multiplication)*
multiplication  ->  power (("*" | "/" power)*
unaryPower      ->  ("-" unaryPower) | power
power           ->  unary ("**" power)?
unary           ->  (("-") unary) | primary
primary         ->  NUMBER | STRING | ("("expression")")
```

### Code detials

- Singleton pattern: make `Basic` and `MainWindow` accessible to all files, avoiding useage of any `extern` keyword.
- `shared_ptr`: There's no native pointer in my program. `shared_ptr` handles all memory management.
