#include <sanguis/gui/fill_color.hpp>
#include <sanguis/gui/fill_level.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/aux_/shrink_rect.hpp>
#include <sanguis/gui/aux_/style/background_color.hpp>
#include <sanguis/gui/aux_/style/border_color.hpp>
#include <sanguis/gui/aux_/style/inner_border.hpp>
#include <sanguis/gui/aux_/style/outer_border.hpp>
#include <sanguis/gui/aux_/style/simple.hpp>
#include <sanguis/gui/aux_/style/spacing.hpp>
#include <sanguis/gui/aux_/style/text_color.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::gui::aux_::style::simple::simple()
:
	sanguis::gui::style::base()
{
}

sanguis::gui::aux_::style::simple::~simple()
{
}

sge::rucksack::dim const
sanguis::gui::aux_::style::simple::button_spacing() const
{
	return
		this->spacing();
}

void
sanguis::gui::aux_::style::simple::draw_button(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		_area,
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sanguis::gui::aux_::style::outer_border::value,
			_area.size()
			-
			2
			*
			sanguis::gui::aux_::style::outer_border::value
		),
		sanguis::gui::aux_::style::background_color()
	);
}

void
sanguis::gui::aux_::style::simple::draw_bar(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area,
	sanguis::gui::fill_level const _fill_level,
	sanguis::gui::fill_color const &_fill_color
) const
{
	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		_area,
		sanguis::gui::aux_::style::border_color()
	);

	sge::rucksack::rect const inner_rect(
		sanguis::gui::aux_::shrink_rect(
			_area,
			sanguis::gui::aux_::style::outer_border::value
		)
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		inner_rect,
		sanguis::gui::aux_::style::background_color()
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		sge::rucksack::rect(
			inner_rect.pos(),
			sge::rucksack::dim(
				fcppt::cast::float_to_int<
					sge::rucksack::scalar
				>(
					fcppt::cast::int_to_float<
						sanguis::gui::fill_level::value_type
					>(
						inner_rect.w()
					)
					*
					_fill_level.get()
				),
				inner_rect.h()
			)
		),
		_fill_color.get()
	);

}

sge::rucksack::padding const
sanguis::gui::aux_::style::simple::frame_padding() const
{
	return
		sge::rucksack::padding{
			10
		};
}

void
sanguis::gui::aux_::style::simple::draw_frame(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area,
	sge::rucksack::padding const _padding
) const
{
	sge::rucksack::scalar const border_size(
		_padding.get()
		/
		2
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				_area.w(),
				border_size
			)
		),
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				border_size,
				_area.h()
			)
		),
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::rucksack::dim(
				_area.w()
				-
				border_size,
				0
			),
			sge::rucksack::dim(
				border_size,
				_area.h()
			)
		),
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::rucksack::dim(
				0,
				_area.h()
				-
				border_size
			),
			sge::rucksack::dim(
				_area.w(),
				border_size
			)
		),
		sanguis::gui::aux_::style::border_color()
	);
}

sge::rucksack::dim const
sanguis::gui::aux_::style::simple::edit_spacing() const
{
	return
		this->spacing();
}

void
sanguis::gui::aux_::style::simple::draw_edit(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		_area,
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		_renderer,
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sanguis::gui::aux_::style::outer_border::value,
			_area.size()
			-
			2
			*
			sanguis::gui::aux_::style::outer_border::value
		),
		sanguis::gui::aux_::style::background_color()
	);
}

sge::rucksack::dim const
sanguis::gui::aux_::style::simple::image_spacing() const
{
	return
		sge::rucksack::dim::null();
}

void
sanguis::gui::aux_::style::simple::draw_image(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

sge::rucksack::dim const
sanguis::gui::aux_::style::simple::text_spacing() const
{
	return
		sge::rucksack::dim::null();
}

void
sanguis::gui::aux_::style::simple::draw_text(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

sanguis::gui::text_color
sanguis::gui::aux_::style::simple::text_color() const
{
	return
		sanguis::gui::text_color(
			sanguis::gui::aux_::style::text_color()
		);
}

sge::rucksack::dim const
sanguis::gui::aux_::style::simple::spacing() const
{
	return
		fcppt::math::dim::fill<
			sge::rucksack::dim::dim_wrapper::value
		>(
			sanguis::gui::aux_::style::spacing::value
		);
}
