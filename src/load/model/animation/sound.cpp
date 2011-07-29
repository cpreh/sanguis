#include "sound.hpp"
#include "../conditional_sound.hpp"
#include "../../log.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <iterator>

namespace
{

typedef fcppt::container::array<
	fcppt::string,
	sanguis::animation_sound_type::size
> animation_sound_array;

animation_sound_array const animation_sounds = {{
	FCPPT_TEXT("start"),
	FCPPT_TEXT("running")
}};

sanguis::animation_sound_type::type
find_sound_type(
	fcppt::string const &_name
)
{
	return
		static_cast<
			sanguis::animation_sound_type::type
		>(
			std::distance(
				animation_sounds.begin(),
				fcppt::algorithm::find_exn(
					animation_sounds.begin(),
					animation_sounds.end(),
					_name
				)
			)
		);
}

}

sge::audio::sound::positional_ptr const
sanguis::load::model::animation::sound::operator[](
	animation_sound_type::type const _sound_type
) const
{
	sound_map::const_iterator const it(
		sounds_.find(
			_sound_type
		)
	);
	
	return
		it == sounds_.end()
		?
			sge::audio::sound::positional_ptr()
		:
			it->second->random();
}

sanguis::load::model::animation::sound::sound()
:
	sounds_()
{
}

sanguis::load::model::animation::sound::~sound()
{
}

sanguis::load::model::animation::sound::sound(
	sge::parse::json::member_vector const &_members,
	resource::sounds const &_ctx
)
:
	sounds_()
{
	for(
		sge::parse::json::member_vector::const_iterator it(
			_members.begin()
		);
		it != _members.end();
		++it
	)
	{
		if(
			fcppt::container::ptr::insert_unique_ptr_map(
				sounds_,
				::find_sound_type(
					it->name
				),
				fcppt::make_unique_ptr<
					model::conditional_sound
				>(
					sge::parse::json::get<
						sge::parse::json::object
					>(
						it->value
					).members,
					fcppt::cref(
						_ctx
					)
				)
			).second == false
		)
			FCPPT_LOG_WARNING(
				load::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in sounds!")
			);
	}
}
