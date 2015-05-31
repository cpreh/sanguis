#ifndef SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container_ref_fwd.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/error.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/enum_array_decl.hpp>
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
namespace tiles
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sanguis::client::load::resource::textures const &
	);

	~context();

	sanguis::client::load::tiles::texture_container const &
	set(
		boost::filesystem::path const &,
		sanguis::tiles::area_container_ref const &
	);

	sanguis::tiles::collection &
	collection();

	sge::texture::part const &
	missing_texture(
		sanguis::tiles::error
	) const;
private:
	typedef
	std::map<
		boost::filesystem::path,
		sanguis::client::load::tiles::set
	>
	map_type;

	sanguis::tiles::collection collection_;

	sanguis::client::load::resource::textures const &textures_;

	map_type sets_;

	typedef
	fcppt::container::enum_array<
		sanguis::tiles::error,
		sge::texture::const_part_unique_ptr
	>
	missing_texture_array;

	missing_texture_array const missing_textures_;
};

}
}
}
}

#endif
