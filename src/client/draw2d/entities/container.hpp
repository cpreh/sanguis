#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED

#include "base.hpp"
#include "with_center.hpp"
#include "with_orientation.hpp"
#include "with_speed.hpp"
#include "../sprite/center.hpp"
#include "../sprite/dim.hpp"
#include "../sprite/order.hpp"
#include "../sprite/rotation.hpp"
#include "../sprite/normal/object.hpp"
#include "../sprite/normal/system.hpp"
#include "../sprite/index_fwd.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include "../../../diff_clock_fwd.hpp"
#include "../../../diff_timer.hpp"
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
	public with_center,
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
		sanguis::diff_clock const &,
		sprite::normal::system &,
		size_type num_sprites,
		sprite::order,
		sprite::dim const &
	);

	~container();

	sprite::center const
	center() const;
protected:
	typedef sprite_vector::iterator iterator;

	typedef sprite_vector::const_iterator const_iterator;

	// entity overrides
	virtual void
	update();

	virtual void
	center(
		sprite::center const &
	);

	// with_orientation overrides
	virtual void
	orientation(
		sprite::rotation
	);

	sprite::rotation
	orientation() const;

	// with_speed overrides
	virtual void
	speed(
		draw2d::speed const &
	);

	draw2d::speed const
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
	update_center(
		sprite::center const &
	);

	draw2d::speed speed_;

	draw2d::center center_;

	sprite_vector sprites_;

	sanguis::diff_timer move_timer_;
};

}
}
}
}

#endif
