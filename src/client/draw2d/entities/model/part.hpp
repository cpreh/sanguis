#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED

#include "sound_state_fwd.hpp"
#include "../../sprite/normal/object.hpp"
#include "../../sprite/normal/texture_animation.hpp"
#include "../../sprite/rotation.hpp"
#include "../../../../animation_type.hpp"
#include "../../../../diff_clock.hpp"
#include "../../../../time_delta_fwd.hpp"
#include "../../../../weapon_type.hpp"
#include "../../../../load/model/part_fwd.hpp"
#include "../../../../load/model/animation/context_fwd.hpp"
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr.hpp>

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
	FCPPT_NONCOPYABLE(
		part
	);
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
		sanguis::time_delta const &
	);

	void
	orientation(
		sprite::rotation
	);

	bool
	ended() const;

	sprite::normal::object &
	object();

	sprite::normal::object const &
	object() const;
private:
	typedef fcppt::scoped_ptr<
		load::model::animation::context
	> animation_context_ptr;
	
	void
	load_animation(
		animation_type::type
	);
	
	void
	update_orientation(
		sprite::rotation
	);

	sprite::rotation
	orientation() const;

	diff_clock anim_diff_clock_;

	typedef fcppt::optional<
		sprite::rotation
	> optional_rotation;

	optional_rotation desired_orientation_;

	load::model::part const &load_part_;

	sprite::normal::object &ref_;

	sanguis::animation_type::type animation_type_;

	weapon_type::type weapon_;

	typedef fcppt::scoped_ptr<
		model::sound_state
	> sound_state_ptr;

	sound_state_ptr sound_state_;

	animation_context_ptr animation_context_;
	
	typedef fcppt::scoped_ptr<
		sprite::normal::texture_animation
	> scoped_texture_animation;

	scoped_texture_animation animation_;

	bool animation_ended_;
};

}
}
}
}
}

#endif
