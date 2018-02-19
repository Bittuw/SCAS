#pragma once

#ifndef DATA_STRUCTS
#define DATA_STRUCTS

#define Connection_Error_Code_Types \
	X(UNDEFINE, 0) \
	X(SUCCESS, 1) \
	X(CONVERTER_OPEN_FAIL, 2) \
	X(CONVERTER_COMMAND_FAIL, 3) \
	X(CONTROLLER_OPEN_FAIL, 4) \
	X(CONTROLLER_COMMAND_FAIL , 5) \
	X(CONNECTION_FAIL, 6)

namespace Connection_Types {
	enum class Connection_Error_Code {
#define X(name, value) name = value,
		Connection_Error_Code_Types
#undef X
	};

	static std::string Connection_Error_Code_String[] = {
	#define X(name, value) #name,
		Connection_Error_Code_Types
	#undef X
	};
}

#undef Connection_Error_Code_Types
#endif