push 1
popr ax

next:

pushr ax
pushr ax
mul
out

pushr ax
push 1
add
popr ax

pushr ax
push 3
ja next:

hlt

