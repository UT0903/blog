import numpy as np
from hyperplaneFitViaTls import hyperplaneFitViaTls
#from another import hyperplaneFitViaTls
def main():
    def Load_Coordinates(n_dim):
        data = [[float(val) for val in input().split()] for i in range(n_dim)]
        return data

    for _ in range(10):
        n_dim = int(input())
        data = Load_Coordinates(n_dim)
        params = hyperplaneFitViaTls(data)
        print(*params)

if __name__ == '__main__':
    main()