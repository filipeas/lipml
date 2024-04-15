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
        int typeErrorFunction;

        void MSE(const vector<double> &features, vector<double> &weights, double error) {
            // MSE error
            weights[0] += -2 * error; // gradient of bias (b0)
            for (size_t j = 0; j < features.size(); j++){
                weights[j + 1] += -2 * features[j] * error; // gradient of weights
            }
        }

        void MAE(const vector<double> &features, vector<double> &weights, double error) {
            // MAE error
            weights[0] += -1 * (error / abs(error)); // gradient of bias (b0)
            for (size_t j = 0; j < features.size(); j++){
                weights[j + 1] += -1 * (features[j] * error / abs(error)); // gradient of weights
            }
        }

        void GradientDescent() {
            int n = X.size(); // number of samples
            int numParameters = betas.size(); // number of parameters
            vector<double> weights(numParameters, 0.0); // start all parameters with 0

            for (int i = 0; i < n; i++){
                double y_pred = Predict(X[i]); // compute predict value by model

                double error = y[i] - y_pred;

                if (typeErrorFunction == 0){
                    // compute MSE Error
                    MSE(X[i], weights, error);
                } else if (typeErrorFunction == 1) {
                    // compute MAE Error
                    MAE(X[i], weights, error);
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
                double y_pred = Predict(X[i]); // compute predict value by model

                double error = y[i] - y_pred;
                totalError += error * error; // error^2 because we need compute MSE
            }

            return totalError / n;
        }

        double Compute_MAE () const {
            double totalError = 0.0;
            int n = X.size();

            for (int i = 0; i < n; i++){
                double y_pred = Predict(X[i]); // compute predict value by model

                double error = abs(y[i] - y_pred);
                totalError += error; // error because we need compute MAE
            }

            return totalError / n;
        }
    public:
        LinearRegression(vector<vector<double>> &X, vector<double> &y, double learningRate, int iterations, int typeErrorFunction)
        : X(X), y(y), learningRate(learningRate), iterations(iterations), typeErrorFunction(typeErrorFunction) {
            betas.resize(X[0].size() + 1, 0.0);
        }

        void Train() {
            for (int i = 0; i < iterations; i++) {
                GradientDescent();
                if (typeErrorFunction == 0){
                    // MSE
                    cout << "Iteration " << i + 1 << ", MSE_train: " << Compute_MSE() << endl;
                }else if (typeErrorFunction == 1) {
                    // MAE
                    cout << "Iteration " << i + 1 << ", MAE_train: " << Compute_MAE() << endl;
                }
            }
        }

        double Predict(const vector<double> &features) const {
            double y_pred = betas[0]; // y' or predicted value by model (start with bias b0)
            for (size_t j = 0; j < features.size(); j++){
                y_pred += betas[j + 1] * features[j]; // coeficients of parameters
            }

            return y_pred;
        }

        vector<double> getFinalParameters() const {
            return betas;
        }
};