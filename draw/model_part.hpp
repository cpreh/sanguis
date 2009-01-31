#ifndef SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED

#include "object_fwd.hpp"
#include "funit.hpp"
#include "../animation_type.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include "../diff_clock.hpp"
#include "../load/model/fwd.hpp"
#include <sge/sprite/texture_animation.hpp> // TODO: fwd this too!
#include <sge/sprite/rotation_type.hpp>
#include <boost/scoped_ptr.hpp>
#include <memory>

namespace sanguis
{
namespace draw
{

class model_part_state;

class model_part {
public:
	model_part(
		load::model::part const &,
		object &ref);
	~model_part();

	bool animation(animation_type::type);
	void weapon(weapon_type::type);
	void update(time_type time);
	void orientation(sge::sprite::rotation_type);
	bool animation_ended() const;
private:
	typedef std::auto_ptr<
		sge::sprite::texture_animation
	> animation_auto_ptr;

	bool try_animation(
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
	load::model::part const*                info;
	object*                                 ref;

	weapon_type::type                       weapon_;
	boost::scoped_ptr<model_part_state>     state;
	
	typedef boost::scoped_ptr<
		sge::sprite::texture_animation
	> scoped_texture_animation;
	scoped_texture_animation                animation_;
	bool                                    ended;
};

}
}

#endif
