#ifndef SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

class set
{
	FCPPT_NONCOPYABLE(
		set
	);
public:
	set(
		sanguis::client::load::resource::textures const &,
		std::filesystem::path const &
	);

	set(
		set &&
	);

	// TODO: Why does this not work?
/*
	set &
	operator=(
		set &&
	);*/

	~set();

	sanguis::client::load::tiles::texture_container const &
	areas(
		sanguis::tiles::area_container_ref
	);
private:
	fcppt::reference<
		sge::texture::part const
	> texture_;

	typedef
	std::map<
		sanguis::tiles::area_container_ref,
		sanguis::client::load::tiles::texture_container
	>
	element_map;

	element_map elements_;
};

}
}
}
}

#endif
