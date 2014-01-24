#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/aux_/shrink_rect.hpp>
#include <sanguis/gui/aux_/style/background_color.hpp>
#include <sanguis/gui/aux_/style/border_color.hpp>
#include <sanguis/gui/aux_/style/outer_border.hpp>
#include <sanguis/gui/widget/bar.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::gui::widget::bar::bar(
	sge::renderer::device::ffp &_renderer,
	sge::rucksack::dim const _dim,
	sge::image::color::any::object const &_foreground,
	sanguis::gui::widget::bar::fill_level const _value
)
:
	sanguis::gui::widget::base(),
	renderer_(
		_renderer
	),
	foreground_(
		_foreground
	),
	value_(
		_value
	),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					_dim.w()
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar(
						_dim.w()
					)
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					_dim.h()
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar(
						_dim.h()
					)
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sanguis::gui::default_aspect()
		)
	)
{
}

sanguis::gui::widget::bar::~bar()
{
}

void
sanguis::gui::widget::bar::value(
	sanguis::gui::widget::bar::fill_level const _value
)
{
	value_ =
		_value;
}

void
sanguis::gui::widget::bar::on_draw(
	sge::renderer::context::ffp &_render_context
)
{
	sanguis::gui::aux_::fill_rect(
		renderer_,
		_render_context,
		this->layout().area(),
		sanguis::gui::aux_::style::border_color()
	);

	sge::rucksack::rect const inner_rect(
		sanguis::gui::aux_::shrink_rect(
			this->layout().area(),
			sanguis::gui::aux_::style::outer_border::value
		)
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_render_context,
		inner_rect,
		sanguis::gui::aux_::style::background_color()
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_render_context,
		sge::rucksack::rect(
			inner_rect.pos(),
			sge::rucksack::dim(
				fcppt::cast::float_to_int<
					sge::rucksack::scalar
				>(
					fcppt::cast::int_to_float<
						sanguis::gui::widget::bar::fill_level::value_type
					>(
						inner_rect.w()
					)
					*
					value_.get()
				),
				inner_rect.h()
			)
		),
		foreground_
	);
}

sge::rucksack::widget::base &
sanguis::gui::widget::bar::layout()
{
	return
		layout_;
}
