#ifndef SANGUIS_CLIENT_PERK_CATEGORY_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CATEGORY_HPP_INCLUDED

#include <sanguis/client/perk/category_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::perk
{

enum class category : std::uint8_t
{
  survival,
  attack,
  fcppt_maximum = attack
};

}

#endif
