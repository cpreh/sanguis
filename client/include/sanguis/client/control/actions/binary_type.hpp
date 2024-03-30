#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_BINARY_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_BINARY_TYPE_HPP_INCLUDED

#include <sanguis/client/control/actions/binary_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::control::actions
{

enum class binary_type : std::uint8_t
{
  shoot_primary,
  shoot_secondary
};

}

#endif
