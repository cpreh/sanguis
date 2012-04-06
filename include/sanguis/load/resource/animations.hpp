#ifndef SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED

#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
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

class animations
{
	FCPPT_NONCOPYABLE(
		animations
	);
public:
	animation::series const
	load(
		boost::filesystem::path const &
	) const;

	explicit animations(
		textures &
	);

	~animations();
private:
	animation::series const
	do_load(
		boost::filesystem::path const &
	) const;

	sge::texture::const_part_shared_ptr const
	load_texture(
		boost::filesystem::path const &
	) const;

	animation::series const
	load_without_frames_file(
		boost::filesystem::path const &
	) const;

	typedef std::map<
		boost::filesystem::path,
		animation::series
	> animation_map;

	textures &textures_;

	mutable animation_map animations_;
};

}
}
}

#endif
