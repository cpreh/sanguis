#ifndef SANGUIS_DRAW_CONTAINER_HPP_INCLUDED
#define SANGUIS_DRAW_CONTAINER_HPP_INCLUDED

#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "sprite/order.hpp"
#include "sprite/rotation_type.hpp"
#include "sprite/normal/object.hpp"
#include "environment_fwd.hpp"
#include "sprite_part_index_fwd.hpp"
#include "entity.hpp"
#include "vector2.hpp"
#include <sge/math/vector/basic_decl.hpp>
#include <sge/sprite/object_decl.hpp>
#include <vector>

namespace sanguis
{
namespace draw
{

class container
:
	public entity
{
	typedef sprite::normal::object object;

	typedef std::vector<
		object
	> sprite_vector;
public:
	typedef sprite_vector::size_type size_type;

	container(
		draw::environment const &env,
		entity_id id,
		size_type,
		sprite::order
	);

	~container();
	
	sprite::point const center() const;
	sprite::point const pos() const;
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
	virtual void pos(sprite::point const &);
	virtual void dim(sprite::dim const &);

	sprite::rotation_type orientation() const;
	vector2 const speed() const;
private:
	void update_pos(sprite::point const &);
	void update_orientation(sprite::rotation_type);
	void transfer(
		sprite::normal::system &
	);

	vector2         speed_,
	                pos_;
	sprite_vector   sprites;
};

}
}

#endif
