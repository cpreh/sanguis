#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_IMPL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/order.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/sprite/buffers_option.hpp>
#include <sge/sprite/system_impl.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/intrusive/ordered_collection_impl.hpp>
#include <sge/sprite/render/geometry_options.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <sge/sprite/render/with_options.hpp>

template<
	typename Choices
>
sanguis::client::draw2d::sprite::system<
	Choices
>::system(
	sge::renderer::device &_renderer
)
:
	system_(
		_renderer,
		sge::sprite::buffers_option::dynamic
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
	sprite::order const _order
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
	sprite::order const _order
)
{
	sge::sprite::render::with_options<
		sge::sprite::render::options<
			sge::sprite::render::geometry_options::fill,
			sge::sprite::render::matrix_options::nothing,
			sge::sprite::render::state_options::nothing,
			sge::sprite::render::vertex_options::declaration_and_buffer
		>
	>(
		collection_.get(
			_order
		).range(),
		system_.buffers(),
		sge::sprite::compare::default_()
	);
}

template<
	typename Choices
>
sge::renderer::device &
sanguis::client::draw2d::sprite::system<
	Choices
>::renderer() const
{
	return system_.buffers().renderer();
}

#endif
