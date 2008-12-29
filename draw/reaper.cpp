#include "reaper.hpp"
#include "z_ordering.hpp"
#include "object.hpp"
#include "../resolution.hpp"
#include <sge/math/compare.hpp>
#include <sge/math/signum.hpp>
#include <cmath>
#include <cassert>

namespace
{

sanguis::draw::funit const
	health_regain = static_cast<sanguis::draw::funit>(5);

}

sanguis::draw::reaper::reaper(
	environment const &env,
	entity_id const id,
	draw::system &sys,
	model const &p)
:
	model(
		env,
		id,
		sys,
		SGE_TEXT("reaper"),
		z_ordering::reaper,
		false,
		static_cast<funit>(1)),
	p(p),
	current_health(p.health()),
	target_health(p.health()),
	inited(false)
{
	color(
		sge::renderer::rgba8_color(
			static_cast<sge::renderer::color_channel_8>(255),
			static_cast<sge::renderer::color_channel_8>(255),
			static_cast<sge::renderer::color_channel_8>(255),
			static_cast<sge::renderer::color_channel_8>(128)));
}

void sanguis::draw::reaper::update(time_type const t)
{
	assert(!sge::math::almost_zero(p.max_health()));

	orientation(static_cast<funit>(0));

	if (!sge::math::nearly_equals(target_health,p.health()))
	{
		if (!inited)
		{
			target_health = current_health = p.health();
			inited = true;
		}
		else
		{
			target_health = p.health();
			// just set some speed so the walking animation is played
			speed(vector2(static_cast<funit>(1),static_cast<funit>(0)));
		}
	}

	const bool regain = std::abs(current_health - target_health) > health_regain * t;

	// reset speed if target is reached
	if (!regain)
		speed(vector2::null());
	else
		speed(vector2(static_cast<funit>(1), static_cast<funit>(0)));
	
	model::update(t);

	// use own positioning system, not the one from model::update
	pos(
		p.pos() -
			sge::sprite::point(
				static_cast<sge::sprite::unit>(
					static_cast<funit>(current_health)/static_cast<funit>(p.max_health())*static_cast<funit>(resolution().w()/4)),
				static_cast<sge::sprite::unit>(0)));
	
	if (regain)
		current_health += sge::math::signum(target_health - current_health) * health_regain * static_cast<funit>(t);
}
