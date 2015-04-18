#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/draw2d/scene/hover/healthbar.hpp>
#include <sanguis/client/draw2d/sprite/buffers_impl.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/colored/color.hpp>
#include <sanguis/client/draw2d/sprite/colored/color_format.hpp>
#include <sanguis/client/draw2d/sprite/colored/object.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/geometry/update.hpp>
#include <sge/sprite/render/parameters_impl.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <initializer_list>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::client::draw2d::sprite::unit const
	border_size = 2,
	bar_height = 8;

sanguis::client::health_value
remaining_health(
	sanguis::client::health_pair const _pair
)
{
	return
		_pair.health().get()
		/
		_pair.max_health().get();
}

}

sanguis::client::draw2d::scene::hover::healthbar::healthbar(
	sge::renderer::device::ffp &_renderer,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::radius const _radius,
	sanguis::client::health_pair const _health_pair
)
:
	buffers_{
		_renderer,
		sge::sprite::buffers::option::static_
	},
	range_{
		sge::sprite::geometry::update(
			sge::sprite::geometry::make_random_access_range(
				std::initializer_list<
					sanguis::client::draw2d::sprite::colored::object
				>{
					sanguis::client::draw2d::sprite::colored::object{
						sge::sprite::roles::pos{} =
							_center.get()
							-
							_radius.get(),
						sge::sprite::roles::size{} =
							sanguis::client::draw2d::sprite::dim(
								_radius.get() * 2,
								bar_height
							),
						sge::sprite::roles::color{} =
							sge::image::color::any::convert<
								sanguis::client::draw2d::sprite::colored::color_format
							>(
								sge::image::color::predef::black()
							)
					},
					sanguis::client::draw2d::sprite::colored::object{
						sge::sprite::roles::pos{} =
							_center.get()
							-
							_radius.get()
							+
							fcppt::math::dim::fill<
								sanguis::client::draw2d::sprite::dim
							>(
								border_size
							),
						sge::sprite::roles::size{} =
							sanguis::client::draw2d::sprite::dim{
								fcppt::cast::float_to_int<
									sanguis::client::draw2d::sprite::unit
								>(
									fcppt::cast::int_to_float<
										sanguis::client::health::value_type
									>(
										(
											_radius.get()
											-
											border_size
										)
										*
										2
									)
									*
									remaining_health(
										_health_pair
									)
								),
								bar_height
								-
								2
								*
								border_size
							},
						sge::sprite::roles::color{} =
							sanguis::client::draw2d::sprite::colored::color(
								(sge::image::color::init::red() %=
									std::min(
										fcppt::literal<
											sanguis::client::health::value_type
										>(
											2
										)
										-
										fcppt::literal<
											sanguis::client::health::value_type
										>(
											2
										)
										*
										remaining_health(
											_health_pair
										),
										fcppt::literal<
											sanguis::client::health::value_type
										>(
											1
										)
									)
								)
								(sge::image::color::init::green() %=
									std::min(
										fcppt::literal<
											sanguis::client::health::value_type
										>(
											1.4
										)
										*
										remaining_health(
											_health_pair
										),
										fcppt::literal<
											sanguis::client::health::value_type
										>(
											0.7
										)
									)
								)
								(sge::image::color::init::blue() %=
									0.0
								)
								(sge::image::color::init::alpha() %=
									1.0
								)
							)
					}
				}
			),
			sge::sprite::compare::nothing(),
			buffers_
		)
	},
	state_{
		_renderer,
		sge::sprite::state::parameters<
			state_choices
		>()
	}
{
}

sanguis::client::draw2d::scene::hover::healthbar::~healthbar()
{
}

void
sanguis::client::draw2d::scene::hover::healthbar::draw(
	sge::renderer::context::ffp &_render_context
)
{
	sge::sprite::render::range_with_options(
		sge::sprite::render::parameters<
			state_choices
		>(
			_render_context,
			buffers_.parameters().vertex_declaration()
		),
		range_,
		state_,
		sge::sprite::state::default_options<
			state_choices
		>()
	);
}
