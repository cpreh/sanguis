#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
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

class sentry
:
	public sanguis::client::draw2d::entities::model::object
{
	FCPPT_NONCOPYABLE(
		sentry
	);
public:
	explicit
	sentry(
		sanguis::client::draw2d::entities::model::load_parameters const &
	);

	~sentry();

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	)
	override;
private:
	using sanguis::client::draw2d::entities::container::orientation;
};

}
}
}
}

#endif
