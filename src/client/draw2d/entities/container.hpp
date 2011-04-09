#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED

#include "base.hpp"
#include "with_orientation.hpp"
#include "with_speed.hpp"
#include "../sprite/point.hpp"
#include "../sprite/dim.hpp"
#include "../sprite/order.hpp"
#include "../sprite/rotation_type.hpp"
#include "../sprite/normal/object.hpp"
#include "../sprite/normal/system.hpp"
#include "../sprite/index_fwd.hpp"
#include "../vector2.hpp"
#include <sge/sprite/object_decl.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class container
:
	public base,
	public with_orientation,
	public with_speed
{
	FCPPT_NONCOPYABLE(
		container
	);

	typedef sprite::normal::object object;

	typedef std::vector<
		object
	> sprite_vector;
public:
	typedef sprite_vector::size_type size_type;

	container(
		sprite::normal::system &,
		size_type num_sprites,
		sprite::order
	);

	~container();
	
	sprite::point const
	center() const;

	sprite::point const
	pos() const;
protected:
	typedef sprite_vector::iterator iterator;

	typedef sprite_vector::const_iterator const_iterator;

	// entity overrides
	virtual void
	update(
		time_type
	);

	virtual void
	pos(
		sprite::point const &
	);

	virtual void
	dim(
		sprite::dim const &
	);

	// with_orientation overrides
	virtual void
	orientation(
		sprite::rotation_type
	);

	sprite::rotation_type
	orientation() const;

	// with_speed overrides
	virtual void
	speed(
		vector2 const &
	);
	
	vector2 const
	speed() const;

	// own functions
	object &
	at(
		sprite::index const &
	);

	object const &
	at(
		sprite::index const &
	) const;

	object &
	master();

	object const &
	master() const;

	iterator
	begin();

	iterator
	end();

	const_iterator
	begin() const;

	const_iterator
	end() const;
private:
	void
	update_pos(
		sprite::point const &
	);

	vector2
		speed_,
		pos_;
	
	sprite_vector sprites_;
};

}
}
}
}

#endif
