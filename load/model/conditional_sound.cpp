#include "conditional_sound.hpp"
#include <fcppt/random/inclusive_range.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::conditional_sound::conditional_sound(
	sge::parse::json::member_vector const &members,
	resource::sounds const &ctx)
:
	range(
		static_cast<
			probability_type
		>(
			sge::parse::json::find_member<
				double
			>(
				members,
				FCPPT_TEXT("prob")
			)
		)
	),
	rng(
		fcppt::random::inclusive_range<probability_type>(
			static_cast<probability_type>(0),
			static_cast<probability_type>(1)
		)
	),
	random_sound_(
		sge::parse::json::find_member<
			sge::parse::json::array
		>(
			members,
			FCPPT_TEXT("elements")
		).elements,
		ctx
	)
{}

sge::audio::sound_ptr const
sanguis::load::model::conditional_sound::random() const
{
	// avoid the corner case in which the probability is 1
	return fcppt::math::compare(range, static_cast<probability_type>(1)) || rng() < range
		? random_sound_.random()
		: sge::audio::sound_ptr();
}
