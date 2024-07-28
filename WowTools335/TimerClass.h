#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <excpt.h>
#include <mutex>



class LuaTimer
{
public:
    LuaTimer(const std::string& TimerName) : TimerName(TimerName) {}
    void start() {
        try {
            running = true;
            thread = std::thread([this]() {
                while (running) {
                    std::string name;
                    {
                        std::lock_guard<std::mutex> lock(mutex); // Lock access to TimerName
                        name = TimerName;
                    }
                   /* CallBack.push_back(name);*/
                    std::cout <<  name << " : " << interval << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(interval));

                    if (!Repeat) {
                        break; // Exit the loop if Repeat is false
                    }
                }
                });
            thread.detach();  // Detach the thread after starting it
        }
        catch (const std::exception& e) {
            std::cerr << "Exception caught in start(): " << e.what() << std::endl;
            // Handle exception as appropriate
        }
        catch (...) {
            std::cerr << "Unknown exception caught in start()" << std::endl;
            // Handle exception as appropriate
        }
    }

   
    void setScript(lua_State* L)
    {
        if (lua_type(L, 2) == LUA_TFUNCTION) {
            lua_pushvalue(L, 2);  // Push the function onto the stack
            int ref = lua_ref(L, LUA_REGISTRYINDEX);  // Store function reference

            // Set the function reference into the global environment with TimerName as key
            lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
            lua_setglobal(L, TimerName.c_str());
        }
    }

    ~LuaTimer() {
        stop();  // Ensure thread stops when LuaTimer is destroyed
    }

    void stop()
    {
        running = false;
    }
    int interval;
    bool Repeat;
    std::string TimerName;

private:
    std::atomic<bool> running;
    std::thread thread;
    std::mutex mutex;
};