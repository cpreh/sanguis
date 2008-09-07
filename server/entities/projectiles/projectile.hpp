#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "../../../time_type.hpp"
#include "../../../messages/types.hpp"
#include "../entity.hpp"
#include <sge/time/timer.hpp>
#include <boost/tr1/functional.hpp>
#include <vector>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class projectile : public entity {
protected:
	projectile(
		environment const &,
		pos_type const &center,
		space_unit angle,
		team::type team,
		property_map const &,
		dim_type const &dim,
		time_type lifetime);
	void die();

	typedef std::vector<
		std::tr1::reference_wrapper<
			entity
		>
	> hit_vector;
private:
	void update(
		time_type,
		container &entities);
	messages::space_unit max_speed() const;

	virtual void do_hit(
		hit_vector const &) = 0;
	virtual void do_die();

	space_unit          max_speed_;
	sge::time::timer    lifetime;
};

}
}
}
}

#endif
