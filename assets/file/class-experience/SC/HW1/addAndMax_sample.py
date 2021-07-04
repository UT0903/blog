# A and B are two-dimension python lists

def addAndMax(A, B):
    ###########################################
    #          write your code here           #
    ###########################################
            
    return 

def main():
    def Load_Matrix():
        r, c = [int(val) for val in input().split()]
        Aele = input().split()
        A = [[int(Aele[i*c + j]) for j in range(c)] for i in range(r)]

        return A

    for _ in range(20):
        A = Load_Matrix()
        B = Load_Matrix()

        print(addAndMax(A, B))

if __name__ == '__main__':
    main()