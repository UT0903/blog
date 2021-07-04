import numpy as np
from circleFitByDss import circleFitByDss

def CircleFitting():
    def Load_Coordinates():
        data = [[float(val) for val in input().split()] for i in range(2)]
        return data

    for _ in range(5):
        data = Load_Coordinates()
        a, b, r = circleFitByDss(data)
        print('{} {} {}'.format(a, b, r))

if __name__ == '__main__':
    CircleFitting()