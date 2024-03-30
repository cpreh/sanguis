#ifndef SANGUIS_CLIENT_LOAD_ANIMATION_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_ANIMATION_TYPE_HPP_INCLUDED

#include <sanguis/client/load/animation_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::load
{

enum class animation_type : std::uint8_t
{
  none,
  attacking,
  walking,
  dying,
  deploying,
  reloading,
  fcppt_maximum = reloading
};

}

#endif
