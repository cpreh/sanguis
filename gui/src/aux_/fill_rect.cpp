#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


void
sanguis::gui::aux_::fill_rect(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const &_rect,
	sge::image::color::any::object const &_color
)
{
	typedef
	sge::sprite::config::type_choices<
		sge::sprite::config::unit_type<
			sge::rucksack::scalar
		>,
		sge::sprite::config::float_type<
			float // don't use
		>
	>
	type_choices;

	typedef
	sge::image::color::rgba8_format
	color_format;

	typedef
	sge::sprite::config::choices<
		type_choices,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_color<
				color_format
			>
		>
	>
	choices;

	typedef
	sge::sprite::object<
		choices
	>
	sprite;

	typedef
	sge::sprite::parameters<
		choices
	>
	parameters;

	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			choices
		>
	>
	sprite_buffers;

	typedef
	sge::sprite::state::all_choices
	state_choices;

	typedef
	sge::sprite::state::object<
		state_choices
	>
	sprite_state;

	typedef
	sge::sprite::state::parameters<
		state_choices
	>
	state_parameters;

	sprite_state state(
		_renderer,
		state_parameters()
	);

	sprite_buffers buffers(
		_renderer,
		sge::sprite::buffers::option::static_
	);

	sge::sprite::process::one(
		_context,
		sprite(
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
		),
		buffers,
		state
	);
}
