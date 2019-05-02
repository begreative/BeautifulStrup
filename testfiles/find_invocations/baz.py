from foo import add

class Bazzy:

    def __init__(self):
        pass
    
    def add(self, a, b):
        return add(a, b)

    def substract(self, a, b):
        return a - b

    def divide(self, a, b):
        return a/b

    def multiply(self, a, b):
        return a * b
    
