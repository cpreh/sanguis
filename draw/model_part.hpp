#ifndef SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_PART_HPP_INCLUDED

#include "../animation_type.hpp"
#include "../weapon_type.hpp"
#include "../load/model/fwd.hpp"
#include <sge/sprite/fwd.hpp>
#include <sge/sprite/texture_animation.hpp>

namespace sanguis
{
namespace draw
{

class model_part {
public:
	model_part(
		load::model::part const&,
		sge::sprite::object &ref);
	void animation(animation_type::type);
	void weapon(weapon_type::type);
	void update();
private:
	void update_animation();
	sge::sprite::texture_animation::loop_method::type loop_method() const;

	load::model::part const*       info;
	sge::sprite::object*           ref;
	animation_type::type           animation_type_;
	weapon_type::type              weapon_type_;
	sge::sprite::texture_animation animation_;
};

}
}

#endif
