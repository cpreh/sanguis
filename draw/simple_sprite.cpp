#include "simple_sprite.hpp"
#include <sge/renderer/colors.hpp>

sanguis::draw::simple_sprite::simple_sprite(
	const entity_id id,
	sge::sprite::point const& pos_,
	sge::sprite::dim const& dim_,
	const sge::sprite::depth_type depth,
	const sge::sprite::rotation_type angle,
	const sge::virtual_texture_ptr tex)
: entity(
	id)
{
	sprite.push_back(
		sge::sprite::object(
			pos_,
			tex,
			dim_,
			sge::colors::white,
			depth,
			angle));
}

void sanguis::draw::simple_sprite::update(time_type)
{}

sanguis::draw::entity::sprite_vector
sanguis::draw::simple_sprite::to_sprites() const
{
	return sprite;
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

sge::sprite::object&
sanguis::draw::simple_sprite::get()
{
	return sprite.at(0);
}

sge::sprite::object const&
sanguis::draw::simple_sprite::get() const
{
	return sprite.at(0);
}

