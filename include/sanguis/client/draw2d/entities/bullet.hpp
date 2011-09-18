#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/string.hpp>

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
	public model::object
{
	FCPPT_NONCOPYABLE(
		bullet
	);
public:
	bullet(
		model::parameters const &,
		fcppt::string const &name
	);

	~bullet();
private:
	void
	update();

	fcppt::optional<
		sprite::center
	> origin_;
};

}
}
}
}

#endif
