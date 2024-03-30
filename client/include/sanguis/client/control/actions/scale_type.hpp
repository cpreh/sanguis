#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_TYPE_HPP_INCLUDED

#include <sanguis/client/control/actions/scale_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::control::actions
{

enum class scale_type : std::uint8_t
{
  horizontal_move,
  vertical_move
};

}

#endif
