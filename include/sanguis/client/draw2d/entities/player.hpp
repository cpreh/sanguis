#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED

#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/dim_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class player
:
	public sanguis::client::draw2d::entities::model::object
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	explicit
	player(
		sanguis::client::draw2d::entities::model::parameters const &
	);

	~player();

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	)
	override;

	void
	speed(
		sanguis::client::draw2d::speed const &
	)
	override;
protected:
	void
	update()
	override;

	sanguis::client::draw2d::sprite::dim const
	bounding_dim() const;

	using sanguis::client::draw2d::entities::container::orientation;
	using sanguis::client::draw2d::entities::container::speed;
};

}
}
}
}

#endif
