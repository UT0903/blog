import numpy as np
from myPvAlign import myPvAlign

def main():
    def Load_Data():
        pv = [float(val) for val in input().split()]
        noteVec = [float(val) for val in input().split()]
        return np.array(pv), np.array(noteVec)

    for _ in range(48):
        pv, noteVec = Load_Data()
        params = myPvAlign(pv, noteVec)
        print(params)
        # break

if __name__ == '__main__':
    main()