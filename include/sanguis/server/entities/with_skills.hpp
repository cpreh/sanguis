#ifndef SANGUIS_SERVER_ENTITIES_WITH_SKILLS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_SKILLS_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_skills_fwd.hpp>
#include <sanguis/server/skills/container.hpp>
#include <sanguis/server/skills/skill_fwd.hpp>
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

class with_skills
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONCOPYABLE(
		with_skills
	);
protected:
	explicit
	with_skills(
		sanguis::server::skills::container &&
	);
public:
	virtual
	~with_skills() = 0;

	void
	update()
	override;
private:
	typedef
	boost::ptr_vector<
		sanguis::server::skills::skill
	>
	skill_container;

	skill_container skills_;
};

}
}
}

#endif
