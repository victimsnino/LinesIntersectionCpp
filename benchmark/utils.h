#pragma once
#include "intersection_utils.h"

#include <chrono>
#include <iostream>
#include <random>

inline void MeasureTime(const std::vector<Line>& lines)
{
    std::vector<int> durations{};
    for (const auto& [name, function] : {std::make_pair("NaiveFindIntersection", NaiveFindIntersection),
                                         std::make_pair("EffectiveFindIntersection", EffectiveFindIntersection)})
    {
        auto start    = std::chrono::high_resolution_clock::now();
        auto result   = function(lines);
        auto end      = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>((end - start)).count();
        durations.push_back(duration);

        std::cout << name << " duration: " << duration << " microsecnds" <<  std::endl;
        std::cout << " Result: Found - " << std::boolalpha << result.has_value();
        if (result.has_value())
            std::cout << " Indexes (" << result.value().first << ", " << result.value().second << ")";
        std::cout << std::endl << std::endl;
    }

    std::cout << "Diff between durations[1] and durations[0]: " << (durations[1] - durations[0]) << " microsecnds" << std::endl;
}

inline std::vector<Line> GenerateData(int n, int k)
{
    std::vector<Line>          results{};
    std::default_random_engine re;
    for (int i = 0; i < n; ++i)
    {
        std::uniform_real_distribution<double> dist{double(i), double(i + 2)};
        Coords                                 first_point  = {dist(re), dist(re)};
        Coords                                 second_point = {dist(re), dist(re)};
        if (i < k)
        {
            first_point.second  = i;
            second_point.second = i;
        }
        while (first_point == second_point)
        {
            std::cout << "Collision..";
            first_point.first = dist(re);
        }
        results.emplace_back(Point::MakeLine(first_point, second_point, results.size()));
    }
    return results;
}
