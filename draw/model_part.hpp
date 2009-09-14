#ifndef SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED

#include "model_part_state_fwd.hpp"
#include "object_fwd.hpp"
#include "funit.hpp"
#include "../animation_type.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include "../diff_clock.hpp"
#include "../load/model/fwd.hpp"
#include "../animation_state.hpp"
#include <sge/sprite/texture_animation.hpp> // TODO: fwd this too!
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
		sanguis::draw::object &ref);
	~model_part();

	animation_state::type animation(animation_type::type);
	void weapon(weapon_type::type);
	void update(time_type time);
	void orientation(sge::sprite::rotation_type);
	bool animation_ended() const;
	sanguis::draw::object &object();
	sanguis::draw::object const &object() const;
private:
	friend class model_part_state;
	
	typedef sge::auto_ptr<
		sge::sprite::texture_animation
	> animation_auto_ptr;

	animation_state::type try_animation(
		animation_type::type);
	
	animation_auto_ptr get_animation(
		weapon_type::type,
		animation_type::type);
	
	void update_orientation(
		sge::sprite::rotation_type);

	static sge::sprite::texture_animation::loop_method::type
	loop_method(
		animation_type::type);
	sge::sprite::rotation_type orientation() const;

	diff_clock                              anim_diff_clock;
	sge::sprite::rotation_type              desired_orientation;
	load::model::part const*                info_;
	sanguis::draw::object*                  ref_;

	weapon_type::type                       weapon_;
	sge::scoped_ptr<model_part_state>       state_;
	
	typedef sge::scoped_ptr<
		sge::sprite::texture_animation
	> scoped_texture_animation;
	scoped_texture_animation                animation_;
	bool                                    ended_;
};

}
}

#endif
