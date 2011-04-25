#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED

#include "model/object.hpp"
#include "model/parameters_fwd.hpp"
#include "../sprite/center.hpp"
#include "../../../time_delta_fwd.hpp"
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
	update(
		sanguis::time_delta const &
	);

	fcppt::optional<
		sprite::center
	> origin_;
};

}
}
}
}

#endif
