#ifndef SANGUIS_GUI_AUX__DRAW_SPRITE_HPP_INCLUDED
#define SANGUIS_GUI_AUX__DRAW_SPRITE_HPP_INCLUDED

#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{

template<
	typename Choices
>
void
draw_sprite(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::sprite::parameters<
		Choices
	> const &_parameters
)
{
	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			Choices
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

	typedef
	sge::sprite::object<
		Choices
	>
	sprite;

	sge::sprite::process::one(
		_context,
		sprite(
			_parameters
		),
		buffers,
		state
	);
}

}
}
}

#endif
