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
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include "cstandard.h"
#include "klognetprotocol.h"

BOOST_CLASS_EXPORT_GUID(GetKlogServerPortEvent, "GetKlogServerPortEvent")
BOOST_CLASS_EXPORT_GUID(SendKlogServerPortEvent, "SendKlogServerPortEvent")
BOOST_CLASS_EXPORT_GUID(KlogSourceInfo, "KlogSourceInfo")
BOOST_CLASS_EXPORT_GUID(SendKlogConfigEvent, "SendKlogConfigEvent")
BOOST_CLASS_EXPORT_GUID(GetKlogConfigEvent, "GetKlogConfigEvent")
BOOST_CLASS_EXPORT_GUID(SendKlogMessageEvent, "SendKlogMessageEvent")
BOOST_CLASS_EXPORT_GUID(GetKlogMessageEvent, "GetKlogMessageEvent")

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
		void serialize(Archive & ar, GetKlogServerPortEvent & object, const unsigned int version)
		{
			ar & object.event_type;
			ar & object.client_type;
		}

		template<class Archive>
		void serialize(Archive & ar, SendKlogServerPortEvent & object, const unsigned int version)
		{
			ar & object.event_type;
			ar & object.sync_message_port;
			ar & object.async_message_port;
		}

		template<class Archive>
		void serialize(Archive & ar, KlogSourceInfo & object, const unsigned int version)
		{
			ar & object.sourece_ip;
			ar & object.source_port;
			ar & object.source_program_name;
		}

		template<class Archive>
		void serialize(Archive & ar, SendKlogConfigEvent & object, const unsigned int version)
		{
			ar & object.event_type;
			ar & object.klog_config;
			ar & object.source_info;
		}

		template<class Archive>
		void serialize(Archive & ar, GetKlogConfigEvent & object, const unsigned int version)
		{
			ar & object.event_type;
		}

		template<class Archive>
		void serialize(Archive & ar, SendKlogMessageEvent & object, const unsigned int version)
		{

			ar & object.event_type;
			ar & object.klog_message;
			ar & object.source_info;
		}

		template<class Archive>
		void serialize(Archive & ar, GetKlogMessageEvent & object, const unsigned int version)
		{
			ar & object.event_type;
			ar & object.source_info;
		}
	} // namespace serialization
} // namespace boost

