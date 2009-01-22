#ifndef SANGUIS_SERVER_ENTITIES_SATTELITE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SATTELITE_HPP_INCLUDED

#include "entity_fwd.hpp"
#include <sge/collision/sattelite.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
class sattelite : public sge::collision::sattelite
{
	public:
	sattelite(sanguis::server::entities::entity &);
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
