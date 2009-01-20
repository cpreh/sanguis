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
	sattelite(entity &);
	void position_change(collision::point const &);
	sanguis::server::entity &entity();
	sanguis::server::entity const &entity() const;
	private:
	entity &e;
};
}
}
}

#endif
