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
		const pos_type& pos,
		space_unit angle,
		const vector2& speed,
		space_unit health,
		space_unit max_health,
		const dim_type& dim);

	entity_type::type type() const;
	const pos_type& pos() const;
	space_unit angle() const;
	const vector2& speed() const;
	space_unit health() const;
	const dim_type &dim() const;
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
