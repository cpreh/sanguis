#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/load/model/object.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/json_header.hpp>
#include <sanguis/load/model/load_delay.hpp>
#include <sanguis/load/model/load_dim.hpp>
#include <sanguis/load/model/optional_delay.hpp>
#include <sanguis/load/model/parse_json.hpp>
#include <sanguis/load/model/split_first_slash.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/log.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_int.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::load::model::object::~object()
{
}

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
		random_part_.take(
			fcppt::make_unique_ptr<
				part_rand
			>(
				fcppt::ref(
					random_generator_
				),
				part_map_distribution(
					part_map_distribution::min(
						0u
					),
					part_map_distribution::max(
						parts_.size() - 1u
					)
				)
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
	boost::filesystem::path const &_path,
	resource::context const &_ctx,
	sanguis::random_generator &_random_generator
)
:
	path_(
		_path
	),
	random_generator_(
		_random_generator
	),
	parts_(),
	random_part_()
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
		this->construct(
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

	sge::parse::json::member_map const &global_entries(
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
		sge::parse::json::member_map const &inner_members(
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
			*inner_members.begin()
		);

		if(
			fcppt::container::ptr::insert_unique_ptr_map(
				parts_,
				member.first,
				fcppt::make_unique_ptr<
					part
				>(
					sge::parse::json::get<
						sge::parse::json::object
					>(
						member.second
					),
					model::global_parameters(
						random_generator_,
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
