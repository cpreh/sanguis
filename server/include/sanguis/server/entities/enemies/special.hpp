#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <fcppt/noncopyable.hpp>


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
		sanguis::random_generator &,
		sanguis::server::entities::enemies::parameters &&,
		sanguis::server::entities::enemies::attribute_container const &,
		sanguis::server::entities::enemies::skills::factory::container const &
	);

	~special()
	override;
private:
	void
	update()
	override;

	sanguis::messages::types::string const &
	name() const
	override;

	sanguis::server::entities::enemies::skills::container const skills_;

	sanguis::messages::types::string const name_;
};

}
}
}
}

#endif
