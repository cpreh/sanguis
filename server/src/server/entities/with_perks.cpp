#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_perks::add_perk(
	sanguis::perk_type const _type
)
{
	fcppt::optional::from(
		fcppt::container::find_opt_mapped(
			perks_,
			_type
		),
		[
			this,
			_type
		]()
		{
			return
				fcppt::make_ref(
					perks_.insert(
						std::make_pair(
							_type,
							sanguis::server::perks::create(
								this->diff_clock(),
								random_generator_.get(), // TODO
								_type
							)
						)
					).first->second
				);
		}
	).get()->raise_level(
		*this
	);
}

sanguis::server::entities::with_perks::with_perks(
	sanguis::random_generator_ref const _random_generator
)
:
	random_generator_(
		_random_generator
	),
	perks_()
{
}

sanguis::server::entities::with_perks::~with_perks()
{
}

void
sanguis::server::entities::with_perks::update()
{
	sanguis::server::environment::object &cur_environment(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			this->environment()
		).get()
	);

	for(
		auto const &perk
		:
		perks_
	)
		perk.second->update(
			*this,
			cur_environment
		);
}
