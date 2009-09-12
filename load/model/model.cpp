#include "model.hpp"
#include "split_first_slash.hpp"
#include "optional_delay.hpp"
#include "find_texture.hpp"
#include "global_parameters.hpp"
#include "../../exception.hpp"
#include "../resource/context.hpp"
#include "../resource/textures.hpp"
#include "../log.hpp"
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/stem.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/parse/json/parse_file.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/random/last_exclusive_range.hpp>
#include <sge/fstream.hpp>
#include <sge/text.hpp>
#include <boost/next_prior.hpp>
#include <boost/foreach.hpp>
#include <utility>

// TODO: split this stuff!

namespace
{

sge::renderer::dim_type const
load_dim(
	sge::parse::json::member_vector const &entries)
{
	sge::parse::json::array const &array(
		sge::parse::json::find_member<
			sge::parse::json::array
		>(
			entries,
			SGE_TEXT("cell_dimensions")
		)
	);

	sge::parse::json::element_vector const &elements(
		array.elements
	);

	if(elements.size() < 2)
		throw sanguis::exception(
			SGE_TEXT("Insufficient members in cell_dimensions!")
		);
	
	return sge::renderer::dim_type(
		static_cast<sge::renderer::size_type>(
			sge::parse::json::get<
				int	
			>(
				elements[0]
			)
		),
		static_cast<sge::renderer::size_type>(
			sge::parse::json::get<
				int	
			>(
				elements[1]
			)
		)
	);
}

sanguis::load::model::optional_delay const
load_delay(
	sge::parse::json::member_vector const &entries)
{
	try
	{
		return sge::parse::json::find_member<
			int
		>(
			entries,
			SGE_TEXT("delay")
		);
	}
	catch(sanguis::exception const &e)
	{
		return sanguis::load::model::optional_delay();
	}
}

}

sanguis::load::model::part const &
sanguis::load::model::model::operator[](
	sge::string const &name) const
{
	part_map::const_iterator const it(
		parts.find(
			name
		)
	);

	if(it == parts.end())
		throw exception(
			SGE_TEXT("Category \"")
			+ name
			+ SGE_TEXT("\" not found in ")
			+ path.string()
		);
	
	return it->second;
}

sanguis::load::model::part const &
sanguis::load::model::model::random_part() const
{
	if(!random_part_)
		random_part_.reset(
			new part_rand(
				sge::random::make_last_exclusive_range(
					static_cast<part_map::size_type>(0),
					parts.size()
				)
			)
		);

	return boost::next(
		parts.begin(),
		(*random_part_)()
	)->second;
}

sanguis::load::model::model::size_type
sanguis::load::model::model::size() const
{
	return parts.size();
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::begin() const
{
	return parts.begin();
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::end() const
{
	return parts.end();
}

sge::renderer::dim_type const
sanguis::load::model::model::dim() const
{
	return cell_size;
}

sanguis::load::model::model::model(
	sge::filesystem::path const &path,
	resource::context const &ctx)
:
	path(path),
	parts()
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("Entering ")
			<< path.string()
	);

	try
	{
		construct(
			ctx
		);
	}
	catch(sge::exception const &e)
	{
		SGE_LOG_ERROR(
			log(),
			sge::log::_1
				<< SGE_TEXT("model \"")
				<< path.string()
				<< SGE_TEXT("\": \"")
				<< e.string()
				<< SGE_TEXT('"')
		);

		throw;
	}
}

void sanguis::load::model::model::construct(
	resource::context const &ctx)
{
	sge::filesystem::path const file(
		path / (sge::filesystem::stem(path) + SGE_TEXT(".json"))
	);

	sge::parse::json::object object_return;
	
	if(
		!sge::parse::json::parse_file(
			file,
			object_return
		)
	)
	{
		SGE_LOG_WARNING(
			sanguis::load::log(),
			sge::log::_1
				<< file 
				<< SGE_TEXT(" contains errors!")
			);
	}

	sge::parse::json::member_vector const &global_entries(
		object_return.members
	);

	sge::parse::json::object const &header(
		sge::parse::json::find_member<
			sge::parse::json::object
		>(
			global_entries,
			SGE_TEXT("header")
		)
	);

	cell_size = load_dim(
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

	BOOST_FOREACH(
		sge::parse::json::element_vector::const_reference r,
		sge::parse::json::find_member<
			sge::parse::json::array
		>(
			global_entries,
			SGE_TEXT("parts")
		).elements
	)
	{
		sge::parse::json::member_vector const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				r
			).members
		);

		if(inner_members.size() != 1)
			throw exception(
				SGE_TEXT("inner members of the part array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			inner_members[0]
		);

		if(
			parts.insert(
				std::make_pair(
					member.name,
					part(
						sge::parse::json::get<
							sge::parse::json::object
						>(
							member.value_
						),
						global_parameters(
							path,
							ctx.textures(),
							cell_size,
							opt_delay,
							texture,
							ctx.sounds()
						)
					)
				)
			)
			.second == false
		)
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< SGE_TEXT("Double insert in model!")
			);
	}
}
