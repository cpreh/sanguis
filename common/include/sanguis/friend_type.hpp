#ifndef SANGUIS_FRIEND_TYPE_HPP_INCLUDED
#define SANGUIS_FRIEND_TYPE_HPP_INCLUDED

#include <sanguis/friend_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class friend_type : std::uint8_t
{
  sentry,
  spider
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::friend_type::spider);

#endif
