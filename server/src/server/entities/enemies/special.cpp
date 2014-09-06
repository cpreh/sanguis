#include <sanguis/enemy_kind.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/finalize_special_parameters.hpp>
#include <sanguis/server/entities/enemies/is_unique.hpp>
#include <sanguis/server/entities/enemies/make_name.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/special.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/callback.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::special::special(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::parameters &&_parameters,
	sanguis::server::entities::enemies::attribute_container const &_attributes,
	sanguis::server::entities::enemies::skills::factory::container const &_skills,
	sanguis::server::entities::enemies::is_unique const _is_unique
)
:
	sanguis::server::entities::enemies::enemy(
		std::move(
			sanguis::server::entities::enemies::finalize_special_parameters(
				_parameters,
				_attributes,
				_skills
			)
		)
	),
	skills_(
		fcppt::algorithm::map<
			sanguis::server::entities::enemies::skills::container
		>(
			_skills,
			[
				&_random_generator,
				&_parameters,
				this
			](
				sanguis::server::entities::enemies::skills::factory::callback const &_create
			)
			{
				return
					_create(
						sanguis::server::entities::enemies::skills::factory::parameters(
							this->diff_clock(),
							_random_generator,
							_parameters.difficulty()
						)
					);
			}
		)
	),
	name_{
		sge::charconv::fcppt_string_to_utf8(
			sanguis::server::entities::enemies::make_name(
				_attributes,
				skills_,
				this->enemy_type()
			)
		)
	},
	is_unique_{
		_is_unique
	}
{
}

sanguis::server::entities::enemies::special::~special()
{
}

void
sanguis::server::entities::enemies::special::update()
{
	sanguis::server::entities::enemies::enemy::update();

	for(
		sanguis::server::entities::enemies::skills::unique_ptr const &skill
		:
		skills_
	)
		skill->update(
			*this
		);
}

sanguis::messages::types::string const &
sanguis::server::entities::enemies::special::name() const
{
	return
		name_;
}

sanguis::enemy_kind
sanguis::server::entities::enemies::special::enemy_kind() const
{
	return
		is_unique_.get()
		?
			sanguis::enemy_kind::unique
		:
			sanguis::enemy_kind::champion
		;
}
