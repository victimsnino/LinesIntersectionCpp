#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "intersection_utils.h"

TEST_CASE("Intersection utils works correct", "[intersection]")
{
    auto first_coordinates  = GENERATE(as<Coords>{}, Coords(0, 0), Coords(1, 2));
    auto second_coordinates = GENERATE(as<Coords>{}, Coords(0,0), Coords(1, 0), Coords(0, 2));
    auto line_id            = GENERATE(as<size_t>{}, 1, 2);

    auto [point_1, point_2, _] = Point::MakeLine(first_coordinates, second_coordinates, line_id);
    INFO("Coords1: " << first_coordinates.first << "," << first_coordinates.second << "\n" <<
         "Coords2: " << second_coordinates.first << "," << second_coordinates.second << "\n" <<
         point_1 << "\n" << point_2);

    CHECK(point_1.GetCoordinates() == (first_coordinates < second_coordinates ? first_coordinates : second_coordinates));
    CHECK(point_2.GetCoordinates() == (first_coordinates < second_coordinates ? second_coordinates : first_coordinates));

    CHECK(point_1.GetOwnerId() == line_id);
    CHECK(point_2.GetOwnerId() == line_id);

    CHECK(point_1.GetType() == Point::PointType::FirstPoint);
    CHECK(point_2.GetType() == Point::PointType::SecondPoint);

    CHECK(((point_1 < point_2) || (first_coordinates == second_coordinates)) == true);
}

TEST_CASE("Find of intersection naive", "[intersection]")
{
    using Type = std::pair<std::vector<std::pair<Coords, Coords>>, std::optional<std::pair<size_t, size_t>>>;

    auto [raw_data, intersection]= GENERATE(as<Type>{}, 
        Type{{{{0, 0}, {1, 1}},             // 0
              {{1, 0}, {0, 1}}},            // 1

            {{0,1}}                         // Indexes
        },
        Type{{{{0, 0}, {1, 1}},             // 0
              {{0,-1}, {1, 0}}},            // 1

            std::nullopt                    // No indexes
        },
        Type{{{{0, 0}, {1, 1}},             // 0
              {{0,-1}, {1, 0}},             // 1
              {{1, 0}, {2,-1}}},            // 2

            {{1, 2}}                        // Indexes
        },
        Type{{{{0, 0}, {1, 1}},             // 0
              {{0, 2}, {1, 2}},             // 1
              {{2, 0}, {2, 2}},             // 2
              {{2.5f, 0}, {3, 1.5f}},       // 3
              {{0, 5}, {5, 0}},             // 4
              {{0, -2}, {5, 1}}},           // 5

            {{4, 5}}                        // Indexes
        },
        Type{{{{0, 0}, {1, 1}},             // 0
              {{-1, -1}, {2, 2}}},          // 1

            {{0,1}}                         // Indexes
        },
        Type{{{{0, 0}, {5, 0}},             // 0
              {{0, 1}, {5, 1}}},            // 1

            std::nullopt                    // No Indexes
        },
        Type{{{{0, 0}, {5, 0}},             // 0
              {{1, -1}, {1, 1}}},           // 1

            {{0,1}}                         // Indexes
        }
    );


    std::vector<Line> lines;

    for (const auto& [coords_1, coords_2] : raw_data)
    {
        auto line = Point::MakeLine(coords_1, coords_2, lines.size());
        lines.emplace_back(line);
    }

    const auto function = GENERATE(NaiveFindIntersection, EffectiveFindIntersection);
    auto res       = function(lines);
    auto print_opt = [](auto intersection, const std::string& name)
    {
        UNSCOPED_INFO(name << " intersection exist: " << std::boolalpha << !!intersection);
        if (intersection.has_value())
        {
            auto [i, j] = intersection.value();
            UNSCOPED_INFO(" Intersection indexes: " << i << " " << j); 
        }
    };

    print_opt(intersection, "Original");
    print_opt(res, "Found");
    REQUIRE(res == intersection);
}