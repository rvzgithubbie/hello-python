import pycstruct

definitions = pycstruct.parse_file('structur.h')

with open('simple_example.dat', 'rb') as f:
    inbytes = f.read()

result = definitions['person'].deserialize(inbytes)

print(str(result))