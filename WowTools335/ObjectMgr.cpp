#include "ObjectMgr.h"

bool ObjectMgr::enumObjects(EnumFunc_t func)
{
	return ((int(*)(int(*)(guid_t, void*), void*))0x004D4B30)([](guid_t guid, void* udata) -> int {
		return (*(EnumFunc_t*)udata)(guid);
		}, &func);
}

GameObjectNative* ObjectMgr::find(guid_t guid, unsigned flags)
{
	return ((GameObjectNative * (*)(guid_t, unsigned, const char*, unsigned))0x004D4DB0)(guid, flags, NULL, 0);
}

char* ObjectMgr::guid2hex(guid_t guid, char* hex)
{
	return ((char* (*)(guid_t, char*))0x0074D0D0)(guid, hex);
}

guid_t ObjectMgr::hex2guid(const char* str)
{
	return ((guid_t(*)(const char*))0x0074D120)(str);
}

int ObjectMgr::GetObjectPointer(uint64_t guid, int Type)
{
	return  guid ? ((int(__cdecl*)(uint64_t, int))0x004D4DB0)(guid, Type) : 0;
}


int ObjectMgr::Descriptors(UINT BaseAddress)
{
    if (!BaseAddress)
    {
        return 0;
    }
    return *(int*)(BaseAddress + 0x08);
}

int ObjectMgr::GetVirtualFuncAddr(UINT Ptr, const int offset)
{
    return Ptr ? *(int*)(*(int*)Ptr + 4 * offset) : 0;
}

template<typename DSC>
DSC ObjectMgr::GetDescriptor(UINT BaseAddress, int offset)
{
    int desc = Descriptors(BaseAddress);
    if (desc == 0) return DSC(0);
    UINT field = offset * 4;
    return *(DSC*)(desc + field);
}

template<typename DSC>
DSC ObjectMgr::GetDescriptor2(UINT BaseAddress, const int offset)
{
    int desc = Descriptors(BaseAddress);
    return desc ? *(DSC*)(desc + offset) : DSC(0);
}

template<typename DSC>
DSC ObjectMgr::GetDescriptorAddr(UINT BaseAddress, const int offset)
{
    int desc = Descriptors(BaseAddress);
    return (DSC)(desc + offset * 4);
}

void* ObjectMgr::GetPointerDescriptor(UINT BaseAddress, const int offset)
{
    return (void*)(Descriptors(BaseAddress) + offset * 4);
}

int ObjectMgr::ObjectDescriptor(UINT BaseAddress, const int offset)
{
    return GetDescriptor2<int>(BaseAddress, offset);
}

bool ObjectMgr::HasFlag(UINT BaseAddress, const int idx, const int flag)
{
    int flags = GetDescriptor<int>(BaseAddress, idx);
    return (flags & flag) != 0;
}


char* ObjectMgr::GetName(UINT Ptr)
{
    if (Ptr == 0)
        return "";
    return ((char* (__thiscall*)(int))GetVirtualFuncAddr(Ptr, 54))(Ptr);
}

void ObjectMgr::Interact(UINT BaseAddress)
{
    if (BaseAddress)
    {
        ((void(__thiscall*)(int))GetVirtualFuncAddr(BaseAddress, 44))(BaseAddress);
    }
}

