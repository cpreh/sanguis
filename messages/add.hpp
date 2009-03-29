#ifndef SANGUIS_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_HPP_INCLUDED

#include "roles/angle.hpp"
#include "roles/health.hpp"
#include "roles/max_health.hp"
#include "roles/pos.hpp"
#include "roles/speed.hpp"
#include "message_type.hpp"
#include "pos.hpp"
#include "dim.hpp"
#include "space_unit.hpp"
#include "vector2.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/bind.hpp>
#include <majutsu/constant.hpp>
#include <majutsu/role.hpp>
#include <majutsu/placeholder.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		majutsu::bind<
			entity_message,
			boost::mpl::vector<
				majutsu::constant<
					types::message::type,
					types::message::add
				>,
				majutsu::placeholder
			>
		>,
		majutsu::role<
			pos,
			roles::pos
		>,
		majutsu::role<
			space_unit,
			roles::angle
		>,
		majutsu::role<
			vector2,
			roles::speed
		>,
		majutsu::role<
			space_unit,
			roles::health
		>,
		majutsu::role<
			space_unit,
			roles::max_health
		>,
		majutsu::role<
			dim
		>
	>
> add;

/*
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
*/

}
}

#endif
