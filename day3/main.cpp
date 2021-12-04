#include <iostream>
#include <array>
#include <bitset>
#include <vector>

#include "input.hpp"

template <size_t N>
auto most_common_bits(const std::vector<std::bitset<N>>& data, bool flip = false) -> std::bitset<N> {
        std::array<size_t, N> counters = {0};
        std::bitset<N> gamma;

        for (const auto& datum : data) {
                for (auto i = 0; i < N; i++) {
                        counters[i] += static_cast<size_t>(datum[i]);
                }
        }

        for (auto i = 0; i < N; i++){
                gamma[i] = counters[i] >= (std::size(data) + (std::size(data) % 2)) / 2;
        }

        return !flip ? gamma : ~gamma;
}

template <size_t N>
auto find_value(std::bitset<N> test_mask, std::vector<std::bitset<N>> data, bool flip = false) -> std::bitset<N> {
        for (auto i = N - 1; i >= 0; i--){
                if (data.size() == 1) return data[0];

                std::erase_if(data, [i, test_mask](auto x) { return x[i] != test_mask[i]; });
                test_mask = most_common_bits(data, flip);
        }

        throw std::runtime_error("no valid number found");
}


int main(void) {
        std::vector<std::bitset<Input::BIT_LENGTH>> data_vector;
        data_vector.insert(std::end(data_vector), std::begin(Input::DATA), std::end(Input::DATA));

        std::cout << "Data len = " << std::size(data_vector) * sizeof(std::bitset<Input::BIT_LENGTH>) << std::endl;

        auto gamma = most_common_bits(data_vector);
        auto epsilon = ~gamma;

        auto gamma_i   = gamma.to_ulong();
        auto epsilon_i = epsilon.to_ulong();


        auto oxygen = find_value(gamma, data_vector);
        auto co2    = find_value(epsilon, data_vector, true);

        auto oxygen_i = oxygen.to_ulong();
        auto co2_i    = co2.to_ulong();

        std::cout 
                << "Part 1: " << gamma_i << " * " << epsilon_i << " = " << gamma_i * epsilon_i << std::endl
                << "Part 2: " << oxygen_i << " * " << co2_i <<    " = "  << oxygen_i * co2_i << std::endl;

        return 0;
}
