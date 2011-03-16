#ifndef SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED

#include "base.hpp"
#include "auto_weak_link_fwd.hpp"
#include "../exp_type.hpp"
#include "../../entity_id.hpp"
#include <fcppt/container/map_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace server
{
namespace entities
{

class exp_area
:
	public base
{
	FCPPT_NONCOPYABLE(
		exp_area
	);
public:
	explicit exp_area(
		exp_type
	);

	~exp_area();
private:
	void
	on_die();

	space_unit
	radius() const;

	bool
	dead() const;

	bool
	invulnerable() const;

	messages::auto_ptr
	add_message(
		player_id
	) const;

	entity_type::type
	type() const;

	server::team::type
	team() const;

	bool
	server_only() const;

	boost::logic::tribool const 
	can_collide_with_entity(
		base const &
	) const;
	
	void
	collision_entity_begin(
		base &
	);

	void
	collision_entity_end(
		base &
	);

	exp_type const exp_;

	typedef fcppt::container::map<
		std::map<
			entity_id,
			auto_weak_link
		>
	> weak_link_map;

	weak_link_map player_links_;
};

}
}
}

#endif
