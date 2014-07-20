#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/aux_/style/background_color.hpp>
#include <sanguis/gui/aux_/style/border_color.hpp>
#include <sanguis/gui/aux_/style/inner_border.hpp>
#include <sanguis/gui/aux_/style/outer_border.hpp>
#include <sanguis/gui/aux_/style/simple.hpp>
#include <sanguis/gui/aux_/style/spacing.hpp>
#include <sanguis/gui/aux_/style/text_color.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
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

sge::image::color::any::object
sanguis::gui::aux_::style::simple::text_color() const
{
	return
		sanguis::gui::aux_::style::text_color();
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
