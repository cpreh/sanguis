#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/model/collection.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::load::model::collection const &
sanguis::load::model::context::operator()() const
{
	return *collection_;
}

sanguis::load::model::context::context(
	resource::context const &_ctx,
	sanguis::random_generator &_random_generator
)
:
	collection_(
		fcppt::make_unique_ptr<
			model::collection
		>(
			fcppt::cref(
				_ctx
			),
			fcppt::ref(
				_random_generator
			)
		)
	)
{
}

sanguis::load::model::context::~context()
{
}
