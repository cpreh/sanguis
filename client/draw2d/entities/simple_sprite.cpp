#include "simple_sprite.hpp"
#include "../sprite/client/parameters.hpp"
#include "../sprite/point.hpp"
#include <fcppt/math/compare.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/center.hpp>

sanguis::client::draw2d::entities::simple_sprite::simple_sprite(
	sprite::client::system &system_,		
	sprite::order const order,
	sge::texture::const_part_ptr const tex,
	sprite::client::repetition_type const _repeat
)
:
	base(),
	with_visibility(),
	sprite_(
		sprite::client::parameters()
		.pos(
			sprite::point::null()
		)
		.system(
			&system_
		)
		.order(
			order
		)
		.texture(
			tex
		)
		.visible(true)
		.texture_size()
		.elements()
	)
{
	if(
		fcppt::math::compare(
			_repeat,
			static_cast<
				sprite::client::repetition_type
			>(1)
		)
	)
		sprite_.repeat(
			_repeat
		);
}

sanguis::client::draw2d::entities::simple_sprite::~simple_sprite()
{}

sanguis::client::draw2d::entities::simple_sprite::object_type const &
sanguis::client::draw2d::entities::simple_sprite::object() const
{
	return sprite_;
}

void
sanguis::client::draw2d::entities::simple_sprite::update(
	time_type
)
{}

void
sanguis::client::draw2d::entities::simple_sprite::pos(
	sprite::point const &pos_
)
{
	sprite_.pos(
		pos_
	);
}

void
sanguis::client::draw2d::entities::simple_sprite::dim(
	sprite::dim const &dim_
)
{
	sprite_.size(
		dim_
	);
}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::simple_sprite::center() const
{
	return
		sge::sprite::center(
			sprite_
		);
}

void
sanguis::client::draw2d::entities::simple_sprite::visible(
	bool const v
)
{
	sprite_.visible(v);
}
