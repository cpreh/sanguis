#ifndef SANGUIS_DRAW_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_HPP_INCLUDED

#include <sge/sprite/object.hpp>
#include <sge/math/vector.hpp>
#include <sge/console/console.hpp>
#include "entity.hpp"

namespace sanguis
{
namespace draw
{

class sprite : public entity {
public:
	sprite(
		entity_id id,
		sprite_vector::size_type init_sprites);
	const sge::sprite::point center() const;
	virtual sprite_vector to_sprites() const;
protected:
	typedef sprite_vector::iterator iterator;
	typedef sprite_vector::const_iterator const_iterator;

	virtual void update(time_type);
	sge::sprite::object& at(sprite_vector::size_type);
	const sge::sprite::object& at(sprite_vector::size_type) const;
	sge::sprite::object& master();
	const sge::sprite::object& master() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	virtual void orientation(sge::space_unit);
	virtual void speed(const sge::math::vector2&);
	virtual void pos(const sge::sprite::point&);
	virtual void dim(const sge::sprite::dim&);
	virtual void visible(bool);

	sge::sprite::rotation_type orientation() const;
	const sge::math::vector2& speed() const;
private:
	void update_pos(const sge::sprite::point&);
	void update_orientation(sge::sprite::rotation_type);

	sge::math::vector2         speed_,
	                           pos_;
	sprite_vector              sprites;
};

}
}

#endif
