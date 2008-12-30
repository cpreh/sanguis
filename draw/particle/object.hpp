#ifndef SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED

#include "base.hpp"
#include <sge/sprite/texture_animation.hpp>
#include <sge/sprite/intrusive_object.hpp>
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
		boost::optional<time_type> fade_time,
		draw::environment const &);
	bool update(
		time_type,
		point const &,
		rotation_type,
		depth_type);
	private:
	sge::sprite::intrusive_object sprite_;
	sge::sprite::texture_animation anim;
	boost::optional<time_type> fade_total;
	time_type fade_remaining;
};

}
}
}

#endif
