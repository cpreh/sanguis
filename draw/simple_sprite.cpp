#include "simple_sprite.hpp"
#include "environment.hpp"
#include <sge/sprite/intrusive/parameters.hpp>
#include <sge/math/compare.hpp>

sanguis::draw::simple_sprite::simple_sprite(
	draw::environment const &env,
	entity_id const id,
	sprite::order const order,
	sge::texture::const_part_ptr const tex,
	sprite::client::repetition_type const _repeat
)
:
	entity(
		env,
		id
	),
	sprite_(
		sprite::client::parameters()
		.system(
			&env.client_system()
		)
		.order(
			order
		)
		.texture(
			tex
		)
		.texture_size()
		.elements()
	)
{
	if(
		sge::math::compare(
			_repeat,
			static_cast<
				sprite::client::repetition_type
			>(1)
		)
	)
		sprite_.repeat(_repeat);
}

void
sanguis::draw::simple_sprite::update(
	time_type
)
{}

void
sanguis::draw::simple_sprite::orientation(
	sprite::rotation_type const angle
)
{
	sprite_.rotation(
		angle
	);
}

void
sanguis::draw::simple_sprite::pos(
	sprite::point const &pos_
)
{
	sprite_.pos(
		pos_
	);
}

void
sanguis::draw::simple_sprite::dim(
	sprite::dim const &dim_
)
{
	sprite_.size(
		dim_
	);
}

void
sanguis::draw::simple_sprite::visible(
	bool const v
)
{
	sprite_.visible(v);
}

sanguis::draw::sprite::rotation_type
sanguis::draw::simple_sprite::orientation() const
{
	return sprite_.rotation();
}
