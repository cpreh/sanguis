#ifndef SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_OBJECT_HPP_INCLUDED

#include "base.hpp"
#include "../sprite/particle/object.hpp"
#include "../sprite/particle/texture_animation.hpp"
#include "../../particle_type.hpp"
#include "../../diff_clock.hpp"
#include "../../load/model/animation.hpp"
#include <sge/sprite/object_decl.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/optional_decl.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{

class object : public base
{
public:
	typedef sge::optional<time_type> optional_time;

	object(
		particle_type::type,
		funit aoe,
		load::model::animation::context_ptr,
		optional_time fade_time,
		draw::environment const &
	);

	~object();

	bool update(
		time_type,
		point const &,
		rotation_type,
		depth_type
	);

private:
	draw::sprite::particle::object sprite_;
	diff_clock clock_;
	load::model::animation::context_ptr animation_context_;
	sge::scoped_ptr<
		sprite::particle::texture_animation
	> animation_;
	optional_time fade_total_;
	time_type fade_remaining_;
};

}
}
}

#endif
