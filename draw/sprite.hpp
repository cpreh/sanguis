#ifndef SANGUIS_DRAW_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_HPP_INCLUDED

#include <sge/sprite/object.hpp>
#include <sge/math/vector.hpp>
#include "entity.hpp"

namespace sanguis
{
namespace draw
{

class sprite : public entity {
public:
	sprite(
		entity_id id,
		const sge::math::vector2& speed,
		sprite_vector::size_type init_sprites);
	sprite_vector to_sprites() const;
	const sge::sprite::point center() const;
protected:
	virtual void update(time_type);
	sge::sprite::object& at(sprite_vector::size_type);
	const sge::sprite::object& at(sprite_vector::size_type) const;
	sge::sprite::object& master();
	const sge::sprite::object& master() const;

	virtual void orientation(sge::space_unit);
	virtual void speed(const sge::math::vector2&);
	virtual void pos(const sge::sprite::point&);
	virtual void dim(const sge::sprite::dim&);

	sge::space_unit orientation() const;
	const sge::math::vector2& speed() const;
private:
	void update_pos(const sge::sprite::point&);

	sge::math::vector2 speed_;
	sprite_vector      sprites;
	sge::math::vector2 pos_;
};

}
}

#endif
