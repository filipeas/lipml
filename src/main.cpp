#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>

#include "./data-structures/LinkedList.cpp"

#include "LinearRegression.cpp"
#include "LogisticRegression.cpp"

using namespace std;

int main()
{
    printf("Hello World");

    // // Dados de exemplo para Linear Regression
    // // vector<vector<double>> X = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}}; // Features
    // // vector<double> y = {3, 4, 5, 6, 7}; // Rótulos
    // vector<vector<double>> X = {{0, 0}, {0, 1}, {1, 0}, {1, 1}}; // Features
    // vector<double> y = {0, 0, 0, 1}; // Rótulos

    // // Parâmetros de treinamento
    // double taxaAprendizado = 0.01; // Taxa de aprendizado
    // int numIteracoes = 1000; // Número de iterações de treinamento

    // // Criar objeto de regressão linear e treinar o modelo
    // LinearRegression modelo(X, y, taxaAprendizado, numIteracoes, 0);
    // modelo.Train();
    
    // // Obter e exibir os parâmetros finais do modelo
    // vector<double> parametrosFinais = modelo.getFinalParameters();
    // cout << "Parâmetros finais: ";
    // for (size_t i = 0; i < parametrosFinais.size(); ++i) {
    //     cout << "beta_" << i << " = " << parametrosFinais[i] << " ";
    // }
    // cout << endl;

    // // exemplo de previsao
    // vector<double> sample = {{0, 0}};
    // double prediction = modelo.Predict(sample);
    // cout << "Probabilidade da amostra pertencer à classe positiva: " << prediction << endl;


    // ---------------------------

    // Dados de exemplo para Logistic Regression simples
    vector<vector<double>> X = {{0, 0}, {0, 1}, {1, 0}, {1, 1}}; // Features
    vector<double> y = {0, 0, 0, 1}; // Rótulos

    // Parâmetros de treinamento
    double taxaAprendizado = 0.01; // Taxa de aprendizado
    int numIteracoes = 1000; // Número de iterações de treinamento

    // Criar objeto de regressão linear e treinar o modelo
    LogisticRegression modelo(X, y, taxaAprendizado, numIteracoes);
    modelo.Train();

    // Obter e exibir os parâmetros finais do modelo
    vector<double> parametrosFinais = modelo.getFinalParameters();
    cout << "Parâmetros finais: ";
    for (size_t i = 0; i < parametrosFinais.size(); ++i) {
        cout << "beta_" << i << " = " << parametrosFinais[i] << " ";
    }
    cout << endl;

    // exemplo de previsao
    vector<vector<double>> test_data = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    cout << "Tabela Verdade AND:" << endl;
    for (size_t i = 0; i < test_data.size(); ++i) {
        double prediction = modelo.Predict(test_data[i]);
        cout << "Para entrada (" << test_data[i][0] << ", " << test_data[i][1] << "), a previsão é: " << prediction << endl;
    }
    return 0;
}
