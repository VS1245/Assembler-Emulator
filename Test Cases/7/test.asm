; multiplication of two numbers
ldc 6
ldc 4    ; A=4 B=6
stl 0    ; M[0]= A = 4 , A =B=6
adc -1
loop:
brz end  ; if A==0 end
adc -1
ldl 0    ; B= iterator =A=6 A= M[0]
adc 4
stl 0    ;M[0]= A, A= B=iterator
br loop
end:
ldl 0