#include <sanguis/tiles/exception.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/orientation_map.hpp>
#include <sanguis/tiles/impl/decode_name.hpp>
#include <sanguis/tiles/impl/make_areas.hpp>
#include <sanguis/tiles/impl/make_orientation_map.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tiles::orientation_map
sanguis::tiles::impl::make_orientation_map(
	boost::filesystem::path const &_path,
	sge::image2d::dim const _size
)
{
	return
		fcppt::algorithm::map_optional<
			sanguis::tiles::orientation_map
		>(
			sge::parse::json::parse_file_exn(
				_path
				/
				FCPPT_TEXT("mapping.json")
			).object().members,
			[
				_size
			](
				sge::parse::json::member const &_member
			)
			{
				return
					fcppt::optional::map(
						sanguis::tiles::impl::decode_name(
							fcppt::optional::to_exception(
								sge::charconv::utf8_string_to_fcppt(
									_member.first
								),
								[]{
									return
										sanguis::tiles::exception{
											FCPPT_TEXT("Failed to convert tile name")
										};
								}
							)
						),
						[
							_size,
							&_member
						](
							sanguis::tiles::orientation const &_orientation
						)
						{
							return
								std::make_pair(
									_orientation,
									sanguis::tiles::impl::make_areas(
										_size,
										_member.second.get()
									)
								);
						}
					);
			}
		);
}
