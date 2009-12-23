#ifndef SANGUIS_DRAW_BULLET_HPP_INCLUDED
#define SANGUIS_DRAW_BULLET_HPP_INCLUDED

#include "model.hpp"
#include "environment_fwd.hpp"
#include "sprite/point.hpp"
#include <fcppt/string.hpp>
#include <fcppt/optional_decl.hpp>

namespace sanguis
{
namespace draw
{

class bullet : public model {
public:
	bullet(
		draw::environment const &,
		entity_id id,
		fcppt::string const &name
	);
private:
	void update(time_type);

	fcppt::optional<
		sprite::point
	> origin;
};

}
}

#endif
