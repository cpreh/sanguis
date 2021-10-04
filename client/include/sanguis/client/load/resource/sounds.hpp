#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED

#include <sanguis/client/load/resource/optional_sound_fwd.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/player_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::load::resource
{

class sounds
{
	FCPPT_NONMOVABLE(
		sounds
	);
public:
	sounds(
		sge::audio::loader_ref,
		sge::audio::player_ref
	);

	~sounds();

	[[nodiscard]]
	sanguis::client::load::resource::optional_sound
	load(
		fcppt::string const &
	) const;

	[[nodiscard]]
	sanguis::client::load::resource::optional_sound
	load_path(
		std::filesystem::path const &
	) const;
private:
	using
	optional_buffer
	=
	fcppt::optional::object<
		sge::audio::buffer_unique_ptr
	>;

	using
	buffer_map
	=
	std::map<
		std::filesystem::path,
		optional_buffer
	>;

	sge::audio::loader_ref const multi_loader_;

	sge::audio::player_ref const player_;

	mutable buffer_map buffers_;
};

}

#endif
