#ifndef SANGUIS_MESSAGES_ADD_ENEMY_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_ENEMY_HPP_INCLUDED

#include "add.hpp"
#include "types.hpp"
#include "../enemy_type.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class add_enemy : public add {
public:
	add_enemy();
	add_enemy(
		entity_id id,
		enemy_type::type,
		pos_type const &,
		space_unit angle,
		vector2 const &speed,
		space_unit health,
		space_unit max_health,
		dim_type const &);

	enemy_type::type etype() const;
private:
	enemy_type::type etype_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
