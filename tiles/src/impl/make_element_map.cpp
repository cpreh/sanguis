#include <sanguis/tiles/element_map.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/impl/decode_name.hpp>
#include <sanguis/tiles/impl/make_element_map.hpp>
#include <sanguis/tiles/impl/make_views.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tiles::element_map
sanguis::tiles::impl::make_element_map(
	sge::image2d::view::const_object const &_view,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::algorithm::map_optional<
			sanguis::tiles::element_map
		>(
			sge::parse::json::parse_file_exn(
				_path
				/
				FCPPT_TEXT("mapping.json")
			).object().members,
			[
				&_view
			](
				sge::parse::json::member const &_member
			)
			{
				return
					fcppt::optional_bind_construct(
						sanguis::tiles::impl::decode_name(
							_member.first
						),
						[
							&_view,
							&_member
						](
							sanguis::tiles::orientation const &_orientation
						)
						{
							return
								std::make_pair(
									_orientation,
									sanguis::tiles::impl::make_views(
										_view,
										_member.second
									)
								);
						}
					);
			}
		);
}
