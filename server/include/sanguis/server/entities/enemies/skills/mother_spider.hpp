#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_MOTHER_SPIDER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_MOTHER_SPIDER_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace skills
{

class mother_spider
:
	public sanguis::server::entities::enemies::skills::skill
{
	FCPPT_NONCOPYABLE(
		mother_spider
	);
public:
	mother_spider();

	~mother_spider()
	override;
private:
	void
	on_die(
		sanguis::server::entities::enemies::enemy const &
	)
	override;

	sanguis::server::entities::enemies::attribute
	attribute() const
	override;
};

}
}
}
}
}

#endif
