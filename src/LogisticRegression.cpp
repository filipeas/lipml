#include <iostream>
#include <vector>

using namespace std;

class LogisticRegression {
    private:
        vector<vector<double>> X;
        vector<double> y;
        vector<double> betas;
        double learningRate;
        int iterations;
        int typeErrorFunction; // 0 - normal | 1 - LDA | 2 - QDA | 3 - Naive Bayes

        double sigmoid(double z) {
            return 1 / (1 + exp(-z));
        }

        void DefaultLogisticRegression(const vector<double> &features, vector<double> &weights, double error) {
            // default logistic regression (entropia cruzada)
            for (int j = 0; j < features.size(); j++) {
                weights[j] += features[j] * error; // gradient of weights
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
                    // compute default logistic regression
                    DefaultLogisticRegression(X[i], weights, error);
                } else if (typeErrorFunction == 1) {
                    // compute LDA
                    // LDA(X[i], weights, error);
                } else if (typeErrorFunction == 2) {
                    // compute QDA
                    // QDA(X[i], weights, error);
                } else if (typeErrorFunction == 3) {
                    // compute Naive Bayes
                    // NaiveBayes(X[i], weights, error);
                }
            }

            // update weights
            for (int i = 0; i < numParameters; i++) {
                betas[i] += (weights[i] / n) * learningRate;
            }
        }

        double Compute_CrossEntropy () {
            double totalError = 0.0;
            int n = X.size();

            for (int i = 0; i < n; i++){
                double y_pred = Predict(X[i]); // compute predict value by model

                totalError += -(y[i] * log(y_pred) + (1 - y[i]) * log(1 - y_pred)); // cross entropy
            }

            return totalError / n;
        }
    public:
        LogisticRegression(vector<vector<double>> &X, vector<double> &y, double learningRate, int iterations, int typeErrorFunction)
        : X(X), y(y), learningRate(learningRate), iterations(iterations), typeErrorFunction(typeErrorFunction) {
            betas.resize(X[0].size(), 0.0);
        }

        void Train() {
            for (int i = 0; i < iterations; i++) {
                GradientDescent();
                if (typeErrorFunction == 0) {
                    // default logistic regression
                    cout << "Iteration " << i + 1 << ", CrossEntropy_train: " << Compute_CrossEntropy() << endl;
                } else if (typeErrorFunction == 1) {
                    // LDA
                    // cout << "Iteration " << i + 1 << ", MAE_train: " << Compute_MAE() << endl;
                } else if (typeErrorFunction == 2) {
                    // QDA
                    // cout << "Iteration " << i + 1 << ", MAE_train: " << Compute_MAE() << endl;
                } else if (typeErrorFunction == 3) {
                    // Naive Bayes
                    // cout << "Iteration " << i + 1 << ", MAE_train: " << Compute_MAE() << endl;
                }
            }
        }

        double Predict(const vector<double> &features) {
            double z = betas[0]; // logits (b0 + b1x1 + b2x2 + ...)
            for (size_t j = 0; j < features.size(); j++){
                z += betas[j + 1] * features[j]; // coeficients of parameters
            }

            return sigmoid(z);
        }

        vector<double> getFinalParameters() const {
            return betas;
        }
};