#ifndef SANGUIS_MESSAGES_ADD_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WEAPON_PICKUP_HPP_INCLUDED

#include "add.hpp"
#include "types.hpp"
#include "../weapon_type.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class add_weapon_pickup : public add {
public:
	add_weapon_pickup();
	add_weapon_pickup(
		entity_id id,
		weapon_type::type,
		pos_type const &,
		space_unit angle,
		dim_type const &);
	
	weapon_type::type wtype() const;
private:
	weapon_type::type wtype_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
