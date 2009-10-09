#ifndef SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED

#include "base.hpp"
#include "auto_weak_link_fwd.hpp"
#include "../exp_type.hpp"
#include "../../entity_id.hpp"
#include "../../diff_clock.hpp"
#include <sge/container/map_decl.hpp>
#include <sge/time/timer.hpp>
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
public:
	explicit exp_area(
		exp_type
	);
protected:
	~exp_area();
private:
	void
	on_update(
		time_type
	);

	void
	on_die();

	bool
	dead() const;

	bool
	invulnerable() const;

	messages::auto_ptr
	add_message() const;

	entity_type::type
	type() const;

	server::team::type
	team() const;

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

	diff_clock diff_clock_;

	sge::time::timer expire_timer_;

	typedef sge::container::map<
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
