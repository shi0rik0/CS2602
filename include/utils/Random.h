#pragma once

#include <random>
#include <type_traits>

namespace cs2602 {
class RandomGenerator {
public:
    using SeedType = std::default_random_engine::result_type;
    RandomGenerator() = default;
    explicit RandomGenerator(SeedType seed) : engine(seed) {

    }
    void set_seed(SeedType seed) {
        engine.seed(seed);
    }

    template <typename T>
    T get(T lower, T upper, typename std::enable_if_t<std::is_integral_v<T>>* = nullptr) {
        std::uniform_int_distribution<T> dis(lower, upper);
        return dis(engine);
    }

    template <typename T>
    T get(T lower, T upper, typename std::enable_if_t<std::is_floating_point_v<T>>* = nullptr) {
        std::uniform_real_distribution<T> dis(lower, upper);
        return dis(engine);
    }
private:
    std::default_random_engine engine;
};
} // namespace cs2602


