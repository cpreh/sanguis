#ifndef SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED

#include "../animation_type.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include "../load/model/fwd.hpp"
#include <sge/sprite/fwd.hpp>
#include <sge/sprite/types.hpp>
#include <sge/sprite/texture_animation.hpp>

namespace sanguis
{
namespace draw
{

class model_part {
public:
	model_part(
		load::model::part const &,
		sge::sprite::object &ref);
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

	sge::sprite::rotation_type     desired_orientation;
	load::model::part const*       info;
	sge::sprite::object*           ref;
	animation_type::type           animation_type_;
	weapon_type::type              weapon_type_;
	sge::sprite::texture_animation animation_;
	bool                           ended;
};

}
}

#endif
