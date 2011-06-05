#include "object.hpp"
#include "find_texture.hpp"
#include "global_parameters.hpp"
#include "json_header.hpp"
#include "load_delay.hpp"
#include "load_dim.hpp"
#include "optional_delay.hpp"
#include "parse_json.hpp"
#include "split_first_slash.hpp"
#include "part.hpp"
#include "../../exception.hpp"
#include "../resource/context.hpp"
#include "../resource/textures.hpp"
#include "../log.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/random/make_last_exclusive_range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <boost/next_prior.hpp>

sanguis::load::model::object::~object()
{}

sanguis::load::model::part const &
sanguis::load::model::object::operator[](
	fcppt::string const &_name
) const
{
	part_map::const_iterator const it(
		parts_.find(
			_name
		)
	);

	if(
		it == parts_.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("Category \"")
			+ _name
			+ FCPPT_TEXT("\" not found in ")
			+ fcppt::filesystem::path_to_string(
				path_
			)
		);
	
	return *it->second;
}

sanguis::load::model::part const &
sanguis::load::model::object::random_part() const
{
	if(
		!random_part_
	)
		random_part_ =
			fcppt::make_unique_ptr<
				part_rand
			>(
				fcppt::random::make_last_exclusive_range(
					static_cast<part_map::size_type>(0),
					parts_.size()
				)
			);

	return
		*boost::next(
			parts_.begin(),
			(*random_part_)()
		)->second;
}

sanguis::load::model::object::size_type
sanguis::load::model::object::size() const
{
	return parts_.size();
}

sanguis::load::model::object::const_iterator
sanguis::load::model::object::begin() const
{
	return parts_.begin();
}

sanguis::load::model::object::const_iterator
sanguis::load::model::object::end() const
{
	return parts_.end();
}

sge::renderer::dim2 const
sanguis::load::model::object::dim() const
{
	return cell_size_;
}

sanguis::load::model::object::object(
	fcppt::filesystem::path const &_path,
	resource::context const &_ctx
)
:
	path_(_path),
	parts_()
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Entering ")
			<< fcppt::filesystem::path_to_string(
				path_
			)
	);

	try
	{
		construct(
			_ctx
		);
	}
	catch(sge::exception const &e)
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("model \"")
				<< fcppt::filesystem::path_to_string(
					path_
				)
				<< FCPPT_TEXT("\": \"")
				<< e.string()
				<< FCPPT_TEXT('"')
		);

		throw;
	}
}

void
sanguis::load::model::object::construct(
	resource::context const &_ctx
)
{
	sge::parse::json::object object_return;
	
	parse_json(
		path_,
		object_return
	);

	sge::parse::json::member_vector const &global_entries(
		object_return.members
	);

	sge::parse::json::object const &header(
		json_header(
			global_entries
		)
	);

	cell_size_ = load_dim(
		header.members
	);

	optional_delay const opt_delay(
		load_delay(
			header.members
		)
	);

	optional_texture_identifier const texture(
		find_texture(
			global_entries
		)
	);

	sge::parse::json::array const &parts_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			global_entries,
			FCPPT_TEXT("parts")
		)
	);

	for(
		sge::parse::json::element_vector::const_iterator it(
			parts_array.elements.begin()
		);
		it != parts_array.elements.end();
		++it
	)
	{
		sge::parse::json::member_vector const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				*it
			).members
		);

		if(
			inner_members.size() != 1
		)
			throw sanguis::exception(
				FCPPT_TEXT("inner members of the part array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			inner_members[0]
		);

		if(
			fcppt::container::ptr::insert_unique_ptr_map(
				parts_,
				member.name,
				fcppt::make_unique_ptr<
					part
				>(
					sge::parse::json::get<
						sge::parse::json::object
					>(
						member.value
					),
					model::global_parameters(
						path_,
						_ctx.textures(),
						cell_size_,
						opt_delay,
						texture,
						_ctx.sounds()
					)
				)
			)
			.second == false
		)
			FCPPT_LOG_WARNING(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in model!")
			);
	}
}
