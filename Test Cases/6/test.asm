;computing mean of 4 numbers
ldc 12
adc 2
adc 32
adc 6 
ldc 2 ; for dividing by 4
; Reg_B= sum and Reg_A =2
shr
stl 0 ; stored value at 0th position



