#include <sanguis/gui/fill_color.hpp>
#include <sanguis/gui/fill_level.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sanguis/gui/widget/bar.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>


sanguis::gui::widget::bar::bar(
	sanguis::gui::style::base const &_style,
	sge::rucksack::dim const _dim,
	sge::rucksack::axis const _axis,
	sanguis::gui::fill_color const &_foreground,
	sanguis::gui::fill_level const _value
)
:
	sanguis::gui::widget::base(),
	style_(
		_style
	),
	axis_{
		_axis
	},
	foreground_(
		_foreground
	),
	value_(
		_value
	),
	layout_{
		sge::rucksack::make_axis_policy(
			[
				_axis,
				_dim
			](
				sge::rucksack::axis const _cur_axis
			)
			{
				sge::rucksack::scalar const ret{
					_dim[
						sge::rucksack::axis_to_index(
							_cur_axis
						)
					]
				};

				return
					_axis
					==
					_cur_axis
					?
						sge::rucksack::axis_policy{
							sge::rucksack::minimum_size{
								ret
							}
						}
					:
						sge::rucksack::axis_policy{
							sge::rucksack::preferred_size{
								ret
							}
						}
					;
			}
		)
	}
{
}

sanguis::gui::widget::bar::~bar()
{
}

void
sanguis::gui::widget::bar::value(
	sanguis::gui::fill_level const _value
)
{
	value_ =
		_value;
}

void
sanguis::gui::widget::bar::on_draw(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_render_context
)
{
	style_.draw_bar(
		_renderer,
		_render_context,
		this->layout().area(),
		axis_,
		value_,
		foreground_
	);
}

sge::rucksack::widget::base &
sanguis::gui::widget::bar::layout()
{
	return
		layout_;
}
