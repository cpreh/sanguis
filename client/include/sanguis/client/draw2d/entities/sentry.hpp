#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
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
	public sanguis::client::draw2d::entities::friend_
{
	FCPPT_NONCOPYABLE(
		sentry
	);
public:
	sentry(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::load::auras::context &,
		sanguis::aura_type_vector const &,
		sanguis::buff_type_vector const &,
		sanguis::client::health_pair
	);

	~sentry()
	override;

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
