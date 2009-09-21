#include "object.hpp"
#include "z_ordering.hpp"
#include "../../load/model/animation_context.hpp"
#include <sge/sprite/texture_animation.hpp>
#include <sge/sprite/intrusive/parameters.hpp>
#include <sge/math/point_rotate.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>

sanguis::draw::particle::object::object(
	particle_type::type const _type,
	funit const _aoe,
	load::model::animation::context_ptr _animation_context,
	boost::optional<time_type> const _fade_total,
	draw::environment const &_e)
:
	base(
		point::null(),
		point::null(),
		depth_type(0),
		rotation_type(0),
		rotation_type(0),
		_e),
	sprite_(
		sge::sprite::intrusive::parameters(
			_e.system(),
			z_ordering(
				_type))
		.size(
			// TODO: maybe resize with respect to the images.dim() ratio here
			sge::sprite::dim(
				static_cast<sge::sprite::unit>(
					2*_aoe),
				static_cast<sge::sprite::unit>(
					2*_aoe)))),
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

bool sanguis::draw::particle::object::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d)
{
	animation_context_->update();
	if (!animation_ && animation_context_->is_finished())
		animation_.reset(
			new sge::sprite::texture_animation(
				animation_context_->result(),
				fade_total_ 
					? sge::sprite::texture_animation::loop_method::repeat
					: sge::sprite::texture_animation::loop_method::stop_at_end,
				sprite_,
				clock_.callback()
			)
		);

	base::update(delta,p,r,d);

	sprite_.z() = d+base::depth();
	sprite_.rotation(base::rot()+r);
	sprite_.center( 
		sge::math::vector::structure_cast<
			sge::sprite::point
		>(
			sge::math::point_rotate(
				p + base::pos(),
				p,
				r + base::rot())));

	clock_.update(
		delta);

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
			sge::image::color::init::alpha =
			static_cast<
				sge::image::color::channel8
			>(
				static_cast<funit>(
					sge::image::color::rgba8::format::channel_max<
						mizuiro::color::channel::alpha
					>()
				)
				* ratio
			)
		)
	);

	return fade_remaining_ < static_cast<funit>(0);
}
