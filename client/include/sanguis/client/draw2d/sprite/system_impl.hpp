#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_IMPL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/order.hpp>
#include <sanguis/client/draw2d/sprite/state.hpp>
#include <sanguis/client/draw2d/sprite/state_choices.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/intrusive/ordered/collection_impl.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/process/with_options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters.hpp>


template<
	typename Choices
>
sanguis::client::draw2d::sprite::system<
	Choices
>::system(
	sge::renderer::device::core &_renderer,
	sanguis::client::draw2d::sprite::state &_state
)
:
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
	typename Choices
>
sanguis::client::draw2d::sprite::system<
	Choices
>::~system()
{
}

template<
	typename Choices
>
typename
sanguis::client::draw2d::sprite::system<
	Choices
>::connection_type &
sanguis::client::draw2d::sprite::system<
	Choices
>::connection(
	sanguis::client::draw2d::sprite::order const _order
)
{
	return
		collection_.connection(
			_order
		);
}

template<
	typename Choices
>
void
sanguis::client::draw2d::sprite::system<
	Choices
>::render(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::sprite::order const _order
)
{
	sge::sprite::process::with_options<
		sge::sprite::process::options<
			sge::sprite::process::geometry_options::update
		>
	>(
		_render_context,
		collection_.get(
			_order
		).range(),
		buffers_,
		sge::sprite::compare::default_(),
		state_,
		sge::sprite::state::default_options<
			sanguis::client::draw2d::sprite::state_choices
		>()
		.no_blend_state()
		.no_rasterizer_state()
	);
}

template<
	typename Choices
>
sge::renderer::device::core &
sanguis::client::draw2d::sprite::system<
	Choices
>::renderer() const
{
	return buffers_.parameters().device();
}

#endif
