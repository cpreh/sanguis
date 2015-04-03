#include <sanguis/gui/impl/draw_sprite.hpp>
#include <sanguis/gui/impl/fill_rect.hpp>
#include <sanguis/gui/impl/sprite_type_choices.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


void
sanguis::gui::impl::fill_rect(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const &_rect,
	sge::image::color::any::object const &_color
)
{
	if(
		_rect.w() <= 0
		||
		_rect.h() <= 0
	)
		return;

	typedef
	sge::image::color::rgba8_format
	color_format;

	typedef
	sge::sprite::config::choices<
		sanguis::gui::impl::sprite_type_choices,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_color<
				color_format
			>
		>
	>
	choices;

	typedef
	sge::sprite::parameters<
		choices
	>
	parameters;

	sanguis::gui::impl::draw_sprite(
		_renderer,
		_context,
		parameters()
		.pos(
			_rect.pos()
		)
		.size(
			_rect.size()
		)
		.color(
			sge::image::color::any::convert<
				color_format
			>(
				_color
			)
		)
	);
}
