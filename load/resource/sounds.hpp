#ifndef SANGUIS_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED

#include "../sound_type.hpp"
#include <sge/audio/sound_fwd.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <boost/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{

class sound_collection;

namespace resource
{

class sounds : boost::noncopyable {
public:
	sound_collection const &
	load(
		sge::filesystem::path const &) const;
	
	sge::audio::sound_ptr const
	make(
		sge::audio::file_ptr,
		sound_type::type) const;

	~sounds();
private:
	sound_collection const
	do_load(
		sge::filesystem::path const &) const;

	sounds(
		sge::audio::multi_loader &,
		sge::audio::player_ptr,
		sge::audio::pool &);

	friend class context;

	typedef std::map<
		sge::filesystem::path,
		sound_collection
	> sound_map;

	sge::audio::multi_loader &ml;
	sge::audio::player_ptr const player;
	sge::audio::pool &pool;
	mutable sound_map sounds_;
};

}
}
}

#endif
