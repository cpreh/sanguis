#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/entities/hover/name_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/healthbar.hpp>
#include <sanguis/client/draw2d/scene/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_impl.hpp>


sanguis::client::draw2d::scene::hover::name_and_health::name_and_health(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::radius const _radius,
	sanguis::client::draw2d::entities::hover::name_and_health const &_name_and_health
)
:
	healthbar_(
		fcppt::optional_bind_construct(
			_name_and_health.health(),
			[
				&_renderer,
				_center,
				_radius
			](
				sanguis::client::health_pair const _health
			)
			{
				return
					fcppt::make_unique_ptr_fcppt<
						sanguis::client::draw2d::scene::hover::healthbar
					>(
						_renderer,
						_center,
						_radius,
						_health
					);
			}
		)
	),
	name_(
		fcppt::optional_bind_construct(
			_name_and_health.name(),
			[
				&_renderer,
				&_font,
				_center,
				_radius
			](
				sanguis::client::draw2d::entities::hover::name const &_name
			)
			{
				return
					sanguis::client::draw2d::scene::hover::name(
						_renderer,
						_font,
						_center,
						_radius,
						_name
					);
			}
		)
	)
{
}

sanguis::client::draw2d::scene::hover::name_and_health::~name_and_health()
{
}

void
sanguis::client::draw2d::scene::hover::name_and_health::draw(
	sge::renderer::context::ffp &_render_context
)
{
	fcppt::maybe_void(
		healthbar_,
		[
			&_render_context
		](
			healthbar_unique_ptr const &_healthbar
		)
		{
			_healthbar->draw(
				_render_context
			);
		}
	);

	fcppt::maybe_void(
		name_,
		[
			&_render_context
		](
			sanguis::client::draw2d::scene::hover::name &_name
		)
		{
			_name.draw(
				_render_context
			);
		}
	);
}
