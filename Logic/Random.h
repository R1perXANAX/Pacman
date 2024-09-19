//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_RANDOM_H
#define PACMANV2_RANDOM_H

#include <random>

/**
 * @file Random.h
 * @brief Singleton class for random number generation.
 *
 * This class encapsulates C++ Standard Library's random number generation
 * facilities in a singleton pattern. It offers methods to generate random numbers
 * either with a specific distribution or within a given range.
 *
 * Usage:
 *  - Access the singleton instance with Random::Instance().
 *  - Use GetRandom<Distribution>() to generate a random number with a specific distribution.
 *  - Use GetRandomInRange(min, max) to generate a random number within a range.
 *
 * Example:
 *  int randomInt = Random::Instance().GetRandomInRange(1, 10);
 *  double randomDouble = Random::Instance().GetRandom<std::uniform_real_distribution<double>>();
 *
 * Note:
 *  - The class is non-copyable and non-assignable.
 */

namespace Logic {
class Random {
private:
    std::mt19937 mt;

    Random()
        : mt(std::random_device{}()) {
    }

public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& GetInstance() {
        static Random instance;
        return instance;
    }

    /**
     * @brief Generates a random number using a specified distribution.
     * @tparam Distribution Distribution type for generating random numbers.
     * @return Random number generated according to the specified distribution.
     */
    template <typename Distribution>
    auto GetRandom() -> decltype(Distribution()(mt)) {
        Distribution distribution;
        return distribution(mt);
    }

    /**
     * @brief Generates a random number within a specified range [min, max].
     * @tparam T Type of the number (integral or floating-point).
     * @param min Lower bound of the range.
     * @param max Upper bound of the range.
     * @return Random number within the specified range.
     */
    template <typename T>
    T GetRandomInRange(T min, T max) {
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(mt);
    }
};
}
#endif //PACMANV2_RANDOM_H
