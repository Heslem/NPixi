#pragma once

#include <vector>
#include "neural_layer.h"

struct neural_network {

private:
    unsigned int number_hidden_layers;
    unsigned int neurons_per_layer; 
    unsigned int number_inputs; 
    unsigned int number_outputs;

    std::vector<neural_layer> network_layers;
public:
    neural_network(const neural_network& other) {
        this->number_hidden_layers = other.number_hidden_layers;
        this->neurons_per_layer = other.neurons_per_layer;
        this->number_inputs = other.number_inputs;
        this->number_outputs = other.number_outputs;
        this->network_layers = other.network_layers;
    }

    neural_network(
        unsigned int hidden_layers_n = 2,
        unsigned int neurons_per_layer_n = 3,
        unsigned int inputs_n = 2,
        unsigned int outputs_n = 1
    )
    {
        if (inputs_n == 0) {
            throw std::invalid_argument("The number of input neurons must be greater than zero. \n");
        }

        if (outputs_n == 0) {
            throw std::invalid_argument("The number of output neurons must be greater than zero. \n");
        }

        if (hidden_layers_n != 0 && neurons_per_layer_n == 0) {
            throw std::invalid_argument("The number of neurons on the hidden layer must be greater than zero if there is a hidden layer. \n");
        }

        this->number_hidden_layers = hidden_layers_n;
        this->neurons_per_layer = neurons_per_layer_n;
        this->number_inputs = inputs_n;
        this->number_outputs = outputs_n;

        if (number_hidden_layers != 0) {

            neural_layer input_Layer(neurons_per_layer, number_inputs);
            network_layers.push_back(input_Layer);

            for (unsigned int i = 0; i < number_hidden_layers - 1; ++i) {
                neural_layer hidden_Layer(neurons_per_layer, neurons_per_layer);
                network_layers.push_back(hidden_Layer);
            }

            neural_layer output_Layer(number_outputs, neurons_per_layer);
            network_layers.push_back(output_Layer);

        }
        else {
            neural_layer input_Layer(number_outputs, number_inputs);
            network_layers.push_back(input_Layer);
        }
    }

    static const int random_int(const int& min, const int& max) {
        int _min = (min < max) ? min : max;
        int _max = (max > min) ? max : min;

        return rand() % (_max - _min + 1) + _min;
    }

    void mutate(const unsigned int& mutateCount = 1) {

        for (unsigned i = 0; i < mutateCount; ++i)
        {
            int randomFactor = random_int(0, 4);
            if (randomFactor < 4) {
                int layer_index = random_int(0, (int)network_layers.size() - 1);

                int max_row_index = (int)network_layers[layer_index].number_inputs - 1;
                int max_colomn_index = (int)network_layers[layer_index].number_neurons - 1;

                int row = random_int(0, max_row_index);
                int colomn = random_int(0, max_colomn_index);

                auto& weight = network_layers[layer_index].weights[row][colomn];
                if (randomFactor == 0)
                {
                    weight = randomizer::random_float();
                }
                else if (randomFactor == 1) {
                    weight = -weight;
                }
                else if (randomFactor == 2) {
                    weight += randomizer::random_float(-0.5f, 0.5f);
                }
                else if (randomFactor == 3) {
                    weight += randomizer::random_float(-0.2f, 0.2f);
                }
            }
        }

    }


    const std::vector<float> get(const std::vector<float>& input_values) {
        if (input_values.size() != number_inputs) {
            throw std::invalid_argument("The input data does not correspond to the dimension of the neural network.\n");
        }

        // Вычисления
        matrix temp(input_values);

        for (neural_layer& layer : network_layers) {
            temp = layer.get(temp);
        }

        std::vector<float> result(number_outputs); // Результат

        for (unsigned int i = 0; i < number_outputs; ++i) {
            result[i] = temp[0][i];
        }

        return result;
    }

    neural_network& operator = (const neural_network& other) {
        if (this == &other) {
            return *this;
        }

        this->number_hidden_layers = other.number_hidden_layers;
        this->neurons_per_layer = other.neurons_per_layer;
        this->number_inputs = other.number_inputs;
        this->number_outputs = other.number_outputs;
        this->network_layers = other.network_layers;

        return *this;
    }
};