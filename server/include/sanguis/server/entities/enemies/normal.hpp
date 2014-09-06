#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_NORMAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_NORMAL_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class normal
:
	public sanguis::server::entities::enemies::enemy
{
	FCPPT_NONCOPYABLE(
		normal
	);
public:
	explicit
	normal(
		sanguis::server::entities::enemies::parameters &&
	);

	~normal()
	override;
private:
	sanguis::messages::types::string const &
	name() const
	override;

	sanguis::enemy_kind
	enemy_kind() const
	override;

	sanguis::messages::types::string const name_;
};

}
}
}
}

#endif
