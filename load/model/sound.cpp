#include "sound.hpp"
#include "../resource/sounds.hpp"
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::sound::sound(
	sge::parse::json::member_vector const &members,
	resource::sounds const &ctx
)
:
	ctx(
		std::tr1::ref(
			ctx
		)
	),
	probability_(
		static_cast<
			probability_type
		>(
			sge::parse::json::find_member_exn<
				double
			>(
				members,
				FCPPT_TEXT("prob")
			)
		)
	),
	file(
		ctx.load(
			sge::parse::json::find_member_exn<
				sge::parse::json::string
			>(
				members,
				FCPPT_TEXT("file")
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
