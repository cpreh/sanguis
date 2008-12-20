#ifndef SANGUIS_DRAW_TYPES_HPP_INCLUDED
#define SANGUIS_DRAW_TYPES_HPP_INCLUDED

#include "funit.hpp"
#include <sge/sprite/intrusive_system.hpp>
#include <sge/sprite/intrusive_object.hpp>
#include <sge/sprite/types.hpp>
#include <sge/math/vector.hpp>

namespace sanguis
{
namespace draw
{

typedef sge::sprite::unit unit;
typedef sge::math::vector<funit, 2> vector2;
typedef sge::sprite::intrusive_object object;
typedef sge::sprite::intrusive_system system;

}
}

#endif
