import numpy as np
from ellipseFit import ellipseFit

def main():
    def Load_Coordinates():
        data = [[float(val) for val in input().split()] for i in range(2)]
        return data

    for _ in range(10):
        data = Load_Coordinates()
        cx, cy, a, b = ellipseFit(data)
        print("{} {} {} {}".format(cx, cy, a, b))

if __name__ == '__main__':
    main()