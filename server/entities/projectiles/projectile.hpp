#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "../../../projectile_type.hpp"
#include "../../../time_type.hpp"
#include "../../../messages/base.hpp"
#include "../entity.hpp"
#include <sge/time/timer.hpp>
#include <boost/optional.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class projectile : public entity {
public:
	projectile_type::type ptype() const;
protected:
	typedef boost::optional<
		time_type
	> optional_life_time;

	projectile(
		projectile_type::type,
		server::environment const &,
		pos_type const &center,
		space_unit angle,
		team::type team,
		property_map const &,
		dim_type const &dim,
		optional_life_time const &);
	
	void die();

	void update(
		time_type,
		container &);
private:
	virtual bool
	can_collide_with(
		entity const &) const;
	
	virtual void do_die();

	messages::auto_ptr add_message() const;

	projectile_type::type ptype_;
	sge::time::timer      lifetime;
};

}
}
}
}

#endif
