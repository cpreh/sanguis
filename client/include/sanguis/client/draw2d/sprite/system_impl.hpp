#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_IMPL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/buffers_impl.hpp>
#include <sanguis/client/draw2d/sprite/state.hpp>
#include <sanguis/client/draw2d/sprite/state_choices.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/intrusive/ordered/collection_impl.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/process/with_options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters.hpp>


template<
	typename Choices,
	typename Category
>
sanguis::client::draw2d::sprite::system<
	Choices,
	Category
>::system(
	sge::renderer::device::core_ref const _renderer,
	state_ref const _state
)
:
	renderer_{
		_renderer
	},
	state_(
		_state
	),
	buffers_(
		_renderer,
		sge::sprite::buffers::option::dynamic
	),
	collection_()
{
}

template<
	typename Choices,
	typename Category
>
sanguis::client::draw2d::sprite::system<
	Choices,
	Category
>::~system<
	Choices,
	Category
>()
= default;

template<
	typename Choices,
	typename Category
>
typename
sanguis::client::draw2d::sprite::system<
	Choices,
	Category
>::connection_ref
sanguis::client::draw2d::sprite::system<
	Choices,
	Category
>::connection(
	Category const _category
)
{
	return
		collection_.connection(
			_category
		);
}

template<
	typename Choices,
	typename Category
>
void
sanguis::client::draw2d::sprite::system<
	Choices,
	Category
>::render(
	sge::renderer::context::core &_render_context,
	Category const _category
)
{
	sge::sprite::process::with_options<
		sge::sprite::process::options<
			sge::sprite::process::geometry_options::update
		>
	>(
		_render_context,
		collection_.get(
			_category
		).range(),
		buffers_,
		sge::sprite::compare::default_(),
		state_.get(),
		sge::sprite::state::default_options<
			sanguis::client::draw2d::sprite::state_choices
		>()
		.no_blend_state()
		.no_rasterizer_state()
	);
}

template<
	typename Choices,
	typename Category
>
sge::renderer::device::core &
sanguis::client::draw2d::sprite::system<
	Choices,
	Category
>::renderer() const
{
	return
		renderer_.get();
}

#endif
