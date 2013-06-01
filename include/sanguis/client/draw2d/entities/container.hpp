#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2_fwd.hpp>
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
#include <sge/sprite/object_decl.hpp>
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
	public sanguis::client::draw2d::entities::base,
	public sanguis::client::draw2d::entities::with_center,
	public sanguis::client::draw2d::entities::with_orientation,
	public sanguis::client::draw2d::entities::with_speed
{
	FCPPT_NONCOPYABLE(
		container
	);

	typedef sanguis::client::draw2d::sprite::normal::object object;

	typedef std::vector<
		object
	> sprite_vector;
public:
	container(
		sanguis::diff_clock const &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::client::draw2d::entities::order_vector const &,
		sanguis::client::draw2d::sprite::dim const &
	);

	~container();

	sanguis::client::draw2d::sprite::center const
	center() const;

	sanguis::client::draw2d::sprite::center const
	extrapolated_center() const;
protected:
	typedef sprite_vector::iterator iterator;

	typedef sprite_vector::const_iterator const_iterator;

	// entity overrides
	virtual
	void
	update();

	virtual
	void
	center(
		sanguis::client::draw2d::sprite::center const &
	);

	// with_orientation overrides
	virtual
	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	);

	sanguis::client::draw2d::sprite::rotation
	orientation() const;

	// with_speed overrides
	virtual
	void
	speed(
		sanguis::client::draw2d::speed const &
	);

	sanguis::client::draw2d::speed const
	speed() const;

	// own functions
	object &
	at(
		sanguis::client::draw2d::sprite::index const &
	);

	object const &
	at(
		sanguis::client::draw2d::sprite::index const &
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
	sanguis::client::draw2d::vector2 const
	center_diff() const;

	void
	update_center(
		sanguis::client::draw2d::sprite::center const &
	);

	sanguis::client::draw2d::speed speed_;

	sanguis::client::draw2d::center center_;

	sprite_vector sprites_;

	sanguis::diff_timer move_timer_;
};

}
}
}
}

#endif
