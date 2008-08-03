#ifndef SANGUIS_MESSAGES_ADD_PICKUP_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PICKUP_HPP_INCLUDED

#include "add.hpp"
#include "types.hpp"
#include "../pickup_type.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class add_pickup : public add {
public:
	add_pickup();
	add_pickup(
		entity_id id,
		pickup_type::type,
		pos_type const &,
		space_unit angle,
		space_unit health,
		space_unit max_health,
		dim_type const &);
	
	pickup_type::type ptype() const;
private:
	pickup_type::type ptype_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
