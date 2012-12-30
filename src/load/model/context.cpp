#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/model/collection.hpp>
#include <fcppt/make_unique_ptr.hpp>

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
			_ctx,
			_random_generator
		)
	)
{
}

sanguis::load::model::context::~context()
{
}
