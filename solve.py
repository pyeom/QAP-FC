import numpy as np
import os


def readfile(filename):
    '''
    Reads the file
        - input:
            filename:   str, name of the file
        ----------------------
        - output:
            n: int, size of the instance
            A: ndarray, matrix of distances between each point
            B: ndarray, matrix of flows between each point
    '''
    fp = open(filename, 'r')
    lines = [line.strip() for line in fp]

    fp.close()

    n = int(lines[0])
    A = np.empty((n, n), dtype='int')
    B = np.empty((n, n), dtype='int')
    
    a = lines[2 : 2 + n]
    b = lines[2 + n + 1: 2 + (2 * n) + 1]
    
    i = 0
    for elemento in a:
        elemento = elemento.strip().split(' ')
        
        for indice in range(len(elemento)):
            A[i][indice] = elemento[indice]
        
        i += 1
    
    i = 0
    for elemento in b:
        elemento = elemento.strip().split(' ')
        
        for indice in range(len(elemento)):
            B[i][indice] = elemento[indice]
        
        i += 1
    
    return n, A, B


def menu():
    '''
    Displays a menu to choose the file to read
        - input:
            none
        ----------------------
        - output:
            filename:   char, name of the chosen file to read
    '''
    directory = os.getcwd()
    directories = os.listdir()

    ## asks what instance to run
    bufer1 = -1

    if bufer1 != 0:
        print("What type of instance you want to review?")
        ignores = ['.git', '.gitattributes', 'README.md', 'solve.py']
        
        directories_solo = [elem for elem in directories if elem not in ignores ]

        for element in range(len(directories_solo)):
            print("{}.- {}".format(element + 1, directories_solo[element]))

        print("0.- Exit")
        bufer1 = int(input("Choose one option: ")) - 1
        print(directories_solo[bufer1])

        try:
            directory = os.chdir(os.getcwd() + "\\" +  directories_solo[bufer1])
            print("Soy el directorio: ", directory)
        
        except:
            pass
        
        bufer2 = -1
        files_in_dir = os.listdir()
        if bufer2 != 0:
            print("What instance you want to solve?")

            for element in range(len(files_in_dir)):
                print("{}.- {}".format(element + 1, files_in_dir[element]))
            
            print("0.- Back")

            bufer2 = int(input("Choose one option: ")) - 1
            filename = files_in_dir[bufer2]
    
    return filename


if __name__=='__main__':
    filename = menu()
    n, A, B = readfile(filename)
    print(A)
    



