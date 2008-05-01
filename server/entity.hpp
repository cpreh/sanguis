#ifndef SANGUIS_SERVER_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_HPP_INCLUDED

#include "entity_fwd.hpp"
#include "teams.hpp"
#include "environment.hpp"
#include "perks/perk.hpp"
#include "../messages/types.hpp"
#include "../entity_id.hpp"
#include "../entity_type.hpp"
#include "../damage_type.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{

class entity
{
public:
	typedef messages::space_unit time_type;
	typedef messages::space_unit health_type;
protected:
	entity(
		const environment &,
		const armor_array &,
		const messages::pos_type &pos,
		const messages::space_unit angle,
		const messages::space_unit direction,
		const messages::space_unit health,
		const messages::space_unit max_health,
		const team::type team,
		const messages::space_unit speed,
		const messages::space_unit max_speed);
public:
	entity_id id() const;

	messages::pos_type pos() const;
	void pos(const messages::pos_type);
	messages::space_unit speed() const;
	void speed(const messages::space_unit);
	messages::space_unit angle() const;
	void angle(const messages::space_unit);
	messages::space_unit direction() const;
	void direction(const messages::space_unit);
	messages::space_unit health() const;
	void health(const messages::space_unit);
	messages::space_unit max_health() const;
	void max_health(const messages::space_unit);
	messages::space_unit max_speed() const;
	void max_speed(const messages::space_unit);
	team::type team() const;
	void damage(
		messages::space_unit,
		damage_array const&);
	bool dead() const;
	virtual void die();

	const armor_array &armor() const;
	const armor_array &armor_diff() const;
	armor_array &armor_diff();

	bool attacking() const;
	void attacking(const bool);

	bool aggressive() const;
	void aggressive(const bool);


	// is calculated from the above
	messages::pos_type center() const;
	messages::pos_type abs_speed() const;
	messages::space_unit radius() const;

	virtual messages::exp_type exp() const;
	virtual messages::dim_type dim() const = 0;
	virtual entity_type::type type() const = 0;
	virtual bool invulnerable() const = 0;
	virtual void update(
		const time_type,
		entity_container &entities);

	void add_perk(
		perks::perk_auto_ptr); 
	
	virtual ~entity();
protected:
	void send(messages::base *); // TODO: this should be an auto_ptr
	entity &insert(entity_ptr); 
	const environment &get_environment() const;
private:
	entity_id id_;
	environment env_;
	messages::pos_type pos_;
	messages::space_unit speed_,
	                     max_speed_,
	                     angle_,
	                     direction_,
	                     health_,
	                     max_health_;
	team::type team_;
	armor_array          armor_,
	                     armor_diff_;
	bool attacking_,
	     aggressive_;

	typedef boost::ptr_list<perks::perk> perk_container;
	perk_container perks_;
};

}
}

#endif
