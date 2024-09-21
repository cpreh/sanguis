#ifndef SANGUIS_CLIENT_PERK_CATEGORY_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CATEGORY_HPP_INCLUDED

#include <sanguis/client/perk/category_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::perk
{

enum class category : std::uint8_t
{
  survival,
  attack
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::client::perk::category::attack);

#endif
