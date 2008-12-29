#ifndef SANGUIS_DRAW_BULLET_HPP_INCLUDED
#define SANGUIS_DRAW_BULLET_HPP_INCLUDED

#include "model.hpp"
#include <sge/string.hpp>
#include <boost/optional.hpp>

namespace sanguis
{
namespace draw
{

class environment;

class bullet : public model {
public:
	bullet(
		environment const &,
		entity_id id,
		draw::system &,
		sge::string const &name);
private:
	void update(time_type);
	boost::optional<sge::sprite::point> origin;
};

}
}

#endif
