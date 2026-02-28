//
// Created by Kai Tears on 27/02/2026.
//

#ifndef SHADCN_IMGUI_SHADCN_HPP
#define SHADCN_IMGUI_SHADCN_HPP

#include <memory>

namespace shadcn
{
    class CFonts;
    class CStyles;

    struct Entry
    {
        Entry( );
        ~Entry( );

        bool initialized;
    };

    struct GlobalContext
    {
        GlobalContext( );
        ~GlobalContext( );

        std::unique_ptr< CFonts > fonts;
        std::unique_ptr< CStyles > styles;
    };

    extern std::unique_ptr< GlobalContext > g;
} // namespace shadcn

#endif // SHADCN_IMGUI_SHADCN_HPP
