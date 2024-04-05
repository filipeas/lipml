#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>

#include <Accelerate/Accelerate.h>

#include "./data-structures/Array.cpp"
#include "./data-structures/LinkedList.cpp"

using namespace std;

struct Pixel
{
    int x, y;
    int dist;
};

vector<vector<int>> IFT(vector<vector<int> > &matrix, vector<pair<int, int>> &seeds){
    int height = matrix.size();
    int width = matrix[0].size();

    vector<vector<int> > dist_matrix(height, vector<int>(width, INT_MAX)); // Create a distance matrix (dist_matrix) with infinite values, except for the seed pixels
    vector<vector<int> > label_matrix(height, vector<int>(width, 0));// Create a label matrix (label_matrix) to keep track of the pixel labels

    queue<Pixel> q;

    for (auto& seed : seeds) {
        int x = seed.first;
        int y = seed.second;

        dist_matrix[x][y] = 0;
        label_matrix[x][y] = x * width + y;
        q.push({x, y, 0});
    }

    while (!q.empty()) {
        Pixel pixel = q.front();
        q.pop();

        int x = pixel.x;
        int y = pixel.y;

        // define neighbors of pixel (refactor for make dinamic... (adjacency relation))
        vector<pair<int, int>> neighbors = {{x+1, y}, {x-1, y}, {x, y+1}, {x, y-1}};

        for (auto& neighbor : neighbors){
            int nx = neighbor.first;
            int ny = neighbor.second;

            if (nx >= 0 && nx < height && ny >= 0 && ny < width) {
                int path_cost = 1; // path_cost function (refactor for make dinamic...)
                if (dist_matrix[nx][ny] > dist_matrix[x][y] + path_cost) {
                    dist_matrix[nx][ny] = dist_matrix[x][y] + path_cost;
                    label_matrix[nx][ny] = label_matrix[x][y];
                    q.push({nx, ny, dist_matrix[nx][ny]});
                }
            }
        }
    }

    return label_matrix;
}

void printAllTree(const vector<vector<int>>& label_matrix){
    for (const auto& row : label_matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void printIsolatedTree(const vector<vector<int>>& label_matrix) {
    int rows = label_matrix.size();
    int cols = label_matrix[0].size();

    // Conjunto para rastrear as etiquetas já impressas
    unordered_set<int> etiquetas_impressas;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int etiqueta = label_matrix[i][j];
            // Verifica se a etiqueta já foi impressa para evitar repetições
            if (etiquetas_impressas.find(etiqueta) == etiquetas_impressas.end()) {
                cout << "Árvore " << etiqueta << ":" << endl;
                // Percorre a matriz de label_matrix para imprimir os pixels pertencentes à mesma árvore
                for (int x = 0; x < rows; ++x) {
                    for (int y = 0; y < cols; ++y) {
                        if (label_matrix[x][y] == etiqueta) {
                            cout << label_matrix[x][y] << " ";
                        } else {
                            cout << "  ";
                        }
                    }
                    cout << endl;
                }
                cout << endl;
                // Adiciona a etiqueta ao conjunto de etiquetas já impressas
                etiquetas_impressas.insert(etiqueta);
            }
        }
    }
}

int main()
{
    // vector<vector<int>> image = {
    //     {1, 2, 3},
    //     {4, 5, 6},
    //     {7, 8, 9}
    // };
    vector<vector<int>> image = {
        {1, 1, 1, 2, 2},
        {1, 1, 3, 2, 2},
        {1, 3, 3, 3, 2},
        {4, 4, 4, 4, 2},
        {4, 4, 4, 4, 4}
    };
    vector<pair<int, int>> seeds = {{0, 0}, {2, 2}}; // Seeds at (0, 0) and (2, 2)

    auto result = IFT(image, seeds);

    printAllTree(result);

    printIsolatedTree(result);

    Array<int> stack;
    stack.push(1);
    stack.push(3);
    cout << stack.peek() << endl;
    cout << stack.pop() << endl;
    cout << stack.peek() << endl;

    LinkedList<int> list;
    list.append(1);
    list.append(4);
    list.print();
    
    return 0;
}
