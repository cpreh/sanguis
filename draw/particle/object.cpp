#include "object.hpp"
#include "z_ordering.hpp"
#include <sge/sprite/intrusive/parameters.hpp>
#include <sge/math/point_rotate.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>

sanguis::draw::particle::object::object(
	particle_type::type const t,
	funit const aoe,
	sge::sprite::animation_series const &images,
	boost::optional<time_type> const fade_total,
	draw::environment const &e)
:
	base(
		point(
			static_cast<funit>(-images.dim().w()/2),
			static_cast<funit>(-images.dim().h()/2)),
		point::null(),
		depth_type(0),
		rotation_type(0),
		rotation_type(0),
		e),
	sprite_(
		sge::sprite::intrusive::parameters(
			e.system(),
			z_ordering(t)
		)
		.size(
			/*
			sge::math::dim::structure_cast<
				sge::sprite::dim
			>(
				images.dim()
			)
			*/
			// TODO: maybe resize with respect to the images.dim() ratio here
			sge::sprite::dim(
				static_cast<sge::sprite::unit>(2*aoe),
				static_cast<sge::sprite::unit>(2*aoe))
		)
	),
	anim(
		images,
		fade_total 
			? sge::sprite::texture_animation::loop_method::repeat
			: sge::sprite::texture_animation::loop_method::stop_at_end,
		sprite_,
		clock.callback()),
	fade_total(fade_total),
	fade_remaining(
		fade_total 
			? *fade_total 
			: static_cast<time_type>(0))
{
}

bool sanguis::draw::particle::object::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d)
{
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

	clock.update(delta);

	bool const ret = anim.process();

	if (!fade_total)
		return ret;
	
	fade_remaining -= delta;

	funit const ratio(
		static_cast<funit>(
			fade_remaining
		)
		/ static_cast<funit>(
			*fade_total
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
					sge::image::color::rgba8::layout::channel_max<
						mizuiro::color::channel::alpha
					>()
				)
				* ratio
			)
		)
	);

	return fade_remaining < static_cast<funit>(0);
}
