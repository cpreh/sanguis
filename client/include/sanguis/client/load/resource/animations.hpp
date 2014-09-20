#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED

#include <sanguis/client/load/resource/animations_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
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

class animations
{
	FCPPT_NONCOPYABLE(
		animations
	);
public:
	sanguis::client::load::resource::animation::series const &
	load(
		boost::filesystem::path const &
	) const;

	explicit
	animations(
		sanguis::client::load::resource::textures &
	);

	~animations();
private:
	sanguis::client::load::resource::animation::series
	do_load(
		boost::filesystem::path const &
	) const;

	sge::texture::const_part_unique_ptr
	load_texture(
		boost::filesystem::path const &
	) const;

	sanguis::client::load::resource::animation::series
	load_without_frames_file(
		boost::filesystem::path const &
	) const;

	typedef std::map<
		boost::filesystem::path,
		sanguis::client::load::resource::animation::series
	> animation_map;

	sanguis::client::load::resource::textures &textures_;

	mutable animation_map animations_;
};

}
}
}
}

#endif
