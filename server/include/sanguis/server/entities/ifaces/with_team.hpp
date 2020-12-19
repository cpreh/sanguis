#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_TEAM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_TEAM_HPP_INCLUDED

#include <sanguis/server/team_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace ifaces
{

class with_team
{
	FCPPT_NONMOVABLE(
		with_team
	);
protected:
	with_team();
public:
	[[nodiscard]]
	virtual
	sanguis::server::team
	team() const = 0;

	virtual
	~with_team();
};

}
}
}
}

#endif
