class Classy:
    def __init__(self, class_name):
        self.name = class_name

    def print_class_info(self):
        print(self.name)

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