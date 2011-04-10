#include "conditional_sound.hpp"
#include <fcppt/random/inclusive_range.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::conditional_sound::conditional_sound(
	sge::parse::json::member_vector const &_members,
	resource::sounds const &_ctx
)
:
	range_(
		static_cast<
			load::probability_type
		>(
			sge::parse::json::find_member_exn<
				double
			>(
				_members,
				FCPPT_TEXT("prob")
			)
		)
	),
	rng_(
		fcppt::random::inclusive_range<
			load::probability_type
		>(
			static_cast<
				load::probability_type
			>(
				0
			),
			static_cast<
				load::probability_type
			>(
				1
			)
		)
	),
	random_sound_(
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
		fcppt::math::compare(
			range_,
			static_cast<
				load::probability_type
			>(
				1
			)
		)
		|| rng_() < range_
		?
			random_sound_.random()
		:
			sge::audio::sound::positional_ptr();
}
