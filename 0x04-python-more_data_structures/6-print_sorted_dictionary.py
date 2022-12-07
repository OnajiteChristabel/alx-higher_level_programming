#!/usr/bin/python3
def print_sorted_dictionary(a_dictionary):
    lists = []
    for i in a_dictionary:
        lists.append(i)
    lists.sort()
    for i in lists:
        print("{}: {}".format(i, a_dictionary[i]))
