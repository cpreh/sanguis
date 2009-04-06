#ifndef SANGUIS_SERVER_ENTITIES_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENTITY_HPP_INCLUDED

#include "entity_fwd.hpp"
#include "base_parameters_fwd.hpp"
#include "auto_weak_link_fwd.hpp"
#include "container.hpp"
#include "property.hpp"
#include "property_map.hpp"
#include "property_type.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../dim_type.hpp"
#include "../health_type.hpp"
#include "../exp_type.hpp"
#include "../teams.hpp"
#include "../environment.hpp"
#include "../perks/auto_ptr.hpp"
#include "../buffs/auto_ptr.hpp"
#include "../auras/auto_ptr.hpp"
#include "../collision/base.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"
#include "../../damage_type.hpp"
#include "../../time_type.hpp"
#include "../../perk_type.hpp"
#include <sge/math/vector/basic_decl.hpp>
#include <sge/math/dim/basic_decl.hpp>
#include <sge/container/linear_set.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/container/map_decl.hpp>
#include <sge/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
class entity : public collision::base {
	SGE_NONCOPYABLE(entity)
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

	entities::property const &
	property(
		property_type::type) const;
	
	entities::property &
	property(
		property_type::type);

	virtual exp_type exp() const;
	dim_type const dim() const;
	entity_type::type type() const;
	bool invulnerable() const;

	virtual void update(
		time_type,
		container &entities);

	virtual void add_perk(
		perks::auto_ptr); 
	
	virtual messages::auto_ptr add_message() const;

	auto_weak_link
	link(
		entity &);
	
	virtual void add_buff(
		buffs::auto_ptr);

	virtual void add_aura(
		auras::auto_ptr);

	virtual ~entity();
protected:
	void send(messages::auto_ptr);
	server::environment const &
	environment() const;
	entity &insert(auto_ptr); 

	bool perk_choosable(
		perk_type::type) const;

	virtual void on_die();
private:
	friend class auto_weak_link;
	friend class satellite;

	void unlink(
		entity *);
	bool has_ref(
		entity *) const;
	
	void speed_change(property::value_type);

	bool
	can_collide_with(
		collision::base const &) const;
	
	void
	collision(
		collision::base &);

	virtual bool
	can_collide_with_entity(
		entity const &) const;
	
	virtual void
	collision_entity(
		entity &);

	entity_id const         id_;
	server::environment     env_;
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
	sge::signal::scoped_connection const speed_change_;

	typedef boost::ptr_map<
		perk_type::type,
		perks::perk
	>                       perk_container;
	perk_container          perks_;

	typedef boost::ptr_list<
		buffs::buff
	>                       buff_container;
	buff_container          buffs_;

	typedef boost::ptr_list<
		auras::aura
	>                       aura_container;
	aura_container          auras_;

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
