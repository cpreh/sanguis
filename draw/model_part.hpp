#ifndef SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED

#include "types.hpp"
#include "../animation_type.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include "../diff_clock.hpp"
#include "../load/model/fwd.hpp"
#include <sge/sprite/fwd.hpp>
#include <sge/sprite/types.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/time/types.hpp>
#include <boost/scoped_ptr.hpp>

namespace sanguis
{
namespace draw
{

class model_part {
public:
	model_part(
		load::model::part const &,
		object &ref);
	void animation(animation_type::type);
	void weapon(weapon_type::type);
	void update(time_type time);
	void orientation(sge::sprite::rotation_type);
private:
	void update_animation();
	void update_orientation(
		sge::sprite::rotation_type);
	sge::sprite::texture_animation::loop_method::type loop_method() const;
	sge::sprite::rotation_type orientation() const;

	diff_clock                              anim_diff_clock;
	sge::sprite::rotation_type              desired_orientation;
	load::model::part const*                info;
	object*                                 ref;
	animation_type::type                    animation_type_;
	weapon_type::type                       weapon_type_;
	boost::scoped_ptr<
		sge::sprite::texture_animation> animation_;
	bool                                    ended;
};

}
}

#endif
