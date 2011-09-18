#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_OBJECT_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/base.hpp>
#include <sanguis/client/draw2d/particle/depth.hpp>
#include <sanguis/client/draw2d/particle/particle_type.hpp>
#include <sanguis/client/draw2d/particle/rotation.hpp>
#include <sanguis/client/draw2d/sprite/particle/object.hpp>
#include <sanguis/client/draw2d/sprite/particle/texture_animation.hpp>
#include <sanguis/client/draw2d/sprite/particle/system.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/load/model/animation/context_ptr.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
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
