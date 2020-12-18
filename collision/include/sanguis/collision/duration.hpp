#ifndef SANGUIS_COLLISION_DURATION_HPP_INCLUDED
#define SANGUIS_COLLISION_DURATION_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{

using
duration
=
std::chrono::duration<
	sanguis::collision::unit
>;

}
}

#endif
