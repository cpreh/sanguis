#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_REF_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_REF_HPP_INCLUDED

#include "entity_fwd.hpp"
#include "weak_link_pair.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
class auto_weak_link_ref {
	explicit auto_weak_link_ref(
		weak_link_pair const &);
	
	weak_link_pair data;

	friend class auto_weak_link;
};

}
}
}

#endif
