#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>

#include "./data-structures/LinkedList.cpp"

#include "LinearRegression.cpp"

using namespace std;

int main()
{
    printf("Hello World");

    // Dados de exemplo
    vector<vector<double>> X = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}}; // Features
    vector<double> y = {3, 4, 5, 6, 7}; // Rótulos

    // Parâmetros de treinamento
    double taxaAprendizado = 0.01; // Taxa de aprendizado
    int numIteracoes = 1000; // Número de iterações de treinamento

    // Criar objeto de regressão linear e treinar o modelo
    LinearRegression modelo(X, y, taxaAprendizado, numIteracoes);
    modelo.train();
    
    // Obter e exibir os parâmetros finais do modelo
    vector<double> parametrosFinais = modelo.getFinalParameters();
    cout << "Parâmetros finais: ";
    for (size_t i = 0; i < parametrosFinais.size(); ++i) {
        cout << "beta_" << i << " = " << parametrosFinais[i] << " ";
    }
    cout << endl;

    return 0;
}
