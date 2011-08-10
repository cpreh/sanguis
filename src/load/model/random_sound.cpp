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
#include <functional>
#include <numeric>

sanguis::load::model::random_sound::random_sound(
	sge::parse::json::element_vector const &_elements,
	resource::sounds const &_ctx
)
:
	rng_(
		fcppt::random::inclusive_range<
			load::probability_type
		>(
			0,
			1
		)
	)
{
	for(
		sge::parse::json::element_vector::const_iterator it(
			_elements.begin()
		);
		it != _elements.end();
		++it
	)
	{
		sounds_.push_back(
			model::sound(
				sge::parse::json::get<
					sge::parse::json::object
				>(
					*it
				).members,
				_ctx
			)
		);
	}

	if(
		sounds_.empty()
	)
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
					load::probability_type
				>(),
				std::tr1::placeholders::_1,
				std::tr1::bind(
					&model::sound::probability,
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
		throw sanguis::exception(
			FCPPT_TEXT("sound probabilities are 0!")
		);

	for(
		sound_container::const_iterator it(
			sounds_.begin()
		);
		it != sounds_.end();
		++it
	)
		ranges_.push_back(
			it->probability()
			/ normalization
		);

	FCPPT_ASSERT(
		ranges_.size() == sounds_.size()
	);
}

sanguis::load::model::random_sound::~random_sound()
{
}

sge::audio::sound::positional_ptr const
sanguis::load::model::random_sound::random() const
{
	if(
		sounds_.empty()
	)
		return sge::audio::sound::positional_ptr();

	load::probability_type const number(
		rng_()
	);

	for(
		range_vector::size_type index = 0;
		index < ranges_.size();
		++index
	)
		if(
			number < ranges_[index]
		)
			return sounds_[index].make();

	throw sanguis::exception(
		FCPPT_TEXT("probability didn't match any sounds!")
	);
}
