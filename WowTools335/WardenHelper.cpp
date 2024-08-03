#include "Warden.h"
#include <string>
#include <sstream>
#include <filesystem>
#include <cstdio>  // For snprintf
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

int CustomFilterFunction(DWORD exceptionCode)
{

    //printf("%d\n", exceptionCode);
    // Check the exception code and decide what to do
    if (exceptionCode == EXCEPTION_ACCESS_VIOLATION)
    {
        // Handle access violation, maybe log it
        return EXCEPTION_EXECUTE_HANDLER; // Execute the handler
    }
    else
    {
        // For other exceptions, let the system search for another handler
        return EXCEPTION_CONTINUE_SEARCH;
    }
}

bool IsValidMemoryAddress(DWORD lpAddress)
{
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<void*>(lpAddress), &mbi, sizeof(mbi)))
    {
        // Check if the region is committed and readable
        return (mbi.State == MEM_COMMIT) &&
            (mbi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
                PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE));
    }
    return false;
}

DWORD ReadDWORD(DWORD address)
{
    if (address == 0 || !IsValidMemoryAddress(address))
    {
        return 0;
    }
    __try
    {
        return *(DWORD*)(address);
    }
    __except (CustomFilterFunction(GetExceptionCode()))
    {

        MessageBox(NULL, "Unable to Hook Warden, restart Wow", "Warden Hook", MB_OK | MB_ICONINFORMATION);
        ExitProcess(0);
    }
    return 0;
}

DWORD _ReadDWORD(DWORD address)
{
    DWORD results = 0;

    // Preliminary check for null or zero address
    if (address == 0 || !IsValidMemoryAddress(address))
    {
        //std::cerr << "Invalid address: null or zero." << std::endl;
        return NULL; // Return 0 or some error code
    }

    __try
    {
        // Attempt to read the value at the provided address
        results = *(reinterpret_cast<DWORD*>(address));
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cerr << "Exception caught: access violation." << std::endl;
        return 0; // Handle the exception and return an error value
    }

    return results;
}

std::string ParseSha1Hash(const DWORD* Seed, const DWORD* p_hash)
{
    std::stringstream ss;

    int printedChars = 0; // Counter to keep track of printed characters
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            ss << std::hex << std::setw(2) << std::setfill('0') << ((Seed[i] >> (j * 8)) & 0xFF);
            printedChars += 2; // Increment counter for each character printed
            if (printedChars >= 8) // Check if we've printed 8 characters
                break;
        }
        if (printedChars >= 8) // Break outer loop if we've printed 8 characters
            break;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            ss << std::hex << std::setw(2) << std::setfill('0') << ((p_hash[i] >> (j * 8)) & 0xFF);
        }
    }

    // Return the result as a std::string
    return ss.str();
}

DWORD GetBaseAddress()
{
    HMODULE hModule = GetModuleHandle(nullptr);

    return reinterpret_cast<DWORD>(hModule);
}

bool tContains(const char* Data, const char* substring)
{
    std::string str(Data);
    return str.find(substring) != std::string::npos;
}

void WriteLogFile(const char* szString, const char* fileName)
{
    FILE* pFile;
    fopen_s(&pFile, fileName, "a");
    fprintf(pFile, szString);
    fclose(pFile);
}

template<typename ... Args>
std::string Loggin(bool toConsole, const char* fileName, const std::string& format, Args ... args)
{
    printf(format.c_str(), args ...);
    //if (toConsole)
    //    printf(format.c_str(), args ...);

    //if ((fileName != nullptr) && (fileName[0] != '\0')) {
    //    int size_s = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    //    if (size_s <= 0) {
    //        throw std::runtime_error("Error during formatting.");
    //    }
    //    auto size = static_cast<size_t>(size_s);
    //    std::unique_ptr<char[]> buf(new char[size]);
    //    snprintf(buf.get(), size, format.c_str(), args ...);
    //    WriteLogFile(std::string(buf.get(), buf.get() + size - 1).c_str(), fileName);
    //}

    return "";
}
