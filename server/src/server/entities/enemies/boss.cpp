#include <sanguis/enemy_kind.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/entities/enemies/boss.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::boss::boss(
	sanguis::server::entities::enemies::parameters &&_parameters
)
:
	sanguis::server::entities::enemies::enemy(
		std::move(
			_parameters
		)
	),
	name_{
		sge::charconv::fcppt_string_to_utf8(
			FCPPT_TEXT("TODO Some boss name")
		)
	}
{
}

sanguis::server::entities::enemies::boss::~boss()
{
}

sanguis::messages::types::string const &
sanguis::server::entities::enemies::boss::name() const
{
	return
		name_;
}

sanguis::enemy_kind
sanguis::server::entities::enemies::boss::enemy_kind() const
{
	return
		sanguis::enemy_kind::boss;
}
