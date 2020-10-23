#pragma once
#include <cstdint>
#include <ostream>
#include <utility>

class Point
{
public:

    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;

    static std::pair<Point, Point> MakeLine(const std::pair<double, double>& first_point,
                                            const std::pair<double, double>& second_point,
                                            size_t                           line_id);

    enum class PointType : uint8_t
    {
        FirstPoint,
        SecondPoint
    };

    const std::pair<double, double>& GetCoordinates() const;
    size_t                           GetOwnerId() const;
    PointType                        GetType() const;


    friend std::ostream& operator<<(std::ostream& os, const Point& obj);

private:
    Point(const std::pair<double, double>& coordinates, size_t owner_id, PointType type);
private:
    const std::pair<double, double> m_coordinates;
    const size_t                    m_owner_id;
    const PointType                 m_type;
};
