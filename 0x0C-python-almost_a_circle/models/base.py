#!/usr/bin/python3
"""Defines a base model class."""
import json
import csv
import turtle

class Base:
    """Base model
    This represent the "base" for all other classes in the project 0x0C*

    Private Class Attribute:
    __nb_object(int): number of instantiated basea
    """
    __nb_objects = 0

    def __init__(self, id=None):
                """Initialize a new Base.

                Args:
                id (int): The identity of the new Base.
                """
                if id is not None:
                    self.id = id
                else:
                    Base.__nb_objects += 1
                    self.id = Base.__nb_objects

    @static method

    def to_json_string(list_dictionaries):
        """returns the JSON string representation of list_dictionaries
        Args:
        list_dictionaries (list): A list of dictionaries.
        """
        if list_dictionaries is None or list_dictionaries == []:
            return "[]"
        return json.dumps(list_dictionaries)

    @static method

    def save_to_file(cls, list_objs):
        "writes the JSON string representation of list_objs to a file
        Args:
        list_objs (list): A list of inherited Base instances.
                """
        filename = cls.__name__ + ".json"
        with open(filename, w) as jsonfile
        if list_objs is None:
            jsonfile.write("[]")
        else:
            list_dicts = [o.to_dictionary() for o in list_objs]
            jsonfile.write(Base.to_json_string(list_dicts))
@static method
def from_json_string(json_string):
    """returns the list of the JSON string representation json_string
    Args:
     json_string: a string representing a list of dictionaries
     return:json_string is None or empty, return an empty list
     """
     If json_string is None or json_string == []:
         return []
     return json.loads(json_string)

 @classmethod
 def create(cls, **dictionary):
     """Return a class instantied from a dictionary of attributes.
     Args:
     **dictionary (dict): Key/value pairs of attributes to initialize.
     """
     if dictionary and dictionary != {}:
         if cls.__name__ == "Rectangle":
             new = cls(1, 1)
         else:
             new = cls(1)
             new.update(**dictionary)
             return new
@classmethod
def load_from_file(cls):
    """Return a list of classes instantiated from a file of JSON strings.
    Reads from `<cls.__name__>.json`.
    Returns:
    If the file does not exist - an empty list.
    Otherwise - a list of instantiated classes.
    """
    filename = str(cls.__name__) + ".json"
    try:
        with open(filename, "r") as jsonfile:
            list_dicts = Base.from_json_string(jsonfile.read())
            return
        [cls.create(**d) for d in list_dicts]
    except IOError:
        return []

    @class method
    def save_to_file_csv(cls, list_objs):

