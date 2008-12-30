#include "object.hpp"
#include <sge/iostream.hpp>
#include <sge/math/point_rotate.hpp>

sanguis::draw::particle::object::object(
	sge::sprite::animation_series const &images,
	boost::optional<time_type> const fade_total,
	draw::environment const &e)
:
	base(
		point::null(),
		point::null(),
		depth_type(0),
		rotation_type(0),
		rotation_type(0),
		e),
	sprite_(
		e.system(),
		static_cast<sge::sprite::intrusive_order>(0), // FIXME
		sge::sprite::defaults::pos_,
		sge::sprite::defaults::texture_,
		sge::math::structure_cast<sge::sprite::unit>(images.dim())),
	anim(
		images,
		fade_total 
			? sge::sprite::texture_animation::loop_method::repeat
			: sge::sprite::texture_animation::loop_method::stop_at_end,
		sprite_),
	fade_total(fade_total),
	fade_remaining(
		fade_total 
			? *fade_total 
			: static_cast<time_type>(0))
{}

bool sanguis::draw::particle::object::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d)
{
	base::update(delta,p,r,d);

	bool const ret = anim.process();

	if (!fade_total)
		return ret;
	
	fade_remaining -= delta;
	// UGLY ALERT!
	sge::renderer::color_channel_8 const max = 
		std::numeric_limits<sge::renderer::color_channel_8>::max();
	funit const ratio = static_cast<funit>(fade_remaining)/static_cast<funit>(*fade_total);
	sprite_.color(
		sge::renderer::rgba8_color(
			max,
			max,
			max,
			static_cast<sge::renderer::color_channel_8>(
				static_cast<funit>(max)*ratio)));

	sprite_.z() = d+base::depth();
	sprite_.rotation(base::rot()+r);
	sprite_.pos() = 
		sge::math::structure_cast<sge::sprite::unit>(
			sge::math::point_rotate(p+base::pos(),p,r+base::rot()));

	return fade_remaining < static_cast<funit>(0);
}
