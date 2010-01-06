#include "simple_sprite.hpp"
#include "sprite/client/parameters.hpp"
#include "sprite/point.hpp"
#include <fcppt/math/compare.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>

sanguis::client::draw2d::simple_sprite::simple_sprite(
	sprite::client::system &system_,		
	sprite::order const order,
	sge::texture::const_part_ptr const tex,
	sprite::client::repetition_type const _repeat
)
:
	entity(),
	sprite_(
		sprite::client::parameters()
		.pos(
			sprite::point::null()
		)
		.system(
			system_
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

sanguis::client::draw2d::simple_sprite::~simple_sprite()
{}

void
sanguis::client::draw2d::simple_sprite::update(
	time_type
)
{}

void
sanguis::client::draw2d::simple_sprite::pos(
	sprite::point const &pos_
)
{
	sprite_.pos(
		pos_
	);
}

void
sanguis::client::draw2d::simple_sprite::dim(
	sprite::dim const &dim_
)
{
	sprite_.size(
		dim_
	);
}

void
sanguis::client::draw2d::simple_sprite::visible(
	bool const v
)
{
	sprite_.visible(v);
}
