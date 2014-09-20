#ifndef SANGUIS_CLIENT_LOAD_HUD_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_CONTEXT_HPP_INCLUDED

#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace hud
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

	// TODO: optional_ref
	sge::texture::const_part_shared_ptr const
	weapon_icon(
		sanguis::weapon_type
	);
private:
	typedef
	std::map<
		sanguis::weapon_type,
		sge::texture::const_part_shared_ptr
	>
	weapon_icon_map;

	weapon_icon_map weapon_icons_;
};

}
}
}
}

#endif
