#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PARTICLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PARTICLE_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/particle_name.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/optional_dim_fwd.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/load/resource/animation/series_cref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities
{

class particle
:
	public sanguis::client::draw2d::entities::own
{
	FCPPT_NONMOVABLE(
		particle
	);
public:
	particle(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::draw2d::entities::particle_name const &,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::optional_dim const &
	);

	~particle()
	override;
private:
	particle(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::optional_dim const &,
		sanguis::client::load::resource::animation::series_cref
	);

	void
	update()
	override;

	[[nodiscard]]
	bool
	may_be_removed() const
	override;

	sanguis::client::draw2d::sprite::animation::texture animation_;

	sanguis::client::draw2d::sprite::normal::object sprite_;
};

}

#endif
