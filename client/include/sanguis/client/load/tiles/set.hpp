#ifndef SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/category.hpp>
#include <sanguis/client/load/tiles/const_optional_texture_container_ref_fwd.hpp>
#include <sanguis/client/load/tiles/name.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/bitfield/std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <unordered_map>
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
		sanguis::client::load::tiles::category const &,
		sanguis::client::load::tiles::name const &
	);

	set(
		set &&
	);

	set &
	operator=(
		set &&
	);

	~set();

	sanguis::client::load::tiles::const_optional_texture_container_ref
	orientation(
		sanguis::client::load::tiles::orientation const &
	) const;
private:
	set(
		sanguis::client::load::resource::textures const &,
		boost::filesystem::path const &
	);

	sge::texture::const_part_shared_ptr texture_;

	typedef
	std::unordered_map<
		sanguis::client::load::tiles::orientation,
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
