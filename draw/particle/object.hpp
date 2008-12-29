#ifndef SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED

#include "base.hpp"
#include <sge/sprite/texture_animation.hpp>
#include <sge/sprite/object.hpp>
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
		sge::sprite::animation_series const &,
		boost::optional<time_type> fade_time);
	bool update(time_type);
	void gather(
		point const &,
		rotation_type,
		depth_type,
		sge::sprite::container &) const;
	private:
	sge::sprite::object sprite_;
	sge::sprite::texture_animation anim;
	boost::optional<time_type> fade_total;
	time_type fade_remaining;
};

}
}
}

#endif
