#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/healthbar.hpp>
#include <sanguis/client/draw2d/scene/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_impl.hpp>


sanguis::client::draw2d::scene::hover::name_and_health::name_and_health(
	sanguis::client::draw2d::scene::hover::parameters const &_parameters,
	sanguis::client::draw2d::entities::hover::name_and_health const &_name_and_health
)
:
	healthbar_(
		fcppt::optional_bind_construct(
			_name_and_health.health(),
			[
				&_parameters
			](
				sanguis::client::health_pair const _health
			)
			{
				return
					fcppt::make_unique_ptr<
						sanguis::client::draw2d::scene::hover::healthbar
					>(
						_parameters.renderer(),
						_parameters.center(),
						_parameters.radius(),
						_health
					);
			}
		)
	),
	name_(
		fcppt::optional_bind_construct(
			_name_and_health.name(),
			[
				&_parameters
			](
				sanguis::client::draw2d::entities::hover::name const &_name
			)
			{
				return
					sanguis::client::draw2d::scene::hover::name(
						_parameters,
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
	if(
		healthbar_
	)
		(*healthbar_)->draw(
			_render_context
		);

	if(
		name_
	)
		name_->draw(
			_render_context
		);
}
