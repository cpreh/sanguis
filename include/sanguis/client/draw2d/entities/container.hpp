#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/with_center.hpp>
#include <sanguis/client/draw2d/entities/with_orientation.hpp>
#include <sanguis/client/draw2d/entities/with_speed.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sge/sprite/object_decl.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

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
	container(
		sanguis::diff_clock const &,
		sprite::normal::system &,
		entities::order_vector const &,
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
