#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/shared_ptr_132.hpp>
#include "cstandard.h"

#include "klognetprotocol.h"

namespace boost
{
	namespace serialization
	{

		template<class Archive>
		void serialize(Archive & ar, NetEvent & object, const unsigned int version)
		{
			ar & object.event_type;
		}

		template<class Archive>
		void serialize(Archive & ar, KlogSourceInfo & object, const unsigned int version)
		{
			ar & object.sourece_ip;
			ar & object.source_port;
			ar & object.source_program_name;
		}

		template<class Archive>
		void serialize(Archive & ar, SendKlogConfig & object, const unsigned int version)
		{
			ar & object.event_type;
			ar & object.klog_config;
			ar & object.source_info;
		}

		template<class Archive>
		void serialize(Archive & ar, GetKlogConfig & object, const unsigned int version)
		{
			ar & object.event_type;
		}

		template<class Archive>
		void serialize(Archive & ar, SendKlogMessage & object, const unsigned int version)
		{

			ar & object.event_type;
			ar & object.klog_message;
			ar & object.source_info;
		}

		template<class Archive>
		void serialize(Archive & ar, GetKlogMessage & object, const unsigned int version)
		{
			ar & object.event_type;
			ar & object.source_info;
		}
	} // namespace serialization
} // namespace boost

