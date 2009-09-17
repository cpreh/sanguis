#ifndef SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED

#include "base.hpp"
#include "../object.hpp"
#include "../../particle_type.hpp"
#include "../../diff_clock.hpp"
#include "../../load/model/animation.hpp"
#include <sge/sprite/texture_animation_fwd.hpp>
#include <sge/scoped_ptr.hpp>
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
		load::model::animation::context_ptr,
		boost::optional<time_type> fade_time,
		draw::environment const &);
	bool update(
		time_type,
		point const &,
		rotation_type,
		depth_type);
	private:
	draw::object sprite_;
	diff_clock clock_;
	load::model::animation::context_ptr animation_context_;
	sge::scoped_ptr<sge::sprite::texture_animation> animation_;
	boost::optional<time_type> fade_total_;
	time_type fade_remaining_;
};

}
}
}

#endif
