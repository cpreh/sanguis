#ifndef SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED

#include "auto_weak_link_fwd.hpp"
#include "with_ghosts.hpp"
#include "../collision/body_base_fwd.hpp"
#include "../center.hpp"
#include "../exp.hpp"
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
	public entities::with_ghosts
{
	FCPPT_NONCOPYABLE(
		exp_area
	);
public:
	explicit exp_area(
		server::exp
	);

	~exp_area();
private:
	void
	on_die();

	bool
	dead() const;

	messages::auto_ptr
	add_message(
		server::player_id
	) const;

	sanguis::entity_type::type
	type() const;

	server::team::type
	team() const;

	bool
	server_only() const;

	server::center const
	center() const;

	void
	collision_begin(
		collision::body_base &
	);

	void
	collision_end(
		collision::body_base &
	);

	server::exp const exp_;

	typedef fcppt::container::map<
		std::map<
			sanguis::entity_id,
			entities::auto_weak_link
		>
	> weak_link_map;

	weak_link_map player_links_;
};

}
}
}

#endif
