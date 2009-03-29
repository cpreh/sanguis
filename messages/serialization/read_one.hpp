#ifndef SANGUIS_MESSAGES_SERIALIZATION_READ_ONE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READ_ONE_HPP_INCLUDED

#include "istream.hpp"

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename Class
>
struct read_one {
	read_one(
		std::istream &is,
		Class &obj);

	template<
		typename Role
	>
	void operator()(
		Role &) const;
private:
	istream &is;
	mutable Class &obj;
};


