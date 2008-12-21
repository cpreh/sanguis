#include "object.hpp"
#include <sge/iostream.hpp>
#include <sge/math/point_rotate.hpp>

sanguis::draw::particle::object::object(
	sge::sprite::animation_series const &images,
	boost::optional<time_type> const fade_total)
:
	base(
		point::null(),
		point::null(),
		depth_type(0),
		rotation_type(0),
		rotation_type(0)),
	sprite_(
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

void sanguis::draw::particle::object::gather(
	point const &p,
	rotation_type const r,
	depth_type const d,
	sge::sprite::system::container &c) const
{
	sge::sprite::object temp = sprite_;
	temp.z() = d+base::depth();
	temp.rotation(base::rot()+r);
	temp.pos() = 
		sge::math::structure_cast<sge::sprite::unit>(
			sge::math::point_rotate(p+base::pos(),p,r+base::rot()));
	c.push_back(temp);
}

bool sanguis::draw::particle::object::update(time_type const delta)
{
	base::update(delta);

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

	return fade_remaining < static_cast<funit>(0);
}
