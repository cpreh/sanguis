#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/load/model/random_sound.hpp>
#include <sanguis/load/model/sound.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sanguis/load/resource/sounds.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_real_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <numeric>
#include <fcppt/config/external_end.hpp>

sanguis::load::model::random_sound::random_sound(
	sanguis::random_generator &_random_generator,
	sge::parse::json::element_vector const &_elements,
	resource::sounds const &_ctx
)
:
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

	load::probability_type const normalization(
		std::accumulate(
			sounds_.begin(),
			sounds_.end(),
			static_cast<
				load::probability_type
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
		normalization
		<=
		static_cast<
			load::probability_type
		>(
			0.001f
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("sound probabilities are (almost) 0!")
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

	FCPPT_ASSERT_ERROR(
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
