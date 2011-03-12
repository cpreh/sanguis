#include "random_sound.hpp"
#include "sound.hpp"
#include "../resource/context.hpp"
#include "../resource/sounds.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/random/inclusive_range.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>
#include <numeric>
#include <functional>

sanguis::load::model::random_sound::random_sound(
	sge::parse::json::element_vector const &elements,
	resource::sounds const &ctx)
:
	rng(
		fcppt::random::inclusive_range<
			probability_type	
		>(
			0,
			1
		)
	)
{
	BOOST_FOREACH(
		sge::parse::json::element_vector::const_reference ref,
		elements
	)
	{
		sounds_.push_back(
			sound(			
				sge::parse::json::get<
					sge::parse::json::object
				>(
					ref
				).members,
				ctx
			)
		);
	}

	if(sounds_.empty())
		return;

	probability_type const normalization(
		std::accumulate(
			sounds_.begin(),
			sounds_.end(),
			static_cast<
				probability_type
			>(
				0
			),
			std::tr1::bind(
				std::plus<
					probability_type
				>(),
				std::tr1::placeholders::_1,
				std::tr1::bind(
					&sound::probability,
					std::tr1::placeholders::_2
				)
			)
		)
	);

	if(
		fcppt::math::almost_zero(
			normalization
		)
	)
		throw exception(
			FCPPT_TEXT("sound probabilities are 0!")
		);

	BOOST_FOREACH(
		sound_container::const_reference r,
		sounds_
	)
		ranges.push_back(
			r.probability() / normalization
		);
	
	FCPPT_ASSERT(ranges.size() == sounds_.size());
}

sge::audio::sound::positional_ptr const
sanguis::load::model::random_sound::random() const
{
	if(sounds_.empty())
		return sge::audio::sound::positional_ptr();
	
	probability_type const number(
		rng()
	);

	for(
		range_vector::size_type i = 0;
		i < ranges.size();
		++i
	)
		if(number < ranges[i])
			return sounds_[i].make();
	
	throw exception(
		FCPPT_TEXT("probability didn't match any sounds!")
	);
}
