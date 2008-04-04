#ifndef SANGUIS_DRAW_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_HPP_INCLUDED

#include <sge/sprite/object.hpp>
#include <sge/math/vector.hpp>
#include "entity.hpp"

namespace sanguis
{
namespace draw
{
namespace relative_pos
{
enum type {
	topleft,
	center
};
}

class sprite : public entity {
public:
	sprite(
		entity_id id,
		const sge::math::vector2& speed,
		const sge::sprite::object& master,
		relative_pos::type);
	sprite_vector to_sprites() const;
	const sge::sprite::point center() const;
protected:
	virtual void update(time_type);
	sge::sprite::object& at(sprite_vector::size_type);
	const sge::sprite::object& at(sprite_vector::size_type) const;
	sge::sprite::object& master();
	const sge::sprite::object& master() const;
	void add_sprite(const sge::sprite::object&);
	virtual void orientation(sge::space_unit);
	virtual void speed(const sge::math::vector2&);
	void pos(const sge::sprite::point&);
	void dim(const sge::sprite::dim&);
	sge::space_unit orientation() const;
	const sge::math::vector2& speed() const;
private:
	void update_pos(const sge::sprite::point&);

	sge::math::vector2 speed_;
	sprite_vector      sprites;
	sge::math::vector2 pos_;
	relative_pos::type relative;
};

}
}

#endif
