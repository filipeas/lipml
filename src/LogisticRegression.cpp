#include <iostream>
#include <vector>

using namespace std;

class LogisticRegression {
    private:
        vector<double> weights;
        double learningRate;

    public:
        LogisticRegression(int numFeatures, double learningRate): learningRate(learningRate) {
            // iniciando weights randomicamente
            for (int i = 0; i < numFeatures; i++) {
                weights.push_back((double) rand() / RAND_MAX);
            }
        }

        double sigmoid(double x) {
            return 1.0 / (1.0 + exp(-x));
        }

        void train(vector<vector<double>> &X, vector<int> &y, int numIterations) {
            
        }
};