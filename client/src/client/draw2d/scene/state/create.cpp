#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/state/array.hpp>
#include <sanguis/client/draw2d/scene/state/base.hpp>
#include <sanguis/client/draw2d/scene/state/create.hpp>
#include <sanguis/client/draw2d/scene/state/dummy.hpp>
#include <sanguis/client/draw2d/scene/state/text.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/enum/array_init.hpp>

sanguis::client::draw2d::scene::state::array
sanguis::client::draw2d::scene::state::create(sge::renderer::device::ffp_ref const _renderer)
{
  return fcppt::enum_::array_init<sanguis::client::draw2d::scene::state::array>(
      [&_renderer](sanguis::client::draw2d::z_ordering const _z_ordering)
      {
        switch (_z_ordering)
        {
        case sanguis::client::draw2d::z_ordering::ground:
        case sanguis::client::draw2d::z_ordering::destructible:
        case sanguis::client::draw2d::z_ordering::pickup:
        case sanguis::client::draw2d::z_ordering::aura:
        case sanguis::client::draw2d::z_ordering::model_generic:
        case sanguis::client::draw2d::z_ordering::player_lower:
        case sanguis::client::draw2d::z_ordering::bullet_tail:
        case sanguis::client::draw2d::z_ordering::bullet:
        case sanguis::client::draw2d::z_ordering::player_upper:
        case sanguis::client::draw2d::z_ordering::flare:
          return fcppt::unique_ptr_to_base<sanguis::client::draw2d::scene::state::base>(
              fcppt::make_unique_ptr<sanguis::client::draw2d::scene::state::dummy>());
        case sanguis::client::draw2d::z_ordering::text:
          return fcppt::unique_ptr_to_base<sanguis::client::draw2d::scene::state::base>(
              fcppt::make_unique_ptr<sanguis::client::draw2d::scene::state::text>(_renderer));
        }

        FCPPT_ASSERT_UNREACHABLE;
      });
}
