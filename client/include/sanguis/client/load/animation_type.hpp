#ifndef SANGUIS_CLIENT_LOAD_ANIMATION_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_ANIMATION_TYPE_HPP_INCLUDED

#include <sanguis/client/load/animation_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
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
  reloading
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::client::load::animation_type::reloading);

#endif
