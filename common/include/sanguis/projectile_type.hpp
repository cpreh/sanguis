#ifndef SANGUIS_PROJECTILE_TYPE_HPP_INCLUDED
#define SANGUIS_PROJECTILE_TYPE_HPP_INCLUDED

#include <sanguis/projectile_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class projectile_type : std::uint8_t
{
  bullet,
  fcppt_maximum = bullet
};

}

#endif
