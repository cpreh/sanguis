#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/particle.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class explosion
:
	public sanguis::client::draw2d::entities::particle
{
	FCPPT_NONMOVABLE(
		explosion
	);
public:
	explosion(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::aoe
	);

	~explosion()
	override;
};

}
}
}
}

#endif
