import math

def function (x):
    return -2*(math.sin(x/2)) + 5

x = 0;
while(x < 15):
    print("{",x,",",function(x),"}",",")
    x+= 0.5
