import numpy as np
import os


def readfile(filename):
    '''
    Reads the file
        - inputs:
            filename:   str, name of the file
        ----------------------
        - outputs:
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


directory = os.getcwd()
os.chdir(directory + r'\Instancias pequeñas')
filename = 'instance8A.dat'
n, A, B = readfile(filename)
print("Soy n: {}\nSoy A: {}\nSoy B: {}".format(n, A, B))

