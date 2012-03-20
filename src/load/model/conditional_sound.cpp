#include <sanguis/random_generator.hpp>
#include <sanguis/load/model/conditional_sound.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_real_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::conditional_sound::conditional_sound(
	sanguis::random_generator &_random_generator,
	sge::parse::json::member_map const &_members,
	resource::sounds const &_ctx
)
:
	range_(
		sge::parse::json::find_member<
			double
		>(
			_members,
			FCPPT_TEXT("prob")
		)
	),
	rng_(
		_random_generator,
		distribution(
			distribution::min(
				0.f
			),
			distribution::sup(
				1.f
			)
		)
	),
	random_sound_(
		_random_generator,
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			_members,
			FCPPT_TEXT("elements")
		).elements,
		_ctx
	)
{
}

sanguis::load::model::conditional_sound::~conditional_sound()
{
}

sge::audio::sound::positional_ptr const
sanguis::load::model::conditional_sound::random() const
{
	// avoid the corner case in which the probability is 1
	return
		!range_
		|| rng_()
		<
		static_cast<
			load::probability_type
		>(
			*range_
		)
		?
			random_sound_.random()
		:
			sge::audio::sound::positional_ptr();
}
