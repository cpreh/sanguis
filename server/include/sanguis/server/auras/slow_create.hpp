#ifndef SANGUIS_SERVER_AURAS_SLOW_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_SLOW_CREATE_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/buffs/slow_create.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

namespace sanguis::server::auras
{

template <typename Buff>
sanguis::server::auras::unique_ptr slow_create(
    sanguis::server::radius const _radius,
    sanguis::server::team const _team,
    sanguis::server::buffs::slow_factor const _factor)
{
  return fcppt::unique_ptr_to_base<sanguis::server::auras::aura>(
      fcppt::make_unique_ptr<sanguis::server::auras::buff>(
          _radius,
          _team,
          sanguis::aura_type::slow,
          sanguis::server::auras::influence::debuff,
          sanguis::server::buffs::slow_create<Buff>(_factor)));
}

}

#endif
