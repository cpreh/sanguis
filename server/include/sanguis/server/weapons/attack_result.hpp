#ifndef SANGUIS_SERVER_WEAPONS_ATTACK_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTACK_RESULT_HPP_INCLUDED

#include <sanguis/server/weapons/attack_result_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons
{

enum class attack_result : std::uint8_t
{
  success,
  failure
};

}

#endif
