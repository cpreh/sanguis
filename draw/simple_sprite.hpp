#ifndef SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED

#include "entity.hpp"
#include "types.hpp"
#include <sge/sprite/types.hpp>

namespace sanguis
{
namespace draw
{

class simple_sprite : public entity {
public:
	simple_sprite(
		entity_id,
		system &,
		object::order_type,
		sge::texture::part_ptr);
private:
	void update(time_type);
	void orientation(sge::sprite::rotation_type);
	void speed(sge::math::vector2 const&);
	void pos(sge::sprite::point const&);
	void dim(sge::sprite::dim const&);
	void visible(bool);
	sge::math::vector2 const& speed() const;
	sge::sprite::rotation_type orientation() const;
	object &get();
	object const &get() const;

	object sprite;
};

}
}

#endif
