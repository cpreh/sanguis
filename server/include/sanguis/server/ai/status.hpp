#ifndef SANGUIS_SERVER_AI_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_AI_STATUS_HPP_INCLUDED

#include <sanguis/server/ai/status_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::ai
{

enum class status : std::uint8_t
{
  running,
  failure,
  success
};

}

#endif
