#ifndef SANGUIS_DRAW_SENTRY_HPP_INCLUDED
#define SANGUIS_DRAW_SENTRY_HPP_INCLUDED

#include "model.hpp"

namespace sanguis
{
namespace draw
{

class sentry : public model {
public:
	sentry(
		draw::environment const &,
		entity_id);
	
	void orientation(
		sge::sprite::rotation_type);
private:
	using sprite::orientation;
};


}
}

#endif
