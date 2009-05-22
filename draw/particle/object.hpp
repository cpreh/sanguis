#ifndef SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED

#include "base.hpp"
#include "../object.hpp"
#include "../../particle_type.hpp"
#include "../../diff_clock.hpp"
#include <sge/sprite/texture_animation.hpp>
#include <sge/sprite/container.hpp>
#include <boost/optional.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{

class object : public base
{
	public:
	object(
		particle_type::type,
		funit aoe,
		sge::sprite::animation_series const &,
		boost::optional<time_type> fade_time,
		draw::environment const &);
	bool update(
		time_type,
		point const &,
		rotation_type,
		depth_type);
	private:
	draw::object sprite_;
	diff_clock clock;
	sge::sprite::texture_animation anim;
	boost::optional<time_type> fade_total;
	time_type fade_remaining;
};

}
}
}

#endif
