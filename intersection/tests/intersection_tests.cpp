#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "intersection_utils.h"

using coords = std::pair<double, double>;

TEST_CASE("Intersection utils works correct", "[intersection]")
{
    auto first_coordinates  = GENERATE(as<coords>{}, coords(0, 0), coords(1, 2));
    auto second_coordinates = GENERATE(as<coords>{}, coords(0,0), coords(1, 0), coords(0, 2));
    auto line_id            = GENERATE(as<size_t>{}, 1, 2);

    auto [point_1, point_2] = Point::MakeLine(first_coordinates, second_coordinates, line_id);
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
