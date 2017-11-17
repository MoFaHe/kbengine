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
#include "client_templates_ue4.h"	
#include "entitydef/entitydef.h"
#include "entitydef/scriptdef_module.h"
#include "entitydef/property.h"
#include "entitydef/method.h"
#include "entitydef/datatype.h"

namespace KBEngine {	

static std::string headerBody = "/*\n\tGenerated by KBEngine!\n\tPlease do not modify this file!\n#REPLACE#\ttools = kbcmd\n*/\n\n";
static std::string moduleSuffix = "Base";

//-------------------------------------------------------------------------------------
ClientTemplatesUE4::ClientTemplatesUE4():
	ClientTemplates(),
	initBody_()
{
}

//-------------------------------------------------------------------------------------
ClientTemplatesUE4::~ClientTemplatesUE4()
{

}

//-------------------------------------------------------------------------------------
std::string ClientTemplatesUE4::typeToType(const std::string& type)
{
	if (type == "INT8")
	{
		return "int8";
	}
	else if (type == "INT16")
	{
		return "int16";
	}
	else if (type == "INT32")
	{
		return "int32";
	}
	else if (type == "INT64")
	{
		return "int64";
	}
	else if (type == "UINT8")
	{
		return "uint8";
	}
	else if (type == "UINT16")
	{
		return "uint16";
	}
	else if (type == "UINT32")
	{
		return "uint32";
	}
	else if (type == "UINT64")
	{
		return "uint64";
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
		return "FString";
	}
	else if (type == "UNICODE")
	{
		return "FString";
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
		return "TArray";
	}
	else if (type == "FIXED_DICT")
	{
		return "TMap";
	}
#ifdef CLIENT_NO_FLOAT
	else if (type == "VECTOR2")
	{
		return "FVector2D";
	}
	else if (type == "VECTOR3")
	{
		return "FVector";
	}
	else if (type == "VECTOR4")
	{
		return "FVector4";
	}
#else
	else if (type == "VECTOR2")
	{
		return "FVector2D";
	}
	else if (type == "VECTOR3")
	{
		return "FVector";
	}
	else if (type == "VECTOR4")
	{
		return "FVector4";
	}
#endif
	else if (type == "MAILBOX")
	{
		return "TArray<uint8>";
	}

	return type;
}

//-------------------------------------------------------------------------------------
void ClientTemplatesUE4::onCreateTypeFileName()
{
	sourcefileName_ = "KBEAlias.h";
}

//-------------------------------------------------------------------------------------
void ClientTemplatesUE4::onCreateModuleFileName(const std::string& moduleName)
{
	sourcefileName_ = moduleName + moduleSuffix + ".h";
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypesBegin()
{
	sourcefileBody_ = headerBody;
	strutil::kbe_replace(sourcefileBody_, "#REPLACE#", "");

	sourcefileBody_ += "#pragma once\n\n";
	sourcefileBody_ += "#include \"KBECommon.h\"\n";

	sourcefileBody_ += "\n\n// defined in */scripts/entity_defs/alias.xml\n\n";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypesEnd()
{
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeBegin(std::string typeName, FixedDictType* pDataType)
{
	initBody_ = "";
	sourcefileBody_ += fmt::format("class {}\n{{\npublic:\n", typeName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeEnd(std::string typeName, FixedDictType* pDataType)
{
	if (initBody_.size() > 0)
	{
		initBody_ = std::string(":\n") + initBody_;
		initBody_.erase(initBody_.size() - 2);
	}

	sourcefileBody_ += fmt::format("\n\t{}(){}\n\t{{\n\t}}\n", typeName, initBody_);
	sourcefileBody_ += "\n};\n\n";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeBegin(std::string typeName, FixedArrayType* pDataType, const std::string& parentClass)
{
	initBody_ = "";
	sourcefileBody_ += fmt::format("class {}{}\n{{\npublic:\n", typeName, (parentClass.size() > 0 ? std::string(" : ") + parentClass : ""));
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeEnd(std::string typeName, FixedArrayType* pDataType)
{
	if (initBody_.size() > 0)
	{
		initBody_ = std::string(":\n") + initBody_;
		initBody_.erase(initBody_.size() - 2);
	}

	sourcefileBody_ += fmt::format("\n\t{}(){}\n\t{{\n\t}}\n", typeName, initBody_);
	sourcefileBody_ += "\n};\n\n";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_INT8(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tint8 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_INT16(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tint16 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_INT32(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tint32 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_INT64(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tint64 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_UINT8(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tuint8 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_UINT16(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tuint16 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_UINT32(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tuint32 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_UINT64(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tuint64 {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_FLOAT(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tfloat {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "0.0f");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_DOUBLE(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tdouble {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "0.0");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_STRING(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tFString {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_UNICODE(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tFString {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_PYTHON(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PYTHON(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_PY_DICT(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PY_DICT(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_PY_TUPLE(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PY_TUPLE(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_PY_LIST(const std::string& itemName, const std::string& childItemName)
{
	ERROR_MSG("ClientTemplatesUnity::writeTypeItemType_PY_LIST(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_BLOB(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tTArray<uint8> {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_ARRAY(const std::string& itemName, const std::string& childItemName, DataType* pDataType)
{
	std::string new_childItemName = childItemName;

	if (pDataType->type() == DATA_TYPE_FIXEDARRAY)
	{
		FixedArrayType* pFixedArrayType = static_cast<FixedArrayType*>(pDataType);

		// 如果元素又是数组
		if (pFixedArrayType->getDataType()->type() == DATA_TYPE_FIXEDARRAY)
		{
			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pDataType->aliasName(), fmt::format("TArray<{}>", pFixedArrayType->getDataType()->aliasName()));
			else
				new_childItemName = fmt::format("TArray<{}>", pFixedArrayType->getDataType()->aliasName());

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

	sourcefileBody_ += fmt::format("\tTArray<{}> {};\n", new_childItemName, itemName, new_childItemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_FIXED_DICT(const std::string& itemName, const std::string& childItemName, DataType* pDataType)
{
	sourcefileBody_ += fmt::format("\t{} {};\n", childItemName, itemName, childItemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_VECTOR2(const std::string& itemName, const std::string& childItemName)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\tFVector2D {};\n", itemName);
#else
	sourcefileBody_ += fmt::format("\tFVector2D {};\n", itemName);
#endif

	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_VECTOR3(const std::string& itemName, const std::string& childItemName)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\tFVector {};\n", itemName);
#else
	sourcefileBody_ += fmt::format("\tFVector {};\n", itemName);
#endif

	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_VECTOR4(const std::string& itemName, const std::string& childItemName)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\tFVector4 {};\n", itemName);
#else
	sourcefileBody_ += fmt::format("\tFVector4 {};\n", itemName);
#endif

	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeTypeItemType_MAILBOX(const std::string& itemName, const std::string& childItemName)
{
	sourcefileBody_ += fmt::format("\tTArray<uint8> {};\n", itemName);
	initBody_ += fmt::format("\t{}({}),\n", itemName, "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeModuleBegin(ScriptDefModule* pEntityScriptDefModule)
{
	std::string newModuleName = fmt::format("{}{}", pEntityScriptDefModule->getName(), moduleSuffix);

	initBody_ = "\tEntity(),\n";

	sourcefileBody_ = headerBody;
	strutil::kbe_replace(sourcefileBody_, "#REPLACE#", fmt::format("\tPlease inherit this module, such as: (class {} : public {}{})\n", 
		pEntityScriptDefModule->getName(), pEntityScriptDefModule->getName(), moduleSuffix));

	sourcefileBody_ += "#pragma once\n";
	sourcefileBody_ += "#include \"KBEAlias.h\"\n\n";
	sourcefileBody_ += "class Entity;\n";

	sourcefileBody_ += std::string("\n// defined in */scripts/entity_defs/") + pEntityScriptDefModule->getName() + ".def\n";

	sourcefileBody_ += fmt::format("class {} : public Entity\n{{\npublic:\n", newModuleName);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeModuleEnd(ScriptDefModule* pEntityScriptDefModule)
{
	if (initBody_.size() > 0)
	{
		initBody_ = std::string(":\n") + initBody_;
		initBody_.erase(initBody_.size() - 2);
	}

	std::string newModuleName = fmt::format("{}{}", pEntityScriptDefModule->getName(), moduleSuffix);

	sourcefileBody_ += fmt::format("\n\t{}(){}\n\t{{\n\t}}\n", newModuleName, initBody_);
	sourcefileBody_ += fmt::format("\n\tvirtual ~{}()\n\t{{\n\t}}\n\n", newModuleName);
	sourcefileBody_ += "\n};\n\n";
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_INT8(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tint8 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_INT16(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tint16 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_INT32(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tint32 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_INT64(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tint64 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_UINT8(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tuint8 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_UINT16(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tuint16 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_UINT32(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tuint32 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_UINT64(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tuint64 {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), 0);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_FLOAT(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tfloat {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "0.0f");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_DOUBLE(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tdouble {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "0.0");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_STRING(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tFString {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_UNICODE(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tFString {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_PYTHON(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PYTHON(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_PY_DICT(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PY_DICT(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_PY_TUPLE(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PY_TUPLE(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_PY_LIST(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	ERROR_MSG("ClientTemplatesUnity::writeProperty_PY_LIST(): nonsupport!\n");
	return false;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_BLOB(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tTArray<uint8> {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_ARRAY(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	if (std::string("ARRAY") == pPropertyDescription->getDataTypeName())
	{
		return writeTypeItemType_ARRAY(pPropertyDescription->getName(), pPropertyDescription->getDataType()->aliasName(), pPropertyDescription->getDataType());
	}
	else
	{
		sourcefileBody_ += fmt::format("\t{} {};\n", pPropertyDescription->getDataTypeName(), pPropertyDescription->getName());
		initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	} 

	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_FIXED_DICT(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\t{} {};\n", pPropertyDescription->getDataTypeName(), pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_VECTOR2(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\t\tpublic Vector2Int {} = {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector2Int(0, 0)"));
#else
	sourcefileBody_ += fmt::format("\t\tpublic FVector2D {} = {};\n", pPropertyDescription->getName());
#endif

	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_VECTOR3(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\tFVector {};\n", pPropertyDescription->getName());
#else
	sourcefileBody_ += fmt::format("\tFVector {};\n", pPropertyDescription->getName());
#endif

	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_VECTOR4(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
#ifdef CLIENT_NO_FLOAT
	sourcefileBody_ += fmt::format("\tFVector4 {};\n", pPropertyDescription->getName(),
		(strlen(pPropertyDescription->getDefaultValStr()) > 0 ? pPropertyDescription->getDefaultValStr() : "new Vector4Int(0, 0, 0, 0)"));
#else
	sourcefileBody_ += fmt::format("\tFVector4 {};\n", pPropertyDescription->getName());
#endif

	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeProperty_MAILBOX(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, PropertyDescription* pPropertyDescription)
{
	sourcefileBody_ += fmt::format("\tTArray<uint8> {};\n", pPropertyDescription->getName());
	initBody_ += fmt::format("\t{}({}),\n", pPropertyDescription->getName(), "");
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeMethod(ScriptDefModule* pEntityScriptDefModule,
	ScriptDefModule* pCurrScriptDefModule, MethodDescription* pMethodDescription, const char* fillString)
{
	sourcefileBody_ += fmt::format("\tvirtual void {}({}) = 0; \n", pMethodDescription->getName(), fillString);
	return true;
}

//-------------------------------------------------------------------------------------
bool ClientTemplatesUE4::writeMethodArgs_ARRAY(FixedArrayType* pFixedArrayType, std::string& argsTypeBody, const std::string& childItemName)
{
	std::string new_childItemName = childItemName;

	if (pFixedArrayType->type() == DATA_TYPE_FIXEDARRAY)
	{
		// 如果元素又是数组
		if (pFixedArrayType->getDataType()->type() == DATA_TYPE_FIXEDARRAY)
		{
			FixedArrayType* pChildFixedArrayType = static_cast<FixedArrayType*>(pFixedArrayType->getDataType());

			if (new_childItemName.size() > 0)
				strutil::kbe_replace(new_childItemName, pFixedArrayType->aliasName(), fmt::format("TArray<{}>", pChildFixedArrayType->aliasName()));
			else
				new_childItemName = fmt::format("TArray<{}>", pChildFixedArrayType->aliasName());

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

	argsTypeBody += fmt::format("TArray<{}>", new_childItemName);
	return true;
}

//-------------------------------------------------------------------------------------
}
