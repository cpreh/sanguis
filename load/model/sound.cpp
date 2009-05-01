#include "sound.hpp"
#include "get_entry.hpp"
#include "../resource/sounds.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/text.hpp>

sanguis::load::model::sound::sound(
	sge::parse::json::member_vector const &members,
	resource::sounds const &ctx)
:
	ctx(
		std::tr1::ref(
			ctx
		)
	),
	probability_(
		get_entry<
			double
		>(
			members,
			SGE_TEXT("prob")
		)
	),
	file(
		ctx.load(
			get_entry<
				sge::parse::json::string
			>(
				members,
				SGE_TEXT("file")
			)
		)
	)
{}

sanguis::load::probability_type
sanguis::load::model::sound::probability() const
{
	return probability_;
}

sge::audio::sound_ptr const
sanguis::load::model::sound::make() const
{
	return ctx.get().make(
		file,
		sound_type::nonstream
	);
}
