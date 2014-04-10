#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED

#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sge/audio/buffer_shared_ptr.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

class sounds
{
	FCPPT_NONCOPYABLE(
		sounds
	);
public:
	sounds(
		sge::audio::loader &,
		sge::audio::player &
	);

	~sounds();

	sge::audio::buffer_shared_ptr
	load(
		fcppt::string const &
	) const;

	sge::audio::buffer_shared_ptr
	load_path(
		boost::filesystem::path const &
	) const;
private:
	typedef
	std::map<
		boost::filesystem::path,
		sge::audio::buffer_shared_ptr
	>
	buffer_map;

	sge::audio::loader &multi_loader_;

	sge::audio::player &player_;

	mutable buffer_map buffers_;
};

}
}
}
}

#endif
