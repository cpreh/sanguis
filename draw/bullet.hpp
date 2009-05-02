#ifndef SANGUIS_DRAW_BULLET_HPP_INCLUDED
#define SANGUIS_DRAW_BULLET_HPP_INCLUDED

#include "model.hpp"
#include "environment_fwd.hpp"
#include <sge/string.hpp>
#include <sge/optional_decl.hpp>

namespace sanguis
{
namespace draw
{

class bullet : public model {
public:
	bullet(
		draw::environment const &,
		entity_id id,
		sge::string const &name);
private:
	void update(time_type);

	sge::optional<
		sge::sprite::point
	> origin;
};

}
}

#endif
