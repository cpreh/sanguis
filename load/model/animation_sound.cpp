#include "animation_sound.hpp"
#include "../resource/context.hpp"
#include "../resource/sounds.hpp"
#include "../../exception.hpp"
#include <sge/random/exclusive_range_error.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <boost/array.hpp>
#include <utility>
#include <iterator>

sge::audio::sound_ptr const
sanguis::load::model::animation_sound::operator[](
	animation_sound_type::type const stype) const
{
	animation_sound_map::const_iterator const it(
		sounds.find(stype));
	
	if(it == sounds.end())
		return sge::audio::sound_ptr();
	
	return it->second.random();
}

sanguis::load::model::animation_sound::animation_sound(
	sge::filesystem::path const &path,
	resource::context const &ctx)
{
	typedef boost::array<
		sge::string,
		animation_sound_type::size
	> animation_sound_array;

	animation_sound_array const animation_sounds = {{
		SGE_TEXT("start"),
		SGE_TEXT("running"),
		SGE_TEXT("end")
	}};

	for(animation_sound_array::const_iterator it(animation_sounds.begin());
	    it != animation_sounds.end();
	    ++it)
	{
		sge::filesystem::path const sound_path(path / *it);
		
		try
		{
			if(sounds.insert(
				std::make_pair(
					static_cast<animation_sound_type::type>(
						std::distance(
							animation_sounds.begin(),
							it)),
					conditional_sound(
						ctx.sounds().load(
							sound_path),
						ctx)))
			.second == false)
				throw exception(
					SGE_TEXT("Double insert in model::animation_sound: ")
					+ sound_path.string());
		}
		catch(sge::random::exclusive_range_error const &)
		{
			// range of sounds was empty, don't do anything
		}
	}
}
