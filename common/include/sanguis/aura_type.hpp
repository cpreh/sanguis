#ifndef SANGUIS_AURA_TYPE_HPP_INCLUDED
#define SANGUIS_AURA_TYPE_HPP_INCLUDED

#include <sanguis/aura_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class aura_type : std::uint8_t
{
  burn,
  slow,
  fcppt_maximum = slow
};

}

#endif
