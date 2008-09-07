#ifndef SANGUIS_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include "../entity_type.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class add : public entity_message {
public:
	add();
	add(
		entity_id id,
		entity_type::type type_,
		pos_type const &pos,
		space_unit angle,
		vector2 const &speed,
		space_unit health,
		space_unit max_health,
		dim_type const &dim);

	entity_type::type type() const;
	pos_type const &pos() const;
	space_unit angle() const;
	vector2 const &speed() const;
	space_unit health() const;
	dim_type const &dim() const;
	space_unit max_health() const;
private:
	entity_type::type  type_;
	pos_type           pos_;
	space_unit         angle_;
	vector2            speed_;
	space_unit         health_,
	                   max_health_;
	dim_type           dim_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
