call main:
hlt
;------------------------------------------

main:
        in
        call fib:
        push bx
        out
ret
;-------------------------------------------

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
;-------------------------------------------

start cycle:
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

;-------------------------------------------

basic_fib:
        push 1
        pop bx
        jmp exit_in_main:

;-------------------------------------------

new_iteration:
        push dx
        push cx
        ja exit_in_main:
        jmp start_iteration:
;---------------------------------


