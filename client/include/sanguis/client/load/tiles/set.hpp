#ifndef SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_SET_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/category.hpp>
#include <sanguis/client/load/tiles/name.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
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

	~set();

	sge::texture::const_part_shared_ptr
	orientation(
		sanguis::client::load::tiles::orientation const &
	) const;
private:
	typedef
	sanguis::client::load::tiles::orientation::internal_type
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
}

#endif
