#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_OBJECT_HPP_INCLUDED

#include "base.hpp"
#include "../sprite/particle/object.hpp"
#include "../sprite/particle/texture_animation.hpp"
#include "../sprite/particle/system.hpp"
#include "../../../particle_type.hpp"
#include "../../../diff_clock.hpp"
#include "../../../load/model/animation_context_ptr.hpp"
#include <sge/sprite/object_decl.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/noncopyable.hpp>

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
	public base
{
	FCPPT_NONCOPYABLE(object)
public:
	typedef fcppt::optional<time_type> optional_time;

	object(
		particle_type::type,
		funit aoe,
		load::model::animation_context_ptr,
		optional_time fade_time,
		sprite::particle::system &
	);

	~object();

	bool update(
		time_type,
		point const &,
		rotation_type,
		depth_type
	);
private:
	draw2d::sprite::particle::object sprite_;

	diff_clock clock_;

	load::model::animation_context_ptr animation_context_;

	fcppt::scoped_ptr<
		sprite::particle::texture_animation
	> animation_;

	optional_time fade_total_;

	time_type fade_remaining_;
};

}
}
}
}

#endif