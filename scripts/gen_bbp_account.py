#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
list = ['a','b','c','d','e','f','g','h','i','j']
def save_string_to_file(string, filename):
    with open(filename, 'a') as file:
        file.write(string)
        
for i1 in range(0,1):
    for i2 in range(0,1):
        for i3 in range(0,10):
            for i4 in range(0,10):
                    acc=list[i1]+list[i2]+list[i3]+list[i4] +"v"  +".bbp"
                    # save_string_to_file(acc + "\n", "ibbp.txt")
                    save_string_to_file(acc + "\n", "voter.txt")
