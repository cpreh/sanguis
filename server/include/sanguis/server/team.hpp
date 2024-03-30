#ifndef SANGUIS_SERVER_TEAM_HPP_INCLUDED
#define SANGUIS_SERVER_TEAM_HPP_INCLUDED

#include <sanguis/server/team_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server
{

enum class team : std::uint8_t
{
  players,
  monsters
};

}

#endif
