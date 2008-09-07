#ifndef SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED

#include "add.hpp"
#include "types.hpp"
#include "../projectile_type.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class add_projectile : public add {
public:
	add_projectile();
	add_projectile(
		entity_id id,
		projectile_type::type,
		pos_type const &,
		space_unit angle,
		vector2 const &speed,
		space_unit health,
		space_unit max_health,
		dim_type const &);
	
	projectile_type::type ptype() const;
private:
	projectile_type::type ptype_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
