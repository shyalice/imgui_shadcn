//
// Created by Kai Tears on 27/02/2026.
//

#ifndef SHADCN_IMGUI_STYLES_HPP
#define SHADCN_IMGUI_STYLES_HPP

#include "imgui.h"

#include <string>
#include <unordered_map>

namespace shadcn
{
    struct Color;

    extern std::unordered_map< std::string, Color > colorPalette;

    class CStyles
    {
    public:
        ~CStyles( );
        CStyles( );

        void setDarkNeutral( );
        // TODO / FIXME
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_STYLES_HPP
