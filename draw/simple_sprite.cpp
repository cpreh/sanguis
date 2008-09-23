#include "simple_sprite.hpp"
#include <sge/renderer/colors.hpp>

sanguis::draw::simple_sprite::simple_sprite(
	entity_id const id,
	system &sys,
	object::order_type const order,
	sge::texture::part_ptr const tex)
: entity(
	id,
	sys),
  sprite(
  	sys,
	order,
  	sge::sprite::point(
		sge::su(0),
		sge::su(0)),
	tex,
	sge::sprite::texture_dim)
{}

void sanguis::draw::simple_sprite::update(
	time_type const time)
{
	entity::update(time);
}

void sanguis::draw::simple_sprite::orientation(
	const sge::sprite::rotation_type angle)
{
	get().rotation(angle);
}

void sanguis::draw::simple_sprite::speed(
	sge::math::vector2 const& speed_)
{
	// stub
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

sge::math::vector2 const&
sanguis::draw::simple_sprite::speed() const
{
	static const sge::math::vector2 r;
	return r; // stub
}

sge::sprite::rotation_type
sanguis::draw::simple_sprite::orientation() const
{
	return get().rotation();
}

sanguis::draw::object&
sanguis::draw::simple_sprite::get()
{
	return sprite;
}

sanguis::draw::object const &
sanguis::draw::simple_sprite::get() const
{
	return sprite;
}

