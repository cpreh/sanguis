#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class bullet
:
	public sanguis::client::draw2d::entities::model::object
{
	FCPPT_NONCOPYABLE(
		bullet
	);
public:
	bullet(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::load::model::path const &
	);

	~bullet()
	override;
private:
	void
	update()
	override;

	typedef
	fcppt::optional<
		sanguis::client::draw2d::sprite::center
	>
	optional_center;

	optional_center origin_;
};

}
}
}
}

#endif
