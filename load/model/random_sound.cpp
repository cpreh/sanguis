#include "random_sound.hpp"
#include "sound.hpp"
#include "../resource/context.hpp"
#include "../resource/sounds.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/math/compare.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <numeric>
#include <functional>

sanguis::load::model::random_sound::random_sound(
	sge::parse::json::element_vector const &elements,
	resource::sounds const &ctx)
:
	rng(
		sge::random::inclusive_range<
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
			boost::bind(
				std::plus<
					probability_type
				>(),
				_1,
				boost::bind(
					&sound::probability,
					_2
				)
			)
		)
	);

	if(
		sge::math::almost_zero(
			normalization
		)
	)
		throw exception(
			SGE_TEXT("sound probabilities are 0!")
		);

	BOOST_FOREACH(
		sound_container::const_reference r,
		sounds_
	)
		ranges.push_back(
			r.probability() / normalization
		);
	
	SGE_ASSERT(ranges.size() == sounds_.size());
}

sge::audio::sound_ptr const
sanguis::load::model::random_sound::random() const
{
	if(sounds_.empty())
		return sge::audio::sound_ptr();
	
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
		SGE_TEXT("probability didn't match any sounds!")
	);
}
