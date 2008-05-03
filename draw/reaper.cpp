#include "reaper.hpp"
#include "z_ordering.hpp"
#include "../resolution.hpp"
#include <sge/math/compare.hpp>
#include <sge/math/signum.hpp>
#include <sge/sprite/types.hpp>
#include <sge/su.hpp>
#include <sge/iostream.hpp>
#include <cassert>

namespace
{
const sge::space_unit health_regain = sge::su(20);
}

sanguis::draw::reaper::reaper(entity_id id,player const &p)
	: model(id,SGE_TEXT("reaper")),
	  p(p),
		current_health(p.health()),
		target_health(p.health())
{
	for (iterator i = begin(); i != end(); ++i)
	{
		i->z() = z_ordering::reaper;
		i->set_color(sge::make_color(static_cast<sge::color_element>(255),static_cast<sge::color_element>(255),static_cast<sge::color_element>(255),static_cast<sge::color_element>(128)));
	}
}

void sanguis::draw::reaper::update(time_type const t)
{
	assert(!sge::math::almost_zero(p.max_health()));

	orientation(sge::su(0));

	if (!sge::math::nearly_equals(target_health,p.health()))
	{
		target_health = p.health();
		// just set some speed so the walking animation is played
		speed(sge::math::vector2(sge::su(1),sge::su(0)));
	}

	// reset speed if target is reached
	if (sge::math::nearly_equals(current_health,target_health))
		speed(sge::math::vector2());
	
	model::update(t);

	// use own positioning system, not the one from model::update
	pos(
		p.pos()-
			sge::sprite::point(
				static_cast<sge::sprite::unit>(sge::su(current_health)/sge::su(p.max_health())*sge::su(resolution().w()/4)),
				static_cast<sge::sprite::unit>(0)));
	
	current_health += sge::math::signum(target_health - current_health) * health_regain * sge::su(t);
}
