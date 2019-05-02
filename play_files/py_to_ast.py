#!/usr/bin/env python3

import ast
import astpretty
import os
import sys

if len(sys.argv) != 2:
    print("Enter directory path")
    exit()

d = sys.argv[1]
directory = os.fsencode(d)

for file in os.listdir(directory):
    filename = os.fsdecode(file)
    if filename.endswith(".py"):
        python_file = (os.path.join(directory.decode("utf-8"), filename))

        in_file = open(python_file, "r")
        code = in_file.readlines()
        code = "".join(code)
        in_file.close()

        ast_node = ast.parse(code)
        print(ast.dump(ast_node))
        pretty_string = astpretty.pformat(ast_node, indent="  ", show_offsets=True)
        new_file = "ast_" + filename[:-3] + ".txt"
        out_file = open(new_file, "w+")
        out_file.write(pretty_string)
        out_file.close()

        
        
