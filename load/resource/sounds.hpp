#ifndef SANGUIS_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED

#include "sound_identifier.hpp"
#include "../sound_type.hpp"
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/player_ptr.hpp>
#include <sge/audio/buffer_ptr.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/file_ptr.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{

class sounds
{
	FCPPT_NONCOPYABLE(sounds)
public:
	sge::audio::file_ptr const
	load(
		sound_identifier const &
	) const;
	
	sge::audio::file_ptr const
	load_uncached(
		fcppt::filesystem::path const &
	) const;
	
	sge::audio::sound::base_ptr const
	make(
		sge::audio::file_ptr,
		sound_type::type
	) const;

	sge::audio::sound::positional_ptr const
	make_positional(
		sge::audio::file_ptr,
		sge::audio::sound::positional_parameters const &,
		sound_type::type
	) const;

	~sounds();
private:
	sge::audio::file_ptr const
	do_load(
		sound_identifier const &
	) const;

	sounds(
		sge::audio::multi_loader &,
		sge::audio::player_ptr,
		sge::audio::pool &
	);

	friend class context;

	typedef std::map<
		sound_identifier,
		sge::audio::file_ptr
	> sound_map;

	typedef
	std::map
	<
		sge::audio::file_ptr,
		sge::audio::buffer_ptr
	>
	buffer_map;

	sge::audio::multi_loader &ml_;

	sge::audio::player_ptr const player_;

	sge::audio::pool &pool_;

	mutable sound_map sounds_;

	mutable buffer_map buffers_;
};

}
}
}

#endif
