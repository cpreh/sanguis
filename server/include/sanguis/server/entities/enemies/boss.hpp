#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_BOSS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_BOSS_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::enemies
{

class boss
:
	public sanguis::server::entities::enemies::enemy
{
	FCPPT_NONMOVABLE(
		boss
	);
public:
	explicit
	boss(
		sanguis::server::entities::enemies::parameters &&
	);

	~boss()
	override;
private:
	[[nodiscard]]
	sanguis::server::entities::transfer_result
	on_create()
	override;

	void
	remove_from_game()
	override;

	[[nodiscard]]
	sanguis::messages::types::string const &
	name() const
	override;

	[[nodiscard]]
	sanguis::enemy_kind
	enemy_kind() const
	override;

	sanguis::messages::types::string const name_;
};

}

#endif
