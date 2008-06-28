#ifndef SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED

#include "entity.hpp"
#include <sge/sprite/types.hpp>
#include <sge/sprite/object.hpp>

namespace sanguis
{
namespace draw
{

class simple_sprite : public entity {
public:
	simple_sprite(
		entity_id,
		sge::sprite::point const&,
		sge::sprite::dim const&,
		sge::sprite::depth_type,
		sge::sprite::rotation_type,
		sge::texture::part_ptr);
	simple_sprite(
		entity_id,
		sge::sprite::depth_type,
		sge::texture::part_ptr);
private:
	void update(time_type);
	sprite_vector to_sprites() const;
	void orientation(sge::sprite::rotation_type);
	void speed(sge::math::vector2 const&);
	void pos(sge::sprite::point const&);
	void dim(sge::sprite::dim const&);
	void visible(bool);
	sge::math::vector2 const& speed() const;
	sge::sprite::rotation_type orientation() const;
	sge::sprite::object& get();
	sge::sprite::object const& get() const;

	sprite_vector sprite;
};

}
}

#endif
