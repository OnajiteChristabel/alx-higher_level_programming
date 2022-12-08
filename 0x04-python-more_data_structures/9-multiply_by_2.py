#!/usr/bin/python3
def multiply_by_2(a_dictionary):
    tmp = {}
    for i in a_dictionary:
        tmp[i] = a_dictionary[i]
        tmp[i] = tmp[i] * 2
    return tmp
