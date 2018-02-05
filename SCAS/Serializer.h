#pragma once

#ifndef SERIALIZER
#define SERIALIZER

#include "DataBaseStructs.h"

namespace Serialization {

	using namespace Mysql_Types;

	template <typename T> 
	struct Indentity {
		typedef typename T::value_type value_type;
	};

	class Serializer
	{
	public:
		template <typename L, typename...Args>
		Serializer(L& list, Args&...args)
			:
			Serializer(args...)
		{
			write(list);
			list.clear();
			list.shrink_to_fit();
		}
		~Serializer() {	};

	protected:

		Serializer() {
			LPWSTR dir = TEXT("Backup");
			CreateDirectory(dir, NULL);
		}

		template <typename L>
		void write(const L& list) {
			Log(MessageTypes::TRACE) << LoggerFormat::format("Write % data.", *Indentity<L>::value_type::_table_name);

			try {
				auto File_Name = "Backup\\" + *Indentity<L>::value_type::_table_name + ".data";

				size_t size = list.size();
				std::ofstream out_file(File_Name, std::ios::binary);
				if (!out_file.is_open())
					throw std::runtime_error(LoggerFormat::format("Could not open file %", *Indentity<L>::value_type::_table_name));

				out_file.write((char*)&size, sizeof(size));
				for (auto item : list) {
					out_file.write(reinterpret_cast<char*>(&static_cast<Indentity<L>::value_type::POD_type>(item)), sizeof(Indentity<L>::value_type::POD_type));
				}

				out_file.close();
			}
			catch (std::exception& error) {
				Log(MessageTypes::ERR) << LoggerFormat::format("Error while write to %: %", *Indentity<L>::value_type::_table_name, error.what());
			}
		}

		template <typename L>
		void read(L& list) {
			Log(MessageTypes::TRACE) << LoggerFormat::format("Read % data.", *Indentity<L>::value_type::_table_name);
			
			try {
				auto File_Name = "Backup\\" + *Indentity<L>::value_type::_table_name + ".data";
				size_t size = 0;

				std::ifstream input_file(File_Name, std::ios::binary);
				if (!input_file.is_open())
					throw std::runtime_error(LoggerFormat::format("Could not open file %", *Indentity<L>::value_type::_table_name));

				input_file.read((char*)&size, sizeof(size));
				for (; size > 0; size--) {
					Indentity<L>::value_type::POD_type temp;
					input_file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
					list.push_back(temp);
				}
				
				input_file.close();
			}
			catch (std::exception& error) {
				Log(MessageTypes::ERR) << LoggerFormat::format("Error while read to %: %", *Indentity<L>::value_type::_table_name, error.what());
			}
		}
	};

	
}

#endif
