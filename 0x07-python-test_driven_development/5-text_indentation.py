#!/usr/bin/python3
"""Defines a text-indentation function."""


def text_indentation(text):
    """Print text with two new lines after each '.', '?', and ':'.

    Args:
        text (string): The text to print.
    Raises:
        TypeError: If text is not a string.
    """
    if not isinstance(text, str):
        raise TypeError("text must be a string")

    else:
        word = text.split()
        idx = 0
        for i in word:
            if idx == len(word) - 1:
                print(i, end="")
            elif i[-1] == '.' or i[-1] == ':' or i[-1] == '?':
                print(i, end="")
                print()
                print()
                idx += 1
            else:
                print(i, end=" ")
                idx += 1
