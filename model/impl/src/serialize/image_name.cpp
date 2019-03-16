#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>


fcppt::optional::object<
	sge::parse::json::member
>
sanguis::model::impl::serialize::image_name(
	sanguis::model::optional_image_name const &_opt_name
)
{
	return
		fcppt::optional::map(
			_opt_name,
			[](
				sanguis::model::image_name const &_name
			)
			{
				return
					sge::parse::json::member{
						sge::charconv::utf8_string{
							"texture"
						},
						sge::parse::json::make_value(
							sge::charconv::fcppt_string_to_utf8(
								_name.get()
							)
						)
					};
			}
		);
}
