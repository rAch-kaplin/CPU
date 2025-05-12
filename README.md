# Stack-Based Processor

It is a stack-based processor emulator with its own assembler supported. 

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Commands](#commands)
- [Build and Run](#build-and-run)
- [Syntax examples](#syntax-examples)
- [Examples](#examples)

## Overview

This project implements a stack-based processor with its own assembly language. It includes:
- Register operations
- Stack operations
- RAM access
- Conditional jumps
- Function calls

## Features

- 21 different commands
- 3 argument types:
  - Immediate values
  - Register references
  - Memory addresses (RAM)
- Support for functions/methods (`call` and `ret` commands)
- Colorful terminal output (see [color logo](img/color-log.png))

## Commands

<details>
<summary>Show available commands</summary>

| Command | Description | Arguments |
|---------|-------------|-----------|
| `push`  | Push value to stack | Register or memory |
| `pop`   | Pop value from stack | Register or memory |
| `add`   | Add top two stack values | None |
| `sub`   | Subtract top two stack values | None |
| `mul`   | Multiply top two stack values | None |
| `div`   | Divide top two stack values | None |
| `sqrt`  | Square root of top stack value | None |
| `sin`   | Sine of top stack value | None |
| `cos`   | Cosine of top stack value | None |
| `out`   | Output top stack value | None |
| `in`    | Input value to stack | None |
| `hlt`   | Halt execution | None |
| `jmp`   | Unconditional jump | Label |
| `jb`    | Jump if below | Label |
| `jbe`   | Jump if below or equal | Label |
| `ja`    | Jump if above | Label |
| `jae`   | Jump if above or equal | Label |
| `je`    | Jump if equal | Label |
| `jne`   | Jump if not equal | Label |
| `call`  | Call function | Label |
| `ret`   | Return from function | None |

</details>

## Build and Run

1. Clone the repository:
```bash
git clone git@github.com:rAch-kaplin/CPU.git
make all
./build/bin/asm -f "file_asm.asm"
./build/bin/proc

For colored output:
./build/bin/proc -m COLOR_MODE
```
### Syntax example
```
push ax           ; push value from ax register to stack
pop [bx + 1]      ; pop value from stack to RAM to address from register bx + 1
jmp label:        ; jump to label named "label"
jbe label:        ; jump if the condition <= is true
```
#### Jumps

You need to specify label in code. Then you can give it to jump function, and it will jump on this label.
P.S.
```
jmp next:
...
next:
```
```
call main:

main:
...
ret
```

## Sample programs
<details>
<summary>Quadratic equation solver</summary>

```
call main:
hlt

main:
    call input_coef:
    push ax
    push 0
    je linear_square:

    call count_discr:
    call check_discr:
ret

input_coef:
    in
    in
    in
    pop cx
    pop bx
    pop ax
ret

count_discr:
    push bx
    push bx
    mul
    push 4
    push ax
    mul
    push cx
    mul
    sub
    pop dx
ret

check_discr:
    push dx
    push 0
    je one_root:
    push dx
    push 0
    jb no_roots:
    jmp two_root:

linear_square:
    push cx
    push bx
    div
    out
ret

one_root:
    push 0
    push bx
    sub
    push 2
    push ax
    mul
    div
    out
ret

no_roots:
    push 9999
    out
ret

two_root:
    push 0
    push bx
    sub
    push dx
    sqrt
    sub
    push 2
    push ax
    mul
    div
    out

    push 0
    push bx
    sub
    push dx
    sqrt
    add
    push 2
    push ax
    mul
    div
    out
ret
```
</details>

<details> <summary>Recursive factorial</summary>
```
call main:
hlt

main:
        in
        pop ax
        call fact:
        push bx
        out
ret

fact:
        push ax
        push 1
        jbe exit_fact:

        push ax
        push ax
        push 1
        sub
        pop ax
        call fact:

        push bx
        mul
        pop bx

        reverse_step:
ret

exit_fact:
        push 1
        pop bx
        jmp reverse_step:
```
</details>

<details> <summary>Fibonacci</summary>
```
call main:
hlt

main:
        in
        pop ax
        call fib:
        push bx
        out
ret

fib:
        push ax
        push 2
        jbe basic_fib:

        push ax
        push 2
        sub
        pop dx
        push 1
        pop cx

        push 1
        push 1
        pop ax
        pop bx

        jmp new_iteration:
        start_iteration:
        jmp start_cycle:

        exit_in_main:
ret

start_cycle:
        push ax
        push bx
        add
        push bx
        pop ax
        pop bx

        push cx
        push 1
        add
        pop cx
        jmp new_iteration:


basic_fib:
        push 1
        pop bx
ret


new_iteration:
        push dx
        push cx
        jae start_iteration:
        jmp exit_in_main:

```
</details>
