#ifndef SANGUIS_SERVER_ENTITIES_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENTITY_HPP_INCLUDED

#include "entity_fwd.hpp"
#include "property.hpp"
#include "property_map.hpp"
#include "../teams.hpp"
#include "../types.hpp"
#include "../environment.hpp"
#include "../perks/auto_ptr.hpp"
#include "../../messages/base.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"
#include "../../damage_type.hpp"
#include "../../time_type.hpp"
#include <sge/container/linear_set.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class base_parameters;
class auto_weak_link;

class entity : boost::noncopyable {
protected:
	explicit entity(
		base_parameters const &);
public:
	entity_id id() const;

	pos_type const pos() const;
	void pos(pos_type const &);
	space_unit angle() const;
	void angle(space_unit);
	space_unit direction() const;
	void direction(space_unit);
	
	pos_type const center() const;
	void center(pos_type const &);
	pos_type const abs_speed() const;
	space_unit speed() const;
	space_unit radius() const;

	server::team::type team() const;

	void damage(
		space_unit,
		damage_array const&);
	bool dead() const;
	virtual void die();

	armor_array const &armor() const;
	armor_array const &armor_diff() const;
	armor_array &armor_diff();

	bool aggressive() const;
	void aggressive(bool);

	health_type health() const;
	void health(health_type);
	health_type max_health() const;

	property const &get_property(
		property::type::enum_type) const;
	property &get_property(
		property::type::enum_type);

	virtual exp_type exp() const;
	dim_type const dim() const;
	entity_type::type type() const;
	bool invulnerable() const;

	virtual void update(
		time_type,
		container &entities);

	void add_perk(
		perks::auto_ptr); 
	
	virtual messages::auto_ptr add_message() const;

	auto_weak_link
	link(
		entity &);

	virtual ~entity();
protected:
	void send(messages::auto_ptr);
	environment const &get_environment() const;
	entity &insert(auto_ptr); 

	virtual void on_die();
private:
	friend class auto_weak_link;

	void unlink(
		entity *);
	bool has_ref(
		entity *) const;
	
	entity_id const         id_;
	environment             env_;
	armor_array             armor_;
	pos_type                center_;
	space_unit              angle_,
	                        direction_;
	team::type              team_;
	property_map            properties;
	entity_type::type const type_;
	bool                    invulnerable_;
	dim_type                collision_dim;
	bool                    aggressive_;
	armor_array             armor_diff_;

	typedef boost::ptr_list<
		perks::perk
	>                       perk_container;
	perk_container          perks_;

	typedef sge::container::linear_set<
		entity *
	>                       link_container;
	link_container          links,
	                        backlinks;
};

}
}
}

#endif
