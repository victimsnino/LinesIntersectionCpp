#include "intersection_utils.h"

#include <tuple>

Point::Point(const std::pair<double, double>& coordinates, size_t owner_id, PointType type)
    : m_coordinates(coordinates)
    , m_owner_id(owner_id)
    , m_type(type) { }

bool Point::operator<(const Point& other) const
{
    return m_coordinates < other.m_coordinates;
}

bool Point::operator>(const Point& other) const
{
    return m_coordinates > other.m_coordinates;
}

std::pair<Point, Point> Point::MakeLine(const std::pair<double, double>& first_point,
                                        const std::pair<double, double>& second_point,
                                        size_t                           line_id)
{
    const auto& first  = first_point < second_point ? first_point : second_point;
    const auto& second = first_point < second_point ? second_point : first_point;

    return {Point(first, line_id, PointType::FirstPoint), Point(second, line_id, PointType::SecondPoint)};
}

const std::pair<double, double>& Point::GetCoordinates() const
{
    return m_coordinates;
}

size_t Point::GetOwnerId() const
{
    return m_owner_id;
}

Point::PointType Point::GetType() const
{
    return m_type;
}

std::ostream& operator<<(std::ostream& os, const Point& obj)
{
    return os
            << "Point: m_coordinates: x " << obj.m_coordinates.first
            << " y " << obj.m_coordinates.second
            << " m_owner_id: " << obj.m_owner_id
            << " m_type: " << (obj.m_type == Point::PointType::FirstPoint ? "FirstPoint" : "SecondPoint");
}
