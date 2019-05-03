#testing all possible Calls

from foo import add
from baz import Bazzy

add(5,5) #basic call
x = add(6,6) #assignment
print(add(2,3)) #call within call

def aaadd(a, b):
    add(a,b); #call within def

b = Bazzy()
print(b.add(3,7))