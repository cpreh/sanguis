#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED

#include "part_state_fwd.hpp"
#include "../../sprite/normal/object.hpp"
#include "../../sprite/normal/texture_animation.hpp"
#include "../../sprite/rotation_type.hpp"
#include "../../../../animation_type.hpp"
#include "../../../../weapon_type.hpp"
#include "../../../../time_type.hpp"
#include "../../../../diff_clock.hpp"
#include "../../../../load/model/part_fwd.hpp"
#include "../../../../load/model/animation_context_fwd.hpp"
#include <sge/sprite/animation/loop_method.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class part
{
	FCPPT_NONCOPYABLE(part)
public:
	part(
		load::model::part const &,
		sprite::normal::object &ref
	);

	~part();

	bool
	try_animation(
		animation_type::type
	);

	void
	weapon(
		weapon_type::type
	);

	void
	update(
		time_type
	);

	void
	orientation(
		sprite::rotation_type
	);

	bool
	animation_ended() const;

	sprite::normal::object &
	object();

	sprite::normal::object const &
	object() const;
private:
	friend class part_state;

	typedef fcppt::scoped_ptr<
		load::model::animation_context
	> animation_context_ptr;
	
	typedef fcppt::auto_ptr<
		sprite::normal::texture_animation
	> animation_auto_ptr;

	void
	load_animation(
		animation_type::type
	);
	
	void
	update_orientation(
		sprite::rotation_type
	);

	static sge::sprite::animation::loop_method::type
	loop_method(
		animation_type::type
	);

	sprite::rotation_type
	orientation() const;

	diff_clock anim_diff_clock_;

	sprite::rotation_type desired_orientation_;

	load::model::part const &load_part_;

	sprite::normal::object &ref_;

	weapon_type::type weapon_;

	typedef fcppt::scoped_ptr<
		part_state
	> part_state_ptr;

	part_state_ptr state_;

	animation_context_ptr animation_context_;
	
	typedef fcppt::scoped_ptr<
		sprite::normal::texture_animation
	> scoped_texture_animation;

	scoped_texture_animation animation_;

	bool ended_;
};

}
}
}
}
}

#endif
