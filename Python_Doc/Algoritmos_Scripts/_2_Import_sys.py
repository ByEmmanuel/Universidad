from sys import argv
"""
script, first, second, third = argv
if len(argv) == 4:
    try:
        print(f"El script se llama: {script} , first variable: {first}, second: {second}, third: {third}")
    except TypeError:
        print("ocurrio un error")
else:
    print("error")
"""

"""
script, user_name = argv
promt = '> '


print(f"Hi {user_name}, i'm the script {script} ")
print(f"do you like me? {user_name}")
likes = input(promt)

print(f"ok te gusta? {likes}")
"""


def print_argvs(*args):
    v1, v2 = argv
    print(f"v1: {v1}, v2: {v2}")
    return None

print_argvs()

"""
#Ejecutar en terminal
script, filename = argv
txt = open(filename)
print(f"asi se llama tu archivo: {filename}")
print(txt.read())
"""


