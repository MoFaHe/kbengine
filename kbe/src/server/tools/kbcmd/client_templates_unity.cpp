/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2017 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "kbcmd.h"
#include "client_templates.h"
#include "client_templates_unity.h"	
#include "entitydef/entitydef.h"
#include "entitydef/scriptdef_module.h"
#include "entitydef/property.h"
#include "entitydef/method.h"
#include "entitydef/datatype.h"

namespace KBEngine {	

static std::string headerBody = "/*\n\tGenerated by KBEngine!\n\tPlease do not modify this file!\n#REPLACE#\ttools = kbcmd\n*/\n\n";
static std::string moduleSuffix = "Base";

//-------------------------------------------------------------------------------------
ClientTemplatesUnity::ClientTemplatesUnity():
	ClientTemplates()
{
}

//-------------------------------------------------------------------------------------
ClientTemplatesUnity::~ClientTemplatesUnity()
{

}

//-------------------------------------------------------------------------------------
std::string ClientTemplatesUnity::typeToType(const std::string& type)
{
	if (type == "INT8")
	{
		return "SByte";
	}
	else if (type == "INT16")
	{
		return "Int16";
	}
	else if (type == "INT32")
	{
		return "Int32";
	}
	else if (type == "INT64")
	{
		return "Int64";
	}
	else if (type == "UINT8")
	{
		return "Byte";
	}
	else if (type == "UINT16")
	{
		return "UInt16";
	}
	else if (type == "UINT32")
	{
		return "UInt32";
	}
	else if (type == "UINT64")
	{
		return "UInt64";
	}
	else if (type == "FLOAT")
	{
		return "float";
	}
	else if (type == "DOUBLE")
	{
		return "double";
	}
	else if (type == "STRING")
	{
		return "string";
	}
	else if (type == "UNICODE")
	{
		return "string";
	}
	else if (type == "PYTHON")
	{
		return type;
	}
	else if (type == "PY_DICT")
	{
		return type;
	}
	else if (type == "PY_TUPLE")
	{
		return type;
	}
	else if (type == "PY_LIST")
	{
		return type;
	}
	else if (type == "BLOB")
	{
		return "byte[]";
	}
	else if (type == "ARRAY")
	{
		return "List";
	}
	else if (type == "FIXED_DICT")
	{
		return "Dictionary";
	}
#ifdef CLIENT_NO_FLOAT
	else if (type == "VECTOR2")
	{
		return "Vector2Int";
	}
	else if (type == "VECTOR3")
	{
		return "Vector3Int";
	}
	else if (type == "VECTOR4")
	{
		return "Vector4Int";
	}
#else
	else if (type == "VECTOR2")
	{
		return "Vector2";
	}
	else if (type == "VECTOR3")
	{
		return "Vector3";
	}
	else if (type == "VECTOR4")
	{
		return "Vector4";
	}
#endif
	else if (type == "MAILBOX")
	{
		return "byte[]";
	}

	return type;
}

//-------------------------------------------------------------------------------------
void ClientTemplatesUnity::onCreateTypeFileName()
{
	sourcefileName_ = "KBEAlias.cs";
}

//-------------------------------------------------------------------------------------
void ClientTemplatesUnity::onCreateModuleFileName(const std::string& moduleName)
{
	sourcefileName_ = moduleName + moduleSuffix + ".cs";
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypesBegin()
{
	sourcefileBody_ = headerBody;
	strutil::kbe_replace(sourcefileBody_, "#REPLACE#", "");

	sourcefileBody_ += "namespace KBEngine\n{\n";
	sourcefileBody_ += "\tusing UnityEngine;\n";
	sourcefileBody_ += "\tusing System;\n";
	sourcefileBody_ += "\tusing System.Collections;\n";
	sourcefileBody_ += "\tusing System.Collections.Generic;\n\n";

	sourcefileBody_ += "\n\n\t// defined in */scripts/entity_defs/alias.xml\n\n";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypesEnd()
{
	sourcefileBody_ += "\n}";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeBegin(std::string typeName, FixedDictType* pDataType)
{
	sourcefileBody_ += fmt::format("\tpublic class {}\n\t{{\n", typeName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeEnd(std::string typeName, FixedDictType* pDataType)
{
	sourcefileBody_ += "\n\t}\n\n";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeBegin(std::string typeName, FixedArrayType* pDataType, const std::string& parentClass)
{
	sourcefileBody_ += fmt::format("\tpublic class {}{}\n\t{{\n", typeName, (parentClass.size() > 0 ? std::string(" : ") + parentClass : ""));
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeEnd(std::string typeName, FixedArrayType* pDataType)
{
	sourcefileBody_ += "\n\t}\n\n";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_INT8(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic SByte {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_INT16(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic Int16 {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_INT32(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic Int32 {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_INT64(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic Int64 {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_UINT8(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic Byte {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_UINT16(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic UInt16 {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_UINT32(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic UInt32 {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_UINT64(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic UInt64 {} = 0;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_FLOAT(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic float {} = 0f;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_DOUBLE(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic double {} = 0d;\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_STRING(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic string {} = \"\";\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_UNICODE(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic string {} = \"\";\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_PYTHON(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PYTHON(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_PY_DICT(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PY_DICT(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_PY_TUPLE(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PY_TUPLE(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_PY_LIST(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PY_LIST(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_BLOB(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic byte[] {} = new byte[0];\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_ARRAY(const std::string& itemName, const std::string& childItemName, DataType* pDataType)
{
	std::string new_childItemName = childItemName;

	if (pDataType->type() == DATA_TYPE_FIXEDARRAY)
	{
		FixedArrayType* pFixedArrayType = static_cast<FixedArrayType*>(pDataType);

		// 如果元素又是数组
		if (pFixedArrayType->getDataType()->type() == DATA_TYPE_FIXEDARRAY)
		{
			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pDataType->aliasName(), fmt::format("List<{}>", pFixedArrayType->getDataType()->aliasName()));
			else
				new_childItemName = fmt::format("List<{}>", pFixedArrayType->getDataType()->aliasName());

			return writeTypeItemType_ARRAY(itemName, new_childItemName, pFixedArrayType->getDataType());
		}
		else if (pFixedArrayType->getDataType()->type() == DATA_TYPE_FIXEDDICT)
		{
			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pDataType->aliasName(), pFixedArrayType->getDataType()->aliasName());
			else
				new_childItemName = pFixedArrayType->getDataType()->aliasName();
		}
		else
		{
			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pDataType->aliasName(), typeToType(pFixedArrayType->getDataType()->getName()));
			else
				new_childItemName = typeToType(pFixedArrayType->getDataType()->getName());
		}
	}

	sourcefileBody_ += fmt::format("\t\tpublic List<{}> {} = new List<{}>();\n", new_childItemName, itemName, new_childItemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_FIXED_DICT(const std::string& itemName, const std::string& childItemName, DataType* pDataType)
{
	sourcefileBody_ += fmt::format("\t\tpublic {} {} = new {}();\n", childItemName, itemName, childItemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_VECTOR2(const std::string& itemName, const std::string& childItemName)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\t\tpublic Vector2Int {} = new Vector2Int(0, 0);\n", itemName);
#else
	sourcefileBody_ += fmt::format("\t\tpublic Vector2 {} = new Vector2(0f, 0f);\n", itemName);
#endif

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_VECTOR3(const std::string& itemName, const std::string& childItemName)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\t\tpublic Vector3Int {} = new Vector3Int(0, 0, 0);\n", itemName);
#else
	sourcefileBody_ += fmt::format("\t\tpublic Vector3 {} = new Vector2(0f, 0f, 0f);\n", itemName);
#endif

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_VECTOR4(const std::string& itemName, const std::string& childItemName)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\t\tpublic Vector4Int {} = new Vector4Int(0, 0, 0, 0);\n", itemName);
#else
	sourcefileBody_ += fmt::format("\t\tpublic Vector4 {} = new Vector4(0f, 0f, 0f, 0f);\n", itemName);
#endif

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeTypeItemType_MAILBOX(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\t\tpublic byte[] {} = new byte[0];\n", itemName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeModuleBegin(ScriptDefModule* pEntityScriptDefModule)
{
	std::string newModuleName = fmt::format("{}{}", pEntityScriptDefModule->getName(), moduleSuffix);

	sourcefileBody_ = headerBody;
	strutil::kbe_replace(sourcefileBody_, "#REPLACE#", fmt::format("\tPlease inherit this module, such as: (class {} : {}{})\n",
		pEntityScriptDefModule->getName(), pEntityScriptDefModule->getName(), moduleSuffix));

	sourcefileBody_ += "namespace KBEngine\n{\n";
	sourcefileBody_ += "\tusing UnityEngine;\n";
	sourcefileBody_ += "\tusing System;\n";
	sourcefileBody_ += "\tusing System.Collections;\n";
	sourcefileBody_ += "\tusing System.Collections.Generic;\n\n";

	sourcefileBody_ += std::string("\t// defined in */scripts/entity_defs/") + pEntityScriptDefModule->getName() + ".def\n";

	sourcefileBody_ += fmt::format("\tpublic abstract class {} : if_Entity_error_use______git_submodule_update_____kbengine_plugins_______open_this_file_and_I_will_tell_you\n\t{{\n", newModuleName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeModuleEnd(ScriptDefModule* pEntityScriptDefModule)
{
	sourcefileBody_ += "\t}\n}";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_INT8(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic SByte {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_INT16(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic Int16 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_INT32(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic Int32 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_INT64(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic Int64 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_UINT8(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic Byte {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_UINT16(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic UInt16 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_UINT32(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic UInt32 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_UINT64(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic UInt64 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_FLOAT(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic float {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0f"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_DOUBLE(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic double {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "0d"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_STRING(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic string {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "\"\""));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_UNICODE(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic string {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "\"\""));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_PYTHON(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PYTHON(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_PY_DICT(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PY_DICT(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_PY_TUPLE(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PY_TUPLE(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_PY_LIST(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PY_LIST(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_BLOB(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic byte[] {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new byte[0]"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_ARRAY(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	if (std::string("ARRAY") == pPropertyDescription->getDataTypeName())
	{
		return writeTypeItemType_ARRAY(pPropertyDescription->getName(), pPropertyDescription->getDataType()->aliasName(), pPropertyDescription->getDataType());
	}
	else
	{
		sourcefileBody_ += fmt::format("\t\tpublic {} {} = new {}();\n", pPropertyDescription->getDataTypeName(), pPropertyDescription->getName(),
			pPropertyDescription->getDataTypeName());
	}

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_FIXED_DICT(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic {} {} = new {}();\n", pPropertyDescription->getDataTypeName(), pPropertyDescription->getName(),
		pPropertyDescription->getDataTypeName());

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_VECTOR2(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\t\tpublic Vector2Int {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector2Int(0, 0)"));
#else
	sourcefileBody_ += fmt::format("\t\tpublic Vector2 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector2(0f, 0f)"));
#endif

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_VECTOR3(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\t\tpublic Vector3Int {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector3Int(0, 0, 0)"));
#else
	sourcefileBody_ += fmt::format("\t\tpublic Vector3 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector3(0f, 0f, 0f)"));
#endif

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_VECTOR4(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\t\tpublic Vector4Int {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector4Int(0, 0, 0, 0)"));
#else
	sourcefileBody_ += fmt::format("\t\tpublic Vector4 {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector4(0f, 0f, 0f, 0f)"));
#endif

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeProperty_MAILBOX(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t\tpublic byte[] {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new byte[0]"));

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeMethod(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, MethodDescription* pMethodDescription, const char* fillString)
{
	sourcefileBody_ += fmt::format("\t\tpublic abstract void {}({}); \n", pMethodDescription->getName(), fillString);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUnity::writeMethodArgs_ARRAY(FixedArrayType* pFixedArrayType, std::string& argsTypeBody, const std::string& childItemName)
{
	std::string new_childItemName = childItemName;

	if (pFixedArrayType->type() == DATA_TYPE_FIXEDARRAY)
	{
		// 如果元素又是数组
		if (pFixedArrayType->getDataType()->type() == DATA_TYPE_FIXEDARRAY)
		{
			FixedArrayType* pChildFixedArrayType = static_cast<FixedArrayType*>(pFixedArrayType->getDataType());

			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pFixedArrayType->aliasName(), fmt::format("List<{}>", pChildFixedArrayType->aliasName()));
			else
				new_childItemName = fmt::format("List<{}>", pChildFixedArrayType->aliasName());

			return writeMethodArgs_ARRAY(pChildFixedArrayType, argsTypeBody, new_childItemName);
		}
		else if (pFixedArrayType->getDataType()->type() == DATA_TYPE_FIXEDDICT)
		{
			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pFixedArrayType->aliasName(), pFixedArrayType->getDataType()->aliasName());
			else
				new_childItemName = pFixedArrayType->getDataType()->aliasName();
		}
		else
		{
			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pFixedArrayType->aliasName(), typeToType(pFixedArrayType->getDataType()->getName()));
			else
				new_childItemName = typeToType(pFixedArrayType->getDataType()->getName());
		}
	}

	argsTypeBody += fmt::format("List<{}>", new_childItemName);
	return true;
}

//-------------------------------------------------------------------------------------
}
