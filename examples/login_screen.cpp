//
// Created by Kai Tears on 27/02/2026.
//

#include "login_screen.hpp"

#include "imgui.h"
#include "../shadcn/include/shadcn/shadcn.hpp"
#include "../shadcn/include/shadcn/fonts/fonts.hpp"
#include "../shadcn/include/shadcn/fonts/lucide/lucide_defines.hpp"
#include "../shadcn/include/shadcn/styles/styles.hpp"
#include "../shadcn/include/shadcn/color/color.hpp"
#include "../shadcn/include/shadcn/elem/button.hpp"
#include "../shadcn/include/shadcn/elem/checkbox.hpp"
#include "../shadcn/include/shadcn/elem/elem.hpp"
#include "../shadcn/include/shadcn/elem/input_text.hpp"
#include "../shadcn/include/shadcn/elem/text.hpp"

using namespace ImGui;

void simpleCheckboxWidget( bool* v, const std::string& name )
{
    auto const cur_y = GetCursorPosY( );
    static bool forward_focus = false;
    shadcn::Checkbox( name, v, { .size = { 16, 16 }, .style = shadcn::CheckboxStyle::Destructive, .forwardFocus = &forward_focus } );
    SameLine( 0, 10 );
    SetCursorPosY( cur_y );
    shadcn::Text( name, { .fontVariant = "geist_500_14", .onClick = [ & ] {
                             *v = ( !*v );
                             forward_focus = true;
                         } } );
}

void LoginScreen::render( )
{
    auto* draw = GetBackgroundDrawList( );
    auto const screen_size = GetIO( ).DisplaySize - ImVec2( 0, 40 ); // :)

    draw->AddRectFilled( { 0, 0 }, GetIO( ).DisplaySize, shadcn::colorPalette[ "background" ].u32( ) );

    auto const key_icon = ICON_LUCIDE_KEY_ROUND;
    auto const font_h = shadcn::g->fonts->get( "geist_500_20" );
    ImVec2 const key_position = { screen_size.x / 2, screen_size.y / 2 - 70 };

    draw->AddRectFilled( key_position - ImVec2( 24, 24 ), key_position + ImVec2( 24, 24 ), shadcn::colorPalette[ "muted" ].modulate( 0.3f ), 10 );
    draw->AddRect( key_position - ImVec2( 24, 24 ), key_position + ImVec2( 24, 24 ), shadcn::colorPalette[ "border" ].u32( ), 10 );

    font_h.renderText( draw, key_position, { 0.5f, 0.5f }, shadcn::colorPalette[ "text" ].u32( ), key_icon );

    font_h.renderText( draw, key_position + ImVec2( 0, 34 ), { 0.5f, 0.f }, shadcn::colorPalette[ "text" ].u32( ), "everness Login" );

    static ImVec2 const window_size = {
        300, 0 };

    SetNextWindowPos( { screen_size.x / 2 - window_size.x / 2, screen_size.y / 2 + 10 } );
    SetNextWindowSize( window_size );

    Begin( "##elem", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground );
    {
        auto const width = GetContentRegionAvail( ).x;

        shadcn::Text( "Enter your key", { .fontVariant = "geist_500_16" } );

        static char buf[ 50 ] = { };
        shadcn::InputText( "##key", "Your key", buf, IM_ARRAYSIZE( buf ), { .size = { width, 8 * 2 + 14 }, .pad = { 8, 8 }, .fontVariant = "geist_500_14", .rounding = 10, .isDestructive = false } );

        if ( buf[ 0 ] != 'E' )
            shadcn::elem::pushInactiveFlag( );

        static bool remember;
        simpleCheckboxWidget( &remember, "Remember me?" );

        auto const btn_width = width / 2 - 5; // 5 = 10/2 - padding

        shadcn::Button( "Cancel", { .size = { btn_width, 8 * 2 + 14 }, .fontVariant = "geist_500_14", .rounding = 10, .style = shadcn::ButtonStyle::Destructive, .onClick = [] {
                                   } } );

        SameLine( 0, 10 );

        shadcn::Button( "OK", { .size = { btn_width, 8 * 2 + 14 }, .fontVariant = "geist_500_14", .rounding = 10, .style = shadcn::ButtonStyle::Primary, .onClick = [] {
                               } } );

        shadcn::elem::popInactiveFlag( );

        End( );
    }
}