#ifndef SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED

#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace resource
{

class animations
{
	FCPPT_NONCOPYABLE(
		animations
	);
public:
	animation::series const
	load(
		fcppt::filesystem::path const &
	) const;

	explicit animations(
		textures &
	);

	~animations();
private:
	animation::series const
	do_load(
		fcppt::filesystem::path const &
	) const;

	sge::texture::const_part_ptr const
	load_texture(
		fcppt::filesystem::path const &
	) const;

	animation::series const
	load_without_frames_file(
		fcppt::filesystem::path const &
	) const;

	typedef std::map<
		fcppt::filesystem::path,
		animation::series
	> animation_map;

	textures &textures_;

	mutable animation_map animations_;
};

}
}
}

#endif
