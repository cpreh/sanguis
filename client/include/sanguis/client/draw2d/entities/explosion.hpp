#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/entities/particle.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		explosion
	);
public:
	explosion(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::client::load::model::collection const &,
		sanguis::client::draw2d::sprite::center,
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
