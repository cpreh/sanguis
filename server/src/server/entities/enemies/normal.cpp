#include <sanguis/enemy_kind.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/normal.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/pretty_name.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::enemies::normal::normal(
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
			sanguis::server::entities::enemies::pretty_name(
				this->enemy_type()
			)
		)
	}
{
}

FCPPT_PP_POP_WARNING

sanguis::server::entities::enemies::normal::~normal()
= default;

sanguis::messages::types::string const &
sanguis::server::entities::enemies::normal::name() const
{
	return
		name_;
}

sanguis::enemy_kind
sanguis::server::entities::enemies::normal::enemy_kind() const
{
	return
		sanguis::enemy_kind::normal;
}
