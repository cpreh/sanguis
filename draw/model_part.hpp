#ifndef SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED

#include "model_part_state_fwd.hpp"
#include "funit.hpp"
#include "sprite/normal/object.hpp"
#include "sprite/normal/texture_animation.hpp"
#include "sprite/rotation_type.hpp"
#include "../animation_type.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include "../diff_clock.hpp"
#include "../load/model/fwd.hpp"
#include "../animation_state.hpp"
#include "../load/model/animation_context_fwd.hpp"
#include <sge/sprite/animation/loop_method.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace draw
{

class model_part {
public:
	model_part(
		load::model::part const &,
		sprite::normal::object &ref
	);

	~model_part();

	bool try_animation(
		animation_type::type);
	void weapon(
		weapon_type::type);
	void update(
		time_type);
	void orientation(
		sprite::rotation_type);
	bool animation_ended() const;

	sprite::normal::object &
	object();

	sprite::normal::object const &
	object() const;
private:
	friend class model_part_state;

	typedef sge::scoped_ptr<load::model::animation_context> animation_context_ptr;
	
	typedef sge::auto_ptr<
		sprite::normal::texture_animation
	> animation_auto_ptr;

	void load_animation(
		animation_type::type);
	
	void update_orientation(
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

	weapon_type::type                       weapon_;
	typedef sge::scoped_ptr<model_part_state> model_part_state_ptr;
	model_part_state_ptr                    state_;
	animation_context_ptr                   animation_context_;
	
	typedef sge::scoped_ptr<
		sprite::normal::texture_animation
	> scoped_texture_animation;

	scoped_texture_animation                animation_;
	bool                                    ended_;
};

}
}

#endif
