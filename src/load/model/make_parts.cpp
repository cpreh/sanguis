#include <sanguis/exception.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/json_header.hpp>
#include <sanguis/load/model/load_delay.hpp>
#include <sanguis/load/model/load_dim.hpp>
#include <sanguis/load/model/make_parts.hpp>
#include <sanguis/load/model/optional_delay.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/model/parse_json.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/part_map.hpp>
#include <sanguis/load/model/part_result.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::part_result
sanguis::load::model::make_parts(
	boost::filesystem::path const &_path,
	sanguis::load::resource::context const &_context
)
{
	sge::parse::json::start const start_return(
		sanguis::load::model::parse_json(
			_path
		)
	);

	sge::parse::json::object const &global_entries(
		start_return.object()
	);

	sge::parse::json::object const &header(
		sanguis::load::model::json_header(
			global_entries
		)
	);

	sanguis::load::model::optional_delay const opt_delay(
		sanguis::load::model::load_delay(
			header
		)
	);

	sanguis::load::model::optional_texture_identifier const texture(
		sanguis::load::model::find_texture(
			global_entries
		)
	);

	sge::parse::json::array const &parts_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			global_entries.members,
			FCPPT_TEXT("parts")
		)
	);

	sanguis::load::model::cell_size const cell_size(
		sanguis::load::model::load_dim(
			header
		)
	);

	sanguis::load::model::part_map parts;

	for(
		auto const &part : parts_array.elements
	)
	{
		sge::parse::json::member_map const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				part
			).members
		);

		if(
			inner_members.size() != 1
		)
			throw sanguis::exception(
				FCPPT_TEXT("inner members of the part array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			*inner_members.begin()
		);

		if(
			parts.insert(
				std::make_pair(
					member.first,
					fcppt::make_unique_ptr<
						sanguis::load::model::part
					>(
						sge::parse::json::get<
							sge::parse::json::object
						>(
							member.second
						),
						sanguis::load::model::global_parameters(
							_path,
							_context.textures(),
							_context.sounds(),
							cell_size,
							opt_delay,
							texture
						)
					)
				)
			)
			.second == false
		)
			FCPPT_LOG_WARNING(
				sanguis::load::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in model!")
			);
	}

	return
		sanguis::load::model::part_result(
			cell_size,
			std::move(
				parts
			)
		);
}
