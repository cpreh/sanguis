#include "simple_sprite.hpp"
#include "environment.hpp"
#include <sge/sprite/intrusive/parameters.hpp>
#include <sge/math/compare.hpp>

sanguis::draw::simple_sprite::simple_sprite(
	draw::environment const &env,
	entity_id const id,
	sge::sprite::intrusive::order const order,
	sge::texture::const_part_ptr const tex,
	sge::sprite::repetition_type const _repeat)
:
	entity(
		env,
		id
	),
	sprite_(
		sge::sprite::intrusive::parameters(
			env.system(),
			order
		)
		.texture(
			tex
		)
	)
{
	if(
		sge::math::compare(
			_repeat,
			static_cast<
				sge::sprite::repetition_type
			>(1)
		)
	)
		sprite_.repeat(_repeat);
}

void sanguis::draw::simple_sprite::update(
	time_type)
{}

void sanguis::draw::simple_sprite::orientation(
	sge::sprite::rotation_type const angle)
{
	get().rotation(angle);
}

void sanguis::draw::simple_sprite::pos(
	sge::sprite::point const &pos_)
{
	get().pos() = pos_;
}

void sanguis::draw::simple_sprite::dim(
	sge::sprite::dim const &dim_)
{
	get().size() = dim_;
}

void sanguis::draw::simple_sprite::visible(
	bool const v)
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

