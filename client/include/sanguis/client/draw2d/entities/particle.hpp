#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PARTICLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PARTICLE_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/particle_name.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/optional_dim_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation_decl.hpp>
#include <sanguis/client/load/resource/animation/series_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class particle
:
	public sanguis::client::draw2d::entities::own
{
	FCPPT_NONCOPYABLE(
		particle
	);
public:
	particle(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::draw2d::entities::particle_name const &,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::sprite::optional_dim
	);

	~particle()
	override;
private:
	particle(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::sprite::optional_dim,
		sanguis::client::load::resource::animation::series const &
	);

	void
	update()
	override;

	bool
	may_be_removed() const
	override;

	bool ended_;

	sanguis::client::draw2d::sprite::normal::object sprite_;

	sanguis::client::draw2d::sprite::normal::texture_animation animation_;
};

}
}
}
}

#endif
