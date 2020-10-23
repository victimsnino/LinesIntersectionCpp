#pragma once
#include <cstdint>
#include <optional>
#include <ostream>
#include <utility>
#include <vector>

class Point;

using Coords = std::pair<double, double>;
using Line = std::pair<Point, Point>;

class Point
{
public:
    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;


    static Line MakeLine(const Coords& first_point,
                         const Coords& second_point,
                         size_t        line_id);

    enum class PointType : uint8_t
    {
        FirstPoint,
        SecondPoint
    };

    const Coords& GetCoordinates() const;
    size_t        GetOwnerId() const;
    PointType     GetType() const;


    friend std::ostream& operator<<(std::ostream& os, const Point& obj);

private:
    Point(const Coords& coordinates, size_t owner_id, PointType type);
private:
    const Coords    m_coordinates;
    const size_t    m_owner_id;
    const PointType m_type;
};

bool IsIntersection(const Line& line_1, const Line& line_2);
std::optional<std::pair<size_t, size_t>> NaiveFindIntersection(std::vector<Line> lines);
