#ifndef DRAW_SPRITE_HPP_INCLUDED
#define DRAW_SPRITE_HPP_INCLUDED

#include <sge/sprite/sprite.hpp>
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
		const sge::math::vector2& speed);
	sprite(
		entity_id id,
		const sge::sprite::point& pos,
		const sge::sprite::dim& dim,
		sge::virtual_texture_ptr tex,
		sge::sprite::rotation_type angle,
		const sge::math::vector2& speed,
		const sge::space_unit z);
	sprite_vector to_sprites() const;
	const sge::sprite::point center() const;
protected:
	virtual void update(time_type);
	sge::sprite& at(sprite_vector::size_type);
	const sge::sprite& at(sprite_vector::size_type) const;
	void add_sprite(const sge::sprite&);
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
	sge::space_unit    health_;
};

}
}

#endif
