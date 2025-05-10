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
