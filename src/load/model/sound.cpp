#include <sanguis/load/model/sound.hpp>
#include <sanguis/load/resource/sounds.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::sound::sound(
	sge::parse::json::member_vector const &_members,
	resource::sounds const &_ctx
)
:
	ctx_(
		fcppt::ref(
			_ctx
		)
	),
	probability_(
		static_cast<
			probability_type
		>(
			sge::parse::json::find_member_exn<
				double
			>(
				_members,
				FCPPT_TEXT("prob")
			)
		)
	),
	file_(
		_ctx.load(
			sge::parse::json::find_member_exn<
				sge::parse::json::string
			>(
				_members,
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

sge::audio::sound::positional_ptr const
sanguis::load::model::sound::make() const
{
	return
		ctx_.get().make_positional(
			file_,
			sge::audio::sound::positional_parameters(),
			sound_type::nonstream
		);
}
