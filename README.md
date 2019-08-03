# HG-List
A tool for storing values in files.

Description 
It can store integer, double, string and bool values with a name in files. 
Also there is a simple interface for writing and reading files.
Everything is found in the "hg" namespace.


Filesyntax:

Type_of_value [Name] {Value}

The value-type is a single lower case character that is the follwing for the specific type: 
i = integer
d = double
s = string
b = bool

String values aren't stored with a " at the beginning and the end

Example:
d [Pi] {3.1415926}
This is a double with the name Pi and the value 3.1415926

You can find examples in the example branch of this repository.

Licence 
If you want to use HG-List in a public project, please email me.
