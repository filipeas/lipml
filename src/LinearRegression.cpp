#include <iostream>
#include <vector>

using namespace std;

class LinearRegression {
    private:
        vector<vector<double>> X;
        vector<double> y;
        vector<double> betas;
        double learningRate;
        int iterations;

        void GradientDescent() {
            int n = X.size(); // number of samples
            int numParameters = betas.size(); // number of parameters
            vector<double> weights(numParameters, 0.0); // start all parameters with 0

            for (int i = 0; i < n; i++){
                double y_pred = betas[0]; // y' or predicted value by model (start with bias b0)
                for (size_t j = 0; j < X[i].size(); j++){
                    y_pred += betas[j + 1] * X[i][j]; // coeficients of parameters
                }

                double error = y[i] - y_pred;

                // MSE error
                weights[0] += -2 * error; // gradient of bias (b0)
                for (size_t j = 0; j < X[i].size(); j++){
                    weights[j + 1] += -2 * X[i][j] * error; // gradient of weights
                }
            }

            // update weights
            for (int i = 0; i < numParameters; i++){
                betas[i] -= (weights[i] / n) * learningRate;
            }
        }

        double Compute_MSE () const {
            double totalError = 0.0;
            int n = X.size();

            for (int i = 0; i < n; i++){
                double y_pred = betas[0]; // start with bias b0
                for (size_t j = 0; j < X[i].size(); j++){
                    y_pred += betas[j + 1] * X[i][j]; // coeficient of parameters
                }

                double error = y[i] - y_pred;
                totalError += error * error; // error^2 because we need compute MSE
            }

            return totalError;
        }
    public:
        LinearRegression(vector<vector<double>> &X, vector<double> &y, double learningRate, int iterations)
        : X(X), y(y), learningRate(learningRate), iterations(iterations) {
            betas.resize(X[0].size() + 1, 0.0);
        }

        void train() {
            for (int i = 0; i < iterations; i++) {
                GradientDescent();
                cout << "Iteration " << i + 1 << ", MSE_train: " << Compute_MSE() << endl;
            }
        }

        vector<double> getFinalParameters() const {
            return betas;
        }
};