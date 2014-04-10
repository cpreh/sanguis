#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_SKILL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_SKILL_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/skill_fwd.hpp>
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

class skill
{
	FCPPT_NONCOPYABLE(
		skill
	);
protected:
	skill();
public:
	virtual
	~skill() = 0;

	virtual
	void
	update(
		sanguis::server::entities::enemies::enemy &
	) = 0;

	virtual
	sanguis::server::entities::enemies::attribute
	attribute() const = 0;
};

}
}
}
}
}

#endif
