#include "object.hpp"
#include "z_ordering.hpp"
#include "../sprite/particle/parameters.hpp"
#include "../sprite/particle/texture_animation.hpp"
#include "../sprite/point.hpp"
#include "../sprite/dim.hpp"
#include "../../../load/model/animation_context.hpp"
#include <sge/sprite/animation/texture_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/center.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <fcppt/math/point_rotate.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional_impl.hpp>
#include <algorithm>

sanguis::client::draw2d::particle::object::object(
	particle_type::type const _type,
	funit const _aoe,
	load::model::animation_context_ptr _animation_context,
	optional_time const _fade_total,
	sprite::particle::system &particle_system_
)
:
	base(
		point::null(),
		point::null(),
		depth_type(0),
		rotation_type(0),
		rotation_type(0)
	),
	sprite_(
		sprite::particle::parameters()
		.system(
			&particle_system_
		)
		.order(
			z_ordering(
				_type
			)
		)
		.size(
			// TODO: maybe resize with respect to the images.dim() ratio here
			sprite::dim(
				static_cast<sprite::unit>(
					2*_aoe
				),
				static_cast<sprite::unit>(
					2*_aoe
				)
			)
		)
		.color(
			sge::image::color::rgba8(
			sge::image::color::init::red %= 1.0,
			sge::image::color::init::green %= 1.0,
			sge::image::color::init::blue %= 1.0,
			sge::image::color::init::alpha %= 1.0))
		.elements()
	),
	animation_context_(
		_animation_context),
	animation_(),
	fade_total_(
		_fade_total),
	fade_remaining_(
		fade_total_
			? *fade_total_
			: static_cast<time_type>(0))
{
}

sanguis::client::draw2d::particle::object::~object()
{
}

bool
sanguis::client::draw2d::particle::object::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d
)
{
	animation_context_->update();
	if (!animation_ && animation_context_->is_finished())
		animation_.reset(
			new sprite::particle::texture_animation(
				animation_context_->result(),
				fade_total_ 
					? sge::sprite::animation::loop_method::repeat
					: sge::sprite::animation::loop_method::stop_at_end,
				sprite_,
				clock_.callback()
			)
		);

	base::update(delta,p,r,d);

	sprite_.z(
		d + base::depth()
	);

	sprite_.rotation(
		base::rot() + r
	);

	sge::sprite::center( 
		sprite_,
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			fcppt::math::point_rotate(
				p + base::pos(),
				p,
				r + base::rot()
			)
		)
	);

	clock_.update(
		delta
	);

	bool const ret = animation_ ? animation_->process() : false;
	if (!fade_total_)
		return ret;
	
	fade_remaining_ -= delta;

	funit const ratio(
		static_cast<funit>(
			fade_remaining_
		)
		/ static_cast<funit>(
			*fade_total_
		)
	);

	sprite_.color(
		sge::image::color::rgba8(
			sge::image::color::init::red %= 1.0,
			sge::image::color::init::green %= 1.0,
			sge::image::color::init::blue %= 1.0,
			sge::image::color::init::alpha %=
				std::max(
					static_cast<funit>(0),
					ratio
				)
		)
	);

	return fade_remaining_ < static_cast<funit>(0);
}
