#include "intersection_utils.h"


#include "avl.h"
#include "dheap.h"

#include <cassert>


Point::Point(const Coords& coordinates, size_t owner_id, PointType type)
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

bool Point::operator==(const Point& other) const
{
    return std::tie(m_coordinates, m_owner_id, m_type) == std::tie(other.m_coordinates,
                                                                   other.m_owner_id,
                                                                   other.m_type);
}

Line Point::MakeLine(const Coords& first_point,
                     const Coords& second_point,
                     size_t        line_id)
{
    const auto& first  = first_point < second_point ? first_point : second_point;
    const auto& second = first_point < second_point ? second_point : first_point;

    return {Point(first, line_id, PointType::FirstPoint), Point(second, line_id, PointType::SecondPoint), line_id};
}

const Coords& Point::GetCoordinates() const
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
            << "Point: m_coordinates: x "
            << obj.m_coordinates.first << " y " << obj.m_coordinates.second
            << " m_owner_id: " << obj.m_owner_id
            << " m_type: " << (obj.m_type == Point::PointType::FirstPoint ? "FirstPoint" : "SecondPoint");
}


bool IsIntersection(const Line& line_1, const Line& line_2)
{
    const auto& [x1, y1] = line_1.first.GetCoordinates();
    const auto& [x2, y2] = line_1.second.GetCoordinates();

    const auto& [x3, y3] = line_2.first.GetCoordinates();
    const auto& [x4, y4] = line_2.second.GetCoordinates();

    const auto denominator = (x1 - x2) * (y4 - y3) - (x4 - x3) * (y1 - y2);
    if (denominator == 0) // parallel or equal
    {
        const bool first_part  = (x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1) == 0;
        const bool second_part = (x1 * y2 - x2 * y1) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y2 - y1) == 0;

        return first_part && second_part;
    }

    const auto numerator_a = (x4 - x2) * (y4 - y3) - (x4 - x3) * (y4 - y2);
    const auto numerator_b = (x1 - x2) * (y4 - y2) - (x4 - x2) * (y1 - y2);
    const auto Ua          = numerator_a / denominator;
    const auto Ub          = numerator_b / denominator;

    return (0 <= Ua && Ua <= 1 && 0 <= Ub && Ub <= 1);
}

std::optional<std::pair<size_t, size_t>> NaiveFindIntersection(const std::vector<Line>& lines)
{
    for (size_t i = 0; i < lines.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < lines.size(); ++j)
        {
            if (IsIntersection(lines[i], lines[j]))
                return std::make_pair(i, j);
        }
    }
    return std::nullopt;
}

static std::pair<size_t, size_t> ReturnIndexes(const Line& first, const Line& second, const std::vector<Line>& lines)
{
    const auto first_index  = std::distance(lines.cbegin(), std::find(lines.cbegin(), lines.cend(), first));
    const auto second_index = std::distance(lines.cbegin(), std::find(lines.cbegin(), lines.cend(), second));

    auto first_in_result  = std::min(first_index, second_index);
    auto second_in_result = std::max(first_index, second_index);
    return {first_in_result, second_in_result};
}

std::optional<std::pair<size_t, size_t>> EffectiveFindIntersection(const std::vector<Line>& lines)
{
    dheap<Point> points{2};

    for (const auto& line : lines)
    {
        points.Insert(line.first);
        points.Insert(line.second);
    }

    AVLTree<Line> tree{};
    while (!points.Empty())
    {
        const auto  point = points.GetMinimumAndPop();
        const auto& line  = lines[point.GetOwnerId()];
        if (point.GetType() == Point::PointType::FirstPoint)
        {
            tree.Insert(line);
            const auto* const node_in_tree = tree.FindNode(line);
            assert(node_in_tree);

            for (const auto* target_node : {node_in_tree->GetLeftBaseNode(), node_in_tree->GetRightBaseNode()})
            {
                if (target_node && IsIntersection(target_node->GetValue(), line))
                {
                    return ReturnIndexes(target_node->GetValue(), line, lines);
                }
            }
        }
        else
        {
            const auto* const node_in_tree = tree.FindNode(line);
            assert(node_in_tree);
            if (const auto*     left_node  = node_in_tree->GetLeftBaseNode())
                if (const auto* right_node = node_in_tree->GetRightBaseNode())
                    if (IsIntersection(left_node->GetValue(), right_node->GetValue()))
                        return ReturnIndexes(left_node->GetValue(), right_node->GetValue(), lines);
            tree.Remove(line);
        }
    }
    return std::nullopt;
}
