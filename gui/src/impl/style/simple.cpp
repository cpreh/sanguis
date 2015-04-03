#include <sanguis/gui/fill_color.hpp>
#include <sanguis/gui/fill_level.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/impl/shrink_rect.hpp>
#include <sanguis/gui/impl/style/background_color.hpp>
#include <sanguis/gui/impl/style/border_color.hpp>
#include <sanguis/gui/impl/style/inner_border.hpp>
#include <sanguis/gui/impl/style/outer_border.hpp>
#include <sanguis/gui/impl/style/simple.hpp>
#include <sanguis/gui/impl/style/spacing.hpp>
#include <sanguis/gui/impl/style/text_color.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::gui::impl::style::simple::simple()
:
	sanguis::gui::style::base()
{
}

sanguis::gui::impl::style::simple::~simple()
{
}

sge::rucksack::dim const
sanguis::gui::impl::style::simple::button_spacing() const
{
	return
		this->spacing();
}

void
sanguis::gui::impl::style::simple::draw_button(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sanguis::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sanguis::gui::impl::style::outer_border::value,
			_area.size()
			-
			2
			*
			sanguis::gui::impl::style::outer_border::value
		),
		sanguis::gui::impl::style::background_color()
	);
}

void
sanguis::gui::impl::style::simple::draw_bar(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area,
	sge::rucksack::axis const _axis,
	sanguis::gui::fill_level const _fill_level,
	sanguis::gui::fill_color const &_fill_color
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sanguis::gui::impl::style::border_color()
	);

	sge::rucksack::rect const inner_rect(
		sanguis::gui::impl::shrink_rect(
			_area,
			sanguis::gui::impl::style::outer_border::value
		)
	);

	_renderer.fill_rect(
		_context,
		inner_rect,
		sanguis::gui::impl::style::background_color()
	);

	sge::rucksack::scalar const fill_size(
		fcppt::cast::float_to_int<
			sge::rucksack::scalar
		>(
			fcppt::cast::int_to_float<
				sanguis::gui::fill_level::value_type
			>(
				inner_rect.size()[
					// TODO: Make a function in rucksack for this
					fcppt::cast::enum_to_int<
						fcppt::math::size_type
					>(
						_axis
					)
				]
			)
			*
			_fill_level.get()
		)
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_axis
			==
			sge::rucksack::axis::y
			?
				sge::rucksack::vector(
					inner_rect.pos().x(),
					inner_rect.pos().y()
					+
					inner_rect.h()
					-
					fill_size
				)
			:
				inner_rect.pos()
			,
			sge::rucksack::dim(
				_axis
				==
				sge::rucksack::axis::x
				?
					fill_size
				:
					inner_rect.w()
				,
				_axis
				==
				sge::rucksack::axis::y
				?
					fill_size
				:
					inner_rect.h()
			)
		),
		_fill_color.get()
	);

}

sge::rucksack::padding const
sanguis::gui::impl::style::simple::frame_padding() const
{
	return
		sge::rucksack::padding{
			10
		};
}

void
sanguis::gui::impl::style::simple::draw_frame(
	sanguis::gui::renderer::base &_renderer,
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

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				_area.w(),
				border_size
			)
		),
		sanguis::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				border_size,
				_area.h()
			)
		),
		sanguis::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
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
		sanguis::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
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
		sanguis::gui::impl::style::border_color()
	);
}

sge::rucksack::dim const
sanguis::gui::impl::style::simple::edit_spacing() const
{
	return
		this->spacing();
}

void
sanguis::gui::impl::style::simple::draw_edit(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sanguis::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sanguis::gui::impl::style::outer_border::value,
			_area.size()
			-
			2
			*
			sanguis::gui::impl::style::outer_border::value
		),
		sanguis::gui::impl::style::background_color()
	);
}

sge::rucksack::dim const
sanguis::gui::impl::style::simple::image_spacing() const
{
	return
		sge::rucksack::dim::null();
}

void
sanguis::gui::impl::style::simple::draw_image(
	sanguis::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

sge::rucksack::dim const
sanguis::gui::impl::style::simple::text_spacing() const
{
	return
		sge::rucksack::dim::null();
}

void
sanguis::gui::impl::style::simple::draw_text(
	sanguis::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

sanguis::gui::text_color
sanguis::gui::impl::style::simple::text_color() const
{
	return
		sanguis::gui::text_color(
			sanguis::gui::impl::style::text_color()
		);
}

sge::rucksack::dim const
sanguis::gui::impl::style::simple::spacing() const
{
	return
		fcppt::math::dim::fill<
			sge::rucksack::dim
		>(
			sanguis::gui::impl::style::spacing::value
		);
}
