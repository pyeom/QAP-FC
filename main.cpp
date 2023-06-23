#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <limits>
#include <algorithm>
#include <string.h>

using namespace std;
using namespace std::chrono;

/**
 * Calcula el costo de asignar la locación i en la ubicación j teniendo en cuenta la matriz de distancias y de flujos,
 * Recibe el valor de las asignaciones en un vector de asignaciones
 * Retorna el costo, es decir, remplaza los calores de la asignación en la FO
 * 
 * ***/
int calculateCost(const vector<vector<int>>& flowMatrix, const vector<vector<int>>& distanceMatrix, const vector<int>& assignment) {
    int cost = 0;
    int n = assignment.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost += flowMatrix[i][j] * distanceMatrix[assignment[i]][assignment[j]];
        }
    }

    return cost;
}

/***
 * Funcion que aplica ForwardChecking teniendo en cuenta el valor obtenido al asignar una locación a una ubicación,
 * Acota el dominio de la siguiente locación en cada iteración,
 * Escoge la mejor ubicación para cada iteración.
 * 
 * ***/
void forwardChecking(const vector<vector<int>>& flowMatrix, const vector<vector<int>>& distanceMatrix, vector<int>& assignment, vector<vector<bool>>& bannedLocations) {
    int n = assignment.size();

    for (int i = 0; i < n; i++) {
        int bestLocation = -1;
        int minCostReduction = numeric_limits<int>::max();

        for (int j = 0; j < n; j++) {
            if (!bannedLocations[i][j]) {
                int costReduction = 0;

                for (int k = 0; k < n; k++) {
                    if (k != i) {
                        costReduction += flowMatrix[i][k] * (distanceMatrix[j][assignment[k]] - distanceMatrix[assignment[i]][assignment[k]]);
                        costReduction += flowMatrix[k][i] * (distanceMatrix[assignment[k]][j] - distanceMatrix[assignment[k]][assignment[i]]);
                    }
                }

                if (costReduction < minCostReduction) {
                    minCostReduction = costReduction;
                    bestLocation = j;
                }
            }
        }

        assignment[i] = bestLocation;

        // Ban the selected location for other facilities
        for (int j = 0; j < n; j++) {
            if (j != i) {
                bannedLocations[j][bestLocation] = true;
            }
        }
    }
}

int main() {
    // Lee el input
    string filename = "tai256c";
    string in_filename, out_filename;
    in_filename = filename + ".dat";
    out_filename = filename + ".out";

    ifstream inputFile(in_filename);
    ofstream outputFile(out_filename);

    if (!inputFile.is_open()) {
        cout << "Failed to open the input file." << endl;
        return 0;
    }

    if (!outputFile.is_open()) {
        cout << "Failed to open the output file." << endl;
        return 0;
    }

    int n;
    if (!(inputFile >> n) || n <= 0) {
        cout << "Invalid input for n." << endl;
        return 0;
    }

    // Inicializa las matrices
    vector<vector<int>> flowMatrix(n, vector<int>(n));
    vector<vector<int>> distanceMatrix(n, vector<int>(n));
    vector<int> assignment(n);
    vector<vector<bool>> bannedLocations(n, vector<bool>(n, false));

    // Lee matriz de flujos
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(inputFile >> flowMatrix[i][j])) {
                cout << "Invalid input for flow matrix." << endl;
                return 0;
            }
        }
    }

    // Linea vacía
    string line;
    getline(inputFile, line);

    // Lee matriz de distancias
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(inputFile >> distanceMatrix[i][j])) {
                cout << "Invalid input for distance matrix." << endl;
                return 0;
            }
        }
    }

    inputFile.close();

    // Comienza el cronometraje
    auto start = high_resolution_clock::now();

    // Aplica FC y encuentra una solución
    forwardChecking(flowMatrix, distanceMatrix, assignment, bannedLocations);

    // Termina el cronometraje
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Calcula el valor de la FO según la solución obtenida
    int cost = calculateCost(flowMatrix, distanceMatrix, assignment);

    // Escribe en el archivo de salida
    outputFile << "FO " << cost << endl;
    outputFile << "T " << duration.count() << " ms" << endl;
    outputFile << n << endl;

    for (int i = 0; i < n; i++) {
        outputFile << assignment[i] << " ";
    }

    outputFile.close();

    cout << "Solution written to: " << out_filename << endl;

    return 0;
}
