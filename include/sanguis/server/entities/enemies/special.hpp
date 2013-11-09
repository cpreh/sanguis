#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_HPP_INCLUDED

#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class special
:
	public sanguis::server::entities::enemies::enemy
{
	FCPPT_NONCOPYABLE(
		special
	);
public:
	special(
		sanguis::server::entities::enemies::parameters &&,
		sanguis::server::entities::enemies::skills::container &&
	);

	~special()
	override;
private:
	void
	update()
	override;

	typedef
	boost::ptr_vector<
		sanguis::server::entities::enemies::skills::skill
	>
	skill_container;

	skill_container skills_;
};

}
}
}
}

#endif
