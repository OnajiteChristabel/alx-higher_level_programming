#!/usr/bin/python3
def uniq_add(my_list=[]):
    tmp = []
    result = 0
    for i in my_list:
        if i not in tmp:
            tmp.append(i)
            result += i
    return result
