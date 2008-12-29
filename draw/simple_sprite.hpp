#ifndef SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED

#include "entity.hpp"
#include "system_fwd.hpp"
#include "object.hpp"
#include <sge/texture/part_fwd.hpp>
#include <sge/sprite/intrusive_order.hpp>

namespace sanguis
{
namespace draw
{

class simple_sprite : public entity {
public:
	simple_sprite(
		entity_id,
		draw::system &,
		sge::sprite::intrusive_order,
		sge::texture::const_part_ptr);
private:
	void update(time_type);
	void orientation(sge::sprite::rotation_type);
	void speed(vector2 const &);
	void pos(sge::sprite::point const &);
	void dim(sge::sprite::dim const &);
	void visible(bool);
	vector2 const &speed() const;
	sge::sprite::rotation_type orientation() const;
	object &get();
	object const &get() const;

	object sprite;
};

}
}

#endif
