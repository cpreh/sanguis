#ifndef SANGUIS_SERVER_BUFFS_SLOW_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_SLOW_CREATE_HPP_INCLUDED

#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/create_callback.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/base_ref.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::buffs
{

template <typename Buff>
sanguis::server::buffs::create_callback
slow_create(sanguis::server::buffs::slow_factor const _factor)
{
  static_assert(
      std::is_base_of_v<sanguis::server::buffs::slow, Buff>, "Buff must derive from buffs::slow");

  return sanguis::server::buffs::create_callback{
      [_factor](sanguis::server::entities::base_ref const _entity)
      {
        FCPPT_PP_PUSH_WARNING
        FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
        return fcppt::optional::map(
            fcppt::cast::dynamic<sanguis::server::entities::with_velocity>(_entity.get()),
            [_factor](
                fcppt::reference<sanguis::server::entities::with_velocity> const _with_velocity)
            {
              return fcppt::unique_ptr_to_base<sanguis::server::buffs::buff>(
                  fcppt::make_unique_ptr<Buff>(_with_velocity, _factor));
            });
        FCPPT_PP_POP_WARNING
      }};
}

}

#endif
