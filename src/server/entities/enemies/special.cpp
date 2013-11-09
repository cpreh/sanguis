#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/finalize_special_parameters.hpp>
#include <sanguis/server/entities/enemies/make_name.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/special.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::special::special(
	sanguis::server::entities::enemies::parameters &&_parameters,
	sanguis::server::entities::enemies::attribute_container const &_attributes,
	sanguis::server::entities::enemies::skills::container &&_skills
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
	skills_(),
	name_(
		sge::charconv::fcppt_string_to_utf8(
			sanguis::server::entities::enemies::make_name(
				_attributes,
				_skills,
				this->enemy_type()
			)
		)
	)
{
	for(
		auto &skill
		:
		_skills
	)
		fcppt::container::ptr::push_back_unique_ptr(
			skills_,
			std::move(
				skill
			)
		);
}

sanguis::server::entities::enemies::special::~special()
{
}

void
sanguis::server::entities::enemies::special::update()
{
	sanguis::server::entities::enemies::enemy::update();

	for(
		auto &skill
		:
		skills_
	)
		skill.update(
			*this
		);
}

sanguis::messages::types::string const &
sanguis::server::entities::enemies::special::name() const
{
	return
		name_;
}
