#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_MAKE_GUARANTEED_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_MAKE_GUARANTEED_HPP_INCLUDED

#include <sanguis/server/weapons/modifiers/guaranteed.hpp>
#include <sanguis/server/weapons/modifiers/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons::modifiers
{

template <typename Parameters, typename... Args>
sanguis::server::weapons::modifiers::guaranteed<Parameters> make_guaranteed(Args &&..._args)
{
  return sanguis::server::weapons::modifiers::guaranteed<Parameters>{
      sanguis::server::weapons::modifiers::make<Parameters>(std::forward<Args>(_args)...)};
}

}

#endif
