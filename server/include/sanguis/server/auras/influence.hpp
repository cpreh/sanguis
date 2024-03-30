#ifndef SANGUIS_SERVER_AURAS_INFLUENCE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_INFLUENCE_HPP_INCLUDED

#include <sanguis/server/auras/influence_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::auras
{

enum class influence : std::uint8_t
{
  buff,
  debuff
};

}

#endif
