#include "ge211_error.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

namespace ge211 {

namespace exceptions {

const char* Exception_base::what() const noexcept
{
    return message_->c_str();
}

Exception_base::Exception_base(const std::string& message)
    : message_{std::make_shared<std::string>(message)}
{ }

Environment_error::Environment_error(const std::string& message)
        : Exception_base(message)
{ }

Client_logic_error::Client_logic_error(const std::string& message)
        : Exception_base(message)
{ }

static std::string build_sdl_error_message(const std::string& message) {
    const char* reason = SDL_GetError();

    std::ostringstream oss;
    if (message.empty())
        oss << "SDL Error: " << reason;
    else
        oss << message << "\n  (reason from SDL: " << reason << ")";

    return oss.str();
}

Host_error::Host_error(const std::string& message)
        : Environment_error{build_sdl_error_message(message)}
{ }

File_error::File_error(const std::string& message)
        : Host_error{message}
{ }

File_error File_error::could_not_open(const std::string& filename)
{
    return File_error("Could not open: " + filename);
}

Font_error::Font_error(const std::string& message)
        : Host_error{message}
{ }

Font_error Font_error::could_not_load(const std::string& filename)
{
    return Font_error("Could not load font: " + filename);
}

Ge211_logic_error::Ge211_logic_error(const std::string& message)
        : Environment_error("Apparent ge211 bug! " + message)
{ }

Image_error::Image_error(const std::string& message)
        : Host_error{message}
{ }

Image_error Image_error::could_not_load(const std::string& filename)
{
    return Image_error("Could not load image: " + filename);
}

}

namespace detail {

static const char* log_level_string(Log_level level)
{
    switch (level) {
        case Log_level::debug:
            return "debug";
        case Log_level::info:
            return "info";
        case Log_level::warn:
            return "warn";
        case Log_level::fatal:
            return "fatal";
    }

    // Shouldn't happen, because switch above is exhaustive. But this
    // makes gcc warn less.
    return "<unknown>";
}

Log_message debug(std::string reason)
{
    return Log_message{std::move(reason), Log_level::debug};
}

Log_message info(std::string reason)
{
    return Log_message{std::move(reason), Log_level::info};
}

Log_message warn(std::string reason)
{
    return Log_message{std::move(reason), Log_level::warn};
}

Log_message fatal(std::string reason)
{
    return Log_message{std::move(reason), Log_level::fatal};
}

Log_message info_sdl()
{
    return info(SDL_GetError());
}

Log_message warn_sdl()
{
    return warn(SDL_GetError());
}

Log_message fatal_sdl()
{
    return fatal(SDL_GetError());
}

Logger& Logger::instance() noexcept
{
    static Logger instance;
    return instance;
}

Log_message::Log_message(std::string reason, Log_message::Level level) noexcept
        : reason_{std::move(reason)}
        , message_{}
        , active_{level >= Logger::instance().level()}
{
    if (active_)
        message_ << "ge211[" << log_level_string(level) << "]: ";
}

Log_message::Log_message(Log_message::Level level)
        : Log_message{"", level}
{ }

Log_message::~Log_message()
{
    if (active_) {
        std::cerr << message_.str();
        if (!reason_.empty()) std::cerr << "\n  (Reason: " << reason_ << ")";
        std::cerr << std::endl;
    }
}

} // end namespace detail

}

