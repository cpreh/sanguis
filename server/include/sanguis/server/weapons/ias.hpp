#ifndef SANGUIS_SERVER_WEAPONS_IAS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_IAS_HPP_INCLUDED

#include <sanguis/time_unit.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::weapons
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::time_unit, ias);

}

#endif
