#pragma once

#ifndef SERIALIZER
#define SERIALIZER

#include "DataBaseStructs.h"

namespace Serialization {

	using namespace Common_Database_Types;

	template <typename T> 
	struct Indentity {
		typedef typename T::value_type value_type;
	};

	class Serializer
	{
	public:
		template <typename...Args>
		Serializer(const Converters_Data_List& copy_converters_list, Args...args)
			:
			Serializer(args...)
		{
			_copy_converters_list = copy_converters_list;
			write(_copy_converters_list);

			_copy_converters_list.clear();
			_copy_converters_list.shrink_to_fit();

			read(_copy_converters_list);
		}
		template <typename...Args>
		Serializer(const Controllers_Data_List& copy_controllers_list, Args...args)
			:
			Serializer(args...)
		{
			_copy_controllers_list = copy_controllers_list;
			write(_copy_controllers_list);

			_copy_controllers_list.clear();
			try {
				read(_copy_controllers_list);
			}
			catch (std::exception& error) {
				Log(MessageTypes::ERR) << error.what();
			}
		}
		template <typename...Args>
		Serializer(const Groups_Data_List& copy_groups_list, Args...args)
			:
			Serializer(args...)
		{
			_copy_groups_list = copy_groups_list;
			write(_copy_groups_list);

			_copy_groups_list.clear();
			_copy_groups_list.shrink_to_fit();

			read(_copy_groups_list);
		}
		template <typename...Args>
		Serializer(const Employees_Data_List& copy_employees_list, Args...args)
			:
			Serializer(args...)
		{
			_copy_employees_list = copy_employees_list;
			write(copy_employees_list);

			_copy_employees_list.clear();
			_copy_employees_list.shrink_to_fit();

			read(_copy_employees_list);
		}
		template <typename...Args>
		Serializer(const Groups_In_Controllers_Data_List& copy_groups_In_Controllers_list, Args...args)
			:
			Serializer(args...)
		{
			_copy_groups_In_Controllers_list = copy_groups_In_Controllers_list;
			write(_copy_groups_In_Controllers_list);

			_copy_groups_In_Controllers_list.clear();
			_copy_groups_In_Controllers_list.shrink_to_fit();

			read(_copy_groups_In_Controllers_list);
		}
		~Serializer() {
			_copy_converters_list.clear();
			_copy_controllers_list.clear();
			_copy_groups_list.clear();
			_copy_employees_list.clear();
			_copy_groups_In_Controllers_list.clear();
		};

		//static void SerializatorInThread();
		Converters_Data_List _copy_converters_list;
		Controllers_Data_List _copy_controllers_list;
		Groups_Data_List _copy_groups_list;
		Employees_Data_List _copy_employees_list;
		Groups_In_Controllers_Data_List _copy_groups_In_Controllers_list;

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
					auto temp = new Indentity<L>::value_type::POD_type;
					input_file.read(reinterpret_cast<char*>(temp), sizeof(Indentity<L>::value_type::POD_type));
					list.push_back(Indentity<L>::value_type(*temp));
					delete temp;
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
