#ifndef SANGUIS_LOAD_TILES_SET_HPP_INCLUDED
#define SANGUIS_LOAD_TILES_SET_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/tiles/orientation.hpp>
#include <sanguis/load/tiles/set_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
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
		sanguis::load::resource::textures const &,
		sanguis::creator::tile
	);

	~set();

	sge::texture::const_part_shared_ptr const
	orientation(
		sanguis::load::tiles::orientation const &
	) const;
private:
	typedef
	sanguis::load::tiles::orientation::internal_type
	orientation_internal_type;

	typedef
	std::unordered_map<
		orientation_internal_type,
		sge::texture::const_part_shared_ptr
	>
	element_map;

	element_map elements_;
};

}
}
}

#endif
