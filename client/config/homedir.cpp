#include "homedir.hpp"
#include "../../exception.hpp"
#include <sge/config/homedir.hpp>
#include <sge/filesystem/exists.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/create_directory.hpp>
#include <sge/text.hpp>

sge::filesystem::path const sanguis::client::config::homedir()
{
	sge::filesystem::path const p = 
		sge::config::homedir()/SGE_TEXT(".sanguis");

	if (!sge::filesystem::exists(p))
		if (!sge::filesystem::create_directory(p))
			throw exception(SGE_TEXT("Home path ")+p.string()+SGE_TEXT(" does not exists and cannot be created"));
			
	
	if (!sge::filesystem::is_directory(p))
		throw exception(SGE_TEXT("Home path ")+p.string()+SGE_TEXT(" exists but is not a directory"));
	
	return p;
}
