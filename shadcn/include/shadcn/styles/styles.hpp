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

    struct GlobalStyleSettings
    {
        bool useAdvancedAnimations = true;
    };

    class CStyles
    {
    public:
        ~CStyles( );
        CStyles( );

        GlobalStyleSettings global;

        void setDarkNeutral( );
        // TODO / FIXME
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_STYLES_HPP
