#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_TEXT_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class text
:
	public sanguis::client::draw2d::entities::own
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	text(
		sanguis::diff_clock const &,
		sanguis::client::draw2d::sprite::normal::system &,
		sge::font::object &,
		sge::font::string const &,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::sprite::normal::color
	);

	~text()
	override;
private:
	text(
		sanguis::diff_clock const &,
		sanguis::client::draw2d::sprite::normal::system &,
		sge::font::text_unique_ptr &&,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::sprite::normal::color
	);

	void
	update()
	override;

	bool
	may_be_removed() const
	override;

	sanguis::diff_timer life_time_;

	sge::texture::const_part_unique_ptr const texture_;

	sanguis::client::draw2d::sprite::normal::object sprite_;

	sanguis::client::draw2d::sprite::center const origin_;
};

}
}
}
}

#endif
