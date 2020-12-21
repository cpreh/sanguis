#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CONTAINER_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/radius_fwd.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/level_vector.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_center.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_orientation.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_speed.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <fcppt/nonmovable.hpp>
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
	public sanguis::client::draw2d::entities::ifaces::with_center,
	public sanguis::client::draw2d::entities::ifaces::with_orientation,
	public sanguis::client::draw2d::entities::ifaces::with_speed
{
	FCPPT_NONMOVABLE(
		container
	);

	using
	object
	=
	sanguis::client::draw2d::sprite::normal::object;

	using
	sprite_vector
	=
	std::vector<
		object
	>;
public:
	container(
		sanguis::diff_clock_cref,
		sanguis::client::draw2d::sprite::normal::system_ref,
		sanguis::client::draw2d::entities::level_vector const &,
		sanguis::client::draw2d::speed,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::dim const &,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::client::draw2d::sprite::normal::color
	);

	~container()
	override;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::center
	center() const
	override;

	[[nodiscard]]
	sanguis::client::draw2d::radius
	radius() const
	override;

	[[nodiscard]]
	bool
	cursor_collision(
		sanguis::client::draw2d::sprite::center
	) const
	override;

	void
	color(
		sanguis::client::draw2d::sprite::normal::color const &
	);

	[[nodiscard]]
	sanguis::client::draw2d::sprite::normal::color
	color() const;

	void
	center(
		sanguis::client::draw2d::sprite::center const &
	)
	override;

	[[nodiscard]]
	sanguis::client::draw2d::center
	float_center() const;

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	)
	override;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::rotation
	orientation() const
	override;

	void
	speed(
		sanguis::client::draw2d::speed const &
	)
	override;

	[[nodiscard]]
	sanguis::client::draw2d::speed
	speed() const
	override;

	[[nodiscard]]
	sanguis::duration
	movement_duration() const;

	// own functions
	[[nodiscard]]
	object &
	at(
		sanguis::client::draw2d::sprite::index const &
	);

	[[nodiscard]]
	object const &
	at(
		sanguis::client::draw2d::sprite::index const &
	) const;

	[[nodiscard]]
	object &
	master();

	[[nodiscard]]
	object const &
	master() const;
protected:
	void
	update()
	override;
private:
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
