#pragma once

#include <cmath>
#include "matrix.h"

struct neural_layer
{
    friend struct neural_network;
private:
    unsigned int number_neurons; 
    unsigned int number_inputs; 
    matrix weights; 
public:

    neural_layer(unsigned int number_neurons, unsigned int number_inputs) 
        : weights(matrix::randomMatrix(number_inputs, number_neurons)), 
        number_neurons(number_neurons),
        number_inputs(number_inputs)
    {
    }

    ~neural_layer() {

    }

    const matrix get(const matrix& input) {
        matrix result(input * weights);
        for (unsigned int i = 0; i < number_neurons; ++i) {
            result[0][i] = tanhf(result[0][i]);
        }

        return result;
    }

    neural_layer& operator=(const neural_layer& other) {
        if (this == &other) {
            return *this;
        }
        number_neurons = other.number_neurons;
        number_inputs = other.number_inputs;
        weights = other.weights;
        return *this;
    }
};