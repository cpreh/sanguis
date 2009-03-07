#ifndef SANGUIS_SERVER_ENTITIES_SATTELITE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SATTELITE_HPP_INCLUDED

#include "entity_fwd.hpp"
#include <sge/collision/satellite.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
class satellite : public sge::collision::satellite
{
	public:
	satellite(sanguis::server::entities::entity &);
	void position_change(sge::collision::point const &);
	sanguis::server::entities::entity &entity();
	sanguis::server::entities::entity const &entity() const;
	private:
	sanguis::server::entities::entity &e;
};
}
}
}

#endif
