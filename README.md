# Basic Interpreter

## Instruction Input

- Skip instruction with no line number (with alert)
- Skip empty instruction (with alert)
- Neglect empty line
- Instruction with the same line number will overwrite the old one
- Instruction can only be input from the input box or from the file

## Error Handling

### Scanning

- Detect invalid character (except for comment)

### Parsing

- Detect non-statement code or grammar error

### Interpreting

- Detect undefined variable
- Detect invalid jump destination
- Detect division by zero

## Todo

### Commands

- [x] RUN
- [x] LOAD
- [x] CLEAR
- [] HELP (message box)
- [x] QUIT

### Console

- [x] Read a line
- [x] Input variable
- [x] Display error message

## Expression grammar

```text
expression      ->  addition
addition        ->  multiplication (("+" | "-") multiplication)*
multiplication  ->  power (("*" | "/" power)*
unaryPower      ->  ("-" unaryPower) | power
power           ->  unary ("**" power)?
unary           ->  (("-") unary) | primary
primary         ->  NUMBER | ("("expression")")
```

## Design notes

- Singleton pattern: make `Basic` and `MainWindow` globally accessable to all files
- Visitor pattern: did not use it because it warrants public accessibility of expr properties, and add more function calls (2 more calls for each expr and stmt)
- `shared_ptr` extensive use of it avoid excessive pass by value
