#ifndef SANGUIS_DRAW_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_HPP_INCLUDED

#include "types.hpp"
#include "entity.hpp"
#include <sge/math/vector.hpp>

namespace sanguis
{
namespace draw
{

class sprite_part_index;

class sprite : public entity {
public:
	sprite(
		entity_id id,
		system &sys,
		sprite_vector::size_type init_sprites,
		object::order_type order);
	
	sge::sprite::point const center() const;
	sge::sprite::point const pos() const;
protected:
	typedef sprite_vector::iterator iterator;
	typedef sprite_vector::const_iterator const_iterator;

	virtual void update(time_type);
	object &at(sprite_part_index const &);
	object const &at(sprite_part_index const &) const;
	object &master();
	object const &master() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	virtual void orientation(funit);
	virtual void speed(vector2 const &);
	virtual void pos(const sge::sprite::point&);
	virtual void dim(const sge::sprite::dim&);
	virtual void color(sge::sprite::color);
	virtual void visible(bool);

	sge::sprite::rotation_type orientation() const;
	vector2 const &speed() const;
private:
	void update_pos(const sge::sprite::point&);
	void update_orientation(sge::sprite::rotation_type);

	vector2         speed_,
	                pos_;
	sprite_vector   sprites;
};

}
}

#endif
