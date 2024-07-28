#pragma once
#include <cstdint>
#include <functional>
#include "SharedHeaders.h"

using guid_t = uint64_t;
struct GameObjectNative;
class ObjectMgr {
public:
	using EnumFunc_t = std::function<bool(guid_t)>;
	static bool enumObjects(EnumFunc_t func);
	static GameObjectNative* find(guid_t guid, unsigned flags);
	static char* guid2hex(guid_t guid, char* buf);
	static guid_t hex2guid(const char* str);
	static int GetObjectPointer(uint64_t guid, int MaskType);


	static int GetVirtualFuncAddr(UINT Ptr, const int offset);
	static int Descriptors(UINT BaseAddress);
	static void* GetPointerDescriptor(UINT BaseAddress, const int offset);
	static int ObjectDescriptor(UINT BaseAddress, const int offset);
	static bool HasFlag(UINT BaseAddress, const int idx, const int flag);

	template<typename DSC>
	static DSC GetDescriptor(UINT BaseAddress, int offset);
	template<typename DSC>
	static DSC GetDescriptor2(UINT BaseAddress, const int offset);
	template<typename DSC>
	static DSC GetDescriptorAddr(UINT BaseAddress, const int offset);



	static char* GetName(UINT Ptr);
	static void Interact(UINT BaseAddress);
};
