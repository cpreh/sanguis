#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_OBJECT_HPP_INCLUDED

#include "base.hpp"
#include "depth.hpp"
#include "particle_type.hpp"
#include "rotation.hpp"
#include "../sprite/particle/object.hpp"
#include "../sprite/particle/texture_animation.hpp"
#include "../sprite/particle/system.hpp"
#include "../aoe.hpp"
#include "../center.hpp"
#include "../../../diff_clock_fwd.hpp"
#include "../../../diff_timer.hpp"
#include "../../../duration.hpp"
#include "../../../load/model/animation/context_ptr.hpp"
#include <sge/sprite/object_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

class object
:
	public particle::base
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef fcppt::optional<
		sanguis::duration
	> optional_time;

	object(
		sanguis::diff_clock const &,
		particle_type::type,
		draw2d::aoe,
		load::model::animation::context_ptr,
		optional_time fade_time,
		sprite::particle::system &
	);

	~object();

	bool
	update(
		draw2d::center const &,
		particle::rotation,
		particle::depth
	);
private:
	sanguis::diff_clock const &diff_clock_;

	draw2d::sprite::particle::object sprite_;

	load::model::animation::context_ptr animation_context_;

	fcppt::scoped_ptr<
		sprite::particle::texture_animation
	> animation_;

	optional_time fade_total_;

	sanguis::diff_timer fade_timer_;
};

}
}
}
}

#endif
