#ifndef SANGUIS_SERVER_AURAS_TARGET_KIND_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_TARGET_KIND_HPP_INCLUDED

#include <sanguis/server/auras/target_kind_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::auras
{

enum class target_kind : std::uint8_t
{
  enemy,
  friend_
};

}

#endif
