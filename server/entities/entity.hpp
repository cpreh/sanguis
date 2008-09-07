#ifndef SANGUIS_SERVER_ENTITIES_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENTITY_HPP_INCLUDED

#include "entity_fwd.hpp"
#include "property.hpp"
#include "property_map.hpp"
#include "../teams.hpp"
#include "../types.hpp"
#include "../environment.hpp"
#include "../perks/perk.hpp"
#include "../../messages/base.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"
#include "../../damage_type.hpp"
#include "../../time_type.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class base_parameters;

class entity {
protected:
	explicit entity(
		base_parameters const &);
public:
	entity_id id() const;

	messages::pos_type pos() const;
	void pos(const messages::pos_type);
	messages::space_unit angle() const;
	void angle(const messages::space_unit);
	messages::space_unit direction() const;
	void direction(const messages::space_unit);
	team::type team() const;
	void damage(
		messages::space_unit,
		damage_array const&);
	bool dead() const;
	virtual void die();

	armor_array const &armor() const;
	armor_array const &armor_diff() const;
	armor_array &armor_diff();

	bool attacking() const;
	void attacking(const bool);

	bool aggressive() const;
	void aggressive(bool);

	health_type health() const;
	void health(health_type);
	health_type max_health() const;

	messages::space_unit speed() const;

	const property &get_property(property::type::enum_type) const;
	property &get_property(property::type::enum_type);

	// is calculated from the above
	messages::pos_type center() const;
	messages::pos_type abs_speed() const;
	messages::space_unit radius() const;

	virtual messages::exp_type exp() const;
	virtual messages::dim_type const dim() const;
	virtual entity_type::type type() const;
	virtual bool invulnerable() const;
	virtual void update(
		time_type,
		container &entities);

	void add_perk(
		perks::perk_auto_ptr); 
	
	virtual messages::auto_ptr add_message() const;

	virtual ~entity();
protected:
	void send(messages::auto_ptr);
	entity &insert(auto_ptr); 
	const environment &get_environment() const;

	virtual void on_die();
private:
	entity_id            id_;
	environment          env_;
	armor_array          armor_;
	messages::pos_type   pos_;
	messages::space_unit angle_,
	                     direction_;
	team::type           team_;
	property_map         properties;
	entity_type::type    type_;
	bool                 invulnerable_;
	messages::dim_type   collision_dim;
	bool                 attacking_,
	                     aggressive_;
	armor_array          armor_diff_;

	typedef boost::ptr_list<
		perks::perk
	>                    perk_container;
	perk_container       perks_;
};

}
}
}

#endif
