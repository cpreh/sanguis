#ifndef SANGUIS_DRAW_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_HPP_INCLUDED

#include "types.hpp"
#include "entity.hpp"
#include <sge/math/vector.hpp>

namespace sanguis
{
namespace draw
{

class sprite : public entity {
public:
	sprite(
		entity_id id,
		system &sys,
		sprite_vector::size_type init_sprites);
	sge::sprite::point const center() const;
protected:
	typedef sprite_vector::iterator iterator;
	typedef sprite_vector::const_iterator const_iterator;

	virtual void update(time_type);
	object &at(sprite_vector::size_type);
	object const &at(sprite_vector::size_type) const;
	object &master();
	object const &master() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	sge::math::vector2 pos() const;

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
