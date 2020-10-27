#pragma once
#include <cstdint>
#include <optional>
#include <ostream>
#include <utility>
#include <vector>

using Coords = std::pair<double, double>;
struct Line;

class Point
{
public:
    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;
    bool operator==(const Point& other) const;


    Point(const Point& other)
        : m_coordinates{other.m_coordinates}
        , m_owner_id{other.m_owner_id}
        , m_type{other.m_type} {}

    Point(Point&& other) noexcept
        : m_coordinates{other.m_coordinates}
        , m_owner_id{other.m_owner_id}
        , m_type{other.m_type} {}


    Point& operator=(Point other) noexcept
    {
        m_coordinates = std::move(other.m_coordinates);
        m_owner_id    = std::move(other.m_owner_id);
        m_type        = std::move(other.m_type);
        return *this;
    }

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
    Coords    m_coordinates;
    size_t    m_owner_id;
    PointType m_type;
};

struct Line
{
    friend bool operator<(const Line& lhs, const Line& rhs)
    {
        return std::tie(lhs.first, lhs.second) < std::tie(rhs.first, rhs.second);
    }

    friend bool operator>(const Line& lhs, const Line& rhs) { return rhs < lhs; }


    friend bool operator==(const Line& lhs, const Line& rhs)
    {
        return std::tie(lhs.first, lhs.second, lhs.line_id) == std::tie(rhs.first, rhs.second, rhs.line_id);
    }

    Point       first;
    Point       second;
    size_t      line_id;
};


bool                                     IsIntersection(const Line& line_1, const Line& line_2);
std::optional<std::pair<size_t, size_t>> NaiveFindIntersection(const std::vector<Line>& lines);

std::optional<std::pair<size_t, size_t>> EffectiveFindIntersection(const std::vector<Line>& lines);