call main:
hlt

main:
        in
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
