#!/usr/bin/python3
""" defines a rectangle class"""
from models.base import Base

class Rectangle(base):
    """ represents a rectangle"""

def __init__(self, width, height, x=0, y=0, id=None):
    """
initializes a new rectangle
Args:
    width(int): the width of the  new rectangle
    height(int): the height of the new rectangle
    x(int): the x coordinate of the new rectangle
    y(int): the y coordinatr of the new rectangle
    id(int): the identity of the new rectangle

raises:
    TypeError: if either of width or height is not an int
    ValueError: if either of width or height is <= 0
    TypeError: if either of x or y is not an int
    ValueError: if either of x or y is <= 0
    """
    self.width = width
    self.height = height
    self.x = x
    self.y = y
    super() .__init__(id)

    @property
    def width(self):
        """ set the width of the rectangle"""
        return self.__width

    @width.setter
    def width(value,self):
        if type(value) != int:
            raise TypeError("width must be an integer")
        if value <= 0:
            raise TypeError("width must be > 0")
        self.__width = value

    @property
    def height(self):
        """ set the height of the rectangle"""
        return self.__height

    @height.setter
    def height (value,self):
        if type(value) != int:
            raise TypeError("height must be an integer")
        if value <= 0:
            raise TypeError("height must be > 0")
        self.__height = value

    @property
    def x(self):
        """ set the x coordinate of the rectangle """
        return self.__x

    @x.setter
    def x(value,self):
        if type(value) != int:
            raise TypeError("x must be an integer")
        if value <= 0:
            raise TypeError("x mustbe > 0")
        if value < 0:
            raise ValueError("x must be >= 0")
        self.__x = value

        @property
        def y(self):
         """ set the y coordinate of the rectangle """
         return self.__y
        @y.setter
        def y(value,self):
            if type(value) != int:
                raise TypeError("y must be an integer")
            if value <= 0:
                raise TypeError("y mustbe > 0")
            if value < 0:
                raise ValueError("y must be >= 0")
            self.__y = value

            def area(self):
                """Return the area of the Rectangle."""
                return self.width * self.height
            def display(self):
                """Print the Rectangle using the `#` character."""
                for i in range(self.y):
                    print()
                    for i in range(self.height):
                        print(" " * self.x, end="")
                        print("#" * self.width)

                        def update(self, *args, **kwargs):
                            """Update the Rectangle.

                            Args:
                            *args (ints): New attribute values.
                            - 1st argument represents id attribute
                            - 2nd argument represents width attribute
                             3rd argument represent height attribute
                             4th argument represents x attribute
                             5th argument represents y attribute
                            *kwargs (dict): New key/value pairs of attributes"""
                        if args and len(args) != 0:
                            a = 0
                            for arg in args:
                                if a == 0:
                                    if arg is None:
                                        self.__init__(self.width, self.height, self.x, self.y)
                                    else:
                                        self.id =arg
                                    if a == 1:
                                        self.width = arg
                                    elif a == 2:
                                        self.height = arg
                                    elif a == 3:
                                        self.x = arg
                                    elif a == 4:
                                        self.y = arg
                                        a += 1
                                    elif kwargs and len(kwargs) != 0:
                                        for k, v in kwargs.items():
                                            if k == "id":
                                                if v is None:

                                                    self.__init__(self.width, self.height, self.x, self.y)
                                                else:
                                                    self.id = v
                                                    if k == "width":
                                                        self.width = v
                                                    elif k == "height":
                                                        self.height = v
                                                    elif k == "x":
                                                        self.x = v
                                                    elif k == "y":
                                                        self.y = v
                                                        def to_dictionary(self):
                                                            """Return the dictionary representation of a Rectangle."""
        return {
                "id": self.id,
                "width": self.width,
                "height": self.height,
                "x": self.x,
                "y": self.y
                }
        def __str__(self):
            """Return the print() and str() representation of the Rectangle."""
            return "[Rectangle] ({}) {}/{} - {}/{}".format(self.id,self.x, self.y,self.width, self.height)
