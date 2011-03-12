#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED

#include "model/object.hpp"
#include "model/parameters_fwd.hpp"
#include "../sprite/point.hpp"
#include <fcppt/string.hpp>
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
	public model::object
{
public:
	bullet(
		model::parameters const &,
		fcppt::string const &name
	);
private:
	void
	update(
		time_type
	);

	fcppt::optional<
		sprite::point
	> origin;
};

}
}
}
}

#endif
