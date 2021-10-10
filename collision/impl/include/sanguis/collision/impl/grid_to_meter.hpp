#ifndef SANGUIS_COLLISION_IMPL_GRID_TO_METER_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_GRID_TO_METER_HPP_INCLUDED

#include <sanguis/collision/length.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/creator/size_type.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::collision::impl
{

inline sanguis::collision::length grid_to_meter(sanguis::creator::size_type const _val)
{
  return fcppt::cast::int_to_float<sanguis::collision::unit>(_val) * boost::units::si::meter;
}

}

#endif
