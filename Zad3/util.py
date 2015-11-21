__author__ = 'Bartek'

def check_param(value, predicate, message):
    if not predicate(value):
        raise Exception(message)
    return value
