call main:
hlt

main:
        in
        call fact:
        pushr bx
        out
ret

fact:
        pushr ax
        push 1
        jbe exit_fact:

        pushr ax
        pushr ax
        push 1
        sub
        popr ax
        call fact:

        pushr bx
        mul
        popr bx

        reverse_step:
ret

exit_fact:
        push 1
        popr bx

        jmp reverse_step:
