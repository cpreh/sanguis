#ifndef SANGUIS_DRAW_BULLET_HPP_INCLUDED
#define SANGUIS_DRAW_BULLET_HPP_INCLUDED

#include "model.hpp"
#include "environment_fwd.hpp"
#include <sge/string.hpp>
#include <boost/optional.hpp>

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

	boost::optional<
		sge::sprite::point
	> origin;
};

}
}

#endif
