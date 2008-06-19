#include "reaper.hpp"
#include "z_ordering.hpp"
#include "../resolution.hpp"
#include <sge/math/compare.hpp>
#include <sge/math/signum.hpp>
#include <sge/sprite/types.hpp>
#include <sge/su.hpp>
#include <sge/iostream.hpp>
#include <cmath>
#include <cassert>

namespace
{
const sge::space_unit health_regain = sge::su(5);
}

sanguis::draw::reaper::reaper(entity_id id,player const &p)
	: model(id,SGE_TEXT("reaper")),
	  p(p),
		current_health(p.health()),
		target_health(p.health()),
		inited(false)
{
	for (iterator i = begin(); i != end(); ++i)
	{
		i->z() = z_ordering::reaper;
		i->set_color(
			sge::renderer::make_color_rgba(
				static_cast<sge::renderer::pixel_channel_8>(255),
				static_cast<sge::renderer::pixel_channel_8>(255),
				static_cast<sge::renderer::pixel_channel_8>(255),
				static_cast<sge::renderer::pixel_channel_8>(128)));
	}
}

void sanguis::draw::reaper::update(time_type const t)
{
	assert(!sge::math::almost_zero(p.max_health()));

	orientation(sge::su(0));

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
			speed(sge::math::vector2(sge::su(1),sge::su(0)));
		}
	}

	const bool regain = std::abs(current_health - target_health) > health_regain * t;

	// reset speed if target is reached
	if (!regain)
		speed(sge::math::vector2());
	else
		speed(sge::math::vector2(sge::su(1),sge::su(0)));
	
	model::update(t);

	// use own positioning system, not the one from model::update
	pos(
		p.pos()-
			sge::sprite::point(
				static_cast<sge::sprite::unit>(sge::su(current_health)/sge::su(p.max_health())*sge::su(resolution().w()/4)),
				static_cast<sge::sprite::unit>(0)));
	
	if (regain)
		current_health += sge::math::signum(target_health - current_health) * health_regain * sge::su(t);
}
