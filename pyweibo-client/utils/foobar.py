# -*- coding: utf-8 -*-

def foobar():
    print 'call function from other py file'
    
def fib(n):    # write Fibonacci series up to n
    a, b = 0, 1
    while b < n:
        print b,
        a, b = b, a+b

def fib2(n): # return Fibonacci series up to n
    result = []
    a, b = 0, 1
    while b < n:
        result.append(b)
        a, b = b, a+b
    return result

def add(a, b):
    return a + b

def sub(a, b):
    return a - b;