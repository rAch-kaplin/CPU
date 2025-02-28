push 1
pop ax

next:

push ax
push ax
mul
out

push ax
push 1
add
pop ax

push ax
push 3
ja next:

hlt

