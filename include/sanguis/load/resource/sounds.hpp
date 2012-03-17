#ifndef SANGUIS_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED

#include <sanguis/load/resource/sound_identifier.hpp>
#include <sanguis/load/sound_type.hpp>
#include <sge/audio/buffer_ptr.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/file_ptr.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis
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

	sge::audio::file_ptr const
	load(
		resource::sound_identifier const &
	) const;

	sge::audio::file_ptr const
	load_uncached(
		boost::filesystem::path const &
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
private:
	template<
		typename Ret
	>
	Ret const
	make_impl(
		sge::audio::file_ptr,
		sound_type::type,
		fcppt::function::object<
			Ret (sge::audio::file_ptr)
		> const &,
		fcppt::function::object<
			Ret (sge::audio::buffer *)
		> const &
	) const;

	sge::audio::file_ptr const
	do_load(
		sound_identifier const &
	) const;

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

	sge::audio::loader &ml_;

	sge::audio::player &player_;

	mutable sound_map sounds_;

	mutable buffer_map buffers_;
};

}
}
}

#endif
