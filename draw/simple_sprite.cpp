#include "simple_sprite.hpp"
#include "environment.hpp"
#include <sge/renderer/colors.hpp>

sanguis::draw::simple_sprite::simple_sprite(
	draw::environment const &env,
	entity_id const id,
	sge::sprite::intrusive_order const order,
	sge::texture::const_part_ptr const tex)
:
	entity(
		env,
		id),
	sprite_(
		env.system(),
		order,
		sge::sprite::point::null(),
		tex,
		sge::sprite::texture_dim)
{}

void sanguis::draw::simple_sprite::update(
	time_type const time)
{
	entity::update(time);
}

void sanguis::draw::simple_sprite::orientation(
	sge::sprite::rotation_type const angle)
{
	get().rotation(angle);
}

void sanguis::draw::simple_sprite::pos(
	sge::sprite::point const& pos_)
{
	get().pos() = pos_;
}

void sanguis::draw::simple_sprite::dim(
	sge::sprite::dim const& dim_)
{
	get().size() = dim_;
}

void sanguis::draw::simple_sprite::visible(
	const bool v)
{
	get().visible(v);
}

sge::sprite::rotation_type
sanguis::draw::simple_sprite::orientation() const
{
	return get().rotation();
}

sanguis::draw::object&
sanguis::draw::simple_sprite::get()
{
	return sprite_;
}

sanguis::draw::object const &
sanguis::draw::simple_sprite::get() const
{
	return sprite_;
}

