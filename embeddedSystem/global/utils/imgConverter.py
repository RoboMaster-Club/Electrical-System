from PIL import Image
import numpy as np

"""
Convert image file to bit matrix
"""

imgFile = "logo.png"
SIZE = (32, 32)

im = Image.open(imgFile)
ico = im.convert("1").resize(SIZE)
ico.show()

mat = np.array(ico, int)

for rowVec in mat:
    counter = 0
    line = "B"
    for element in rowVec:
        if counter != 0 and counter % 8 == 0:
            line += ", B"
        line += str(element)
        counter += 1
    print(line)