class Classy:
    def __init__(self, class_name):
        self.name = class_name

    def print_class_info(self):
        print(self.name)
        x = 6
        y = 65
        z = x+y
        

    def change_class_name(self, new_name):
        self.name = new_name

    def get_class_name(self):
        return self.name


class notClassy:
    def __init__(self, class_name):
        self.name = class_name

    def print_class_info(self):
        print(self.name)

if __name__ == "__main__"():
    pass

c = Classy("beautiful")
c.print_class_info()
c.change_class_name("soup")
print(c.get_class_name())

if c.print_class_info():
    print("yes")

while c.print_class_info():
    c.change_class_name("new")

'''
call can be in assign

'''
