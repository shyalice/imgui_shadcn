#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "shadcn.hpp"
#include "color/color.hpp"
#include "elem/button.hpp"
#include "elem/card.hpp"
#include "elem/checkbox.hpp"
#include "elem/elem.hpp"
#include "elem/input_text.hpp"
#include "elem/slider.hpp"
#include "elem/toggle.hpp"
#include "examples/login_screen.hpp"
#include "fonts/fonts.hpp"
#include "fonts/lucide/lucide_defines.hpp"
#include "styles/styles.hpp"

#include <atomic>
#include <deque>
#include <iostream>
#include <mutex>
#include <string>

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>

#include <json.hpp>

int main( )
{
    glfwInit( );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );

    GLFWwindow* window = glfwCreateWindow( 1280, 720, "01.01.2026 =)", nullptr, nullptr );
    glfwMakeContextCurrent( window );
    if ( !gladLoadGL( ) )
    {
        return 1;
    }

    glfwSwapInterval( 1 );

    IMGUI_CHECKVERSION( );
    ImGui::CreateContext( );
    ImGuiIO& io = ImGui::GetIO( );
    ( void ) io;

    ImVec4 clear_color = ImVec4( 0.45f, 0.55f, 0.60f, 1.00f );

    ImGui::StyleColorsDark( );

    if ( !shadcn::Entry( ).initialized )
        return 1;

    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( "#version 330 core" );

    while ( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents( );

        ImGui_ImplOpenGL3_NewFrame( );
        ImGui_ImplGlfw_NewFrame( );

        ImGui::NewFrame( );

        LoginScreen::render( );

        // ImGui::ShowDemoWindow( );

        ImGui::Begin( "Playground" );
        {
            shadcn::Card card( "Card", ImGui::GetContentRegionAvail( ), shadcn::Card::CardData { .backgroundStyle = shadcn::CardBackgroundStyle::Standard } );
            static bool check;
            shadcn::Checkbox( "checkbox_test", &check, { .size = { 16, 16 }, .onClick = [] {
                                                            std::cout << "Hello, World!" << std::endl;
                                                        } } );

            ImGui::SameLine( 0, 8 );

            shadcn::Toggle( "toggle_test", &check, { .size = { 26, 16 }, .onClick = [] {
                                                    } } );

            ImGui::SameLine( 0, 8 );

            shadcn::Toggle( "toggle_test_d", &check, { .size = { 26, 16 }, .style = shadcn::ToggleStyle::Destructive, .onClick = [] {
                                                      } } );

            ImGui::SameLine( 0, 8 );

            static int slider = 0;
            shadcn::Slider( "Slider", &slider, -5, 5, {
                                                          .size = { 64, 16 },
                                                      } );

            ImGui::SameLine( 0, 8 );

            shadcn::Slider( "Inactive slider", &slider, -5, 5, {
                                                                   .style = shadcn::SliderStyle::Filled,
                                                                   .size = { 64, 16 },
                                                               } );

            ImGui::SameLine( 0, 5 );
            ImGui::Text( "%i", slider );

            shadcn::Button( "Cancel", { .size = { 80, 24 }, .fontVariant = "geist_500_14", .style = shadcn::ButtonStyle::Destructive, .onClick = [] {
                                           std::cout << "Hello, World!" << std::endl;
                                       } } );

            ImGui::SameLine( 0, 8 );

            shadcn::Button( "OK", { .size = { 80, 24 },
                                    .fontVariant = "geist_500_14",
                                    .style = shadcn::ButtonStyle::Primary,
                                    .onClick = [] {
                                        std::cout << "Hello, World!" << std::endl;
                                    } } );

            ImGui::SameLine( 0, 8 );

            shadcn::Button( "Alternative", { .size = { 80, 24 },
                                             .fontVariant = "geist_500_14",
                                             .style = shadcn::ButtonStyle::Secondary,
                                             .onClick = [] {
                                                 std::cout << "Hello, World!" << std::endl;
                                             } } );

            static char buf[ 50 ] = { };
            shadcn::InputText( "Input Field", "Enter something", buf, IM_ARRAYSIZE( buf ), { .size = { 100, 6 * 2 + 14 }, .pad = { 6, 6 }, .isDestructive = true } );

            ImGui::SameLine( 0, 10 );

            static char buf2[ 50 ] = { };
            shadcn::InputText( "Input Field 2", "Enter something 2", buf2, IM_ARRAYSIZE( buf2 ), { .size = { 100, 6 * 2 + 14 }, .pad = { 6, 6 }, .isDestructive = false } );

            card.end( );

            ImGui::End( );
        }

        // ImGui::Begin( "Lucide Icons" );
        // {
        //     static std::vector< int > const font_sizes = {
        //         14, 16, 18, 20 };
        //
        //     for ( auto const size : font_sizes )
        //     {
        //         ImGui::PushFont( shadcn::g->fonts->get( "geist_400_" + std::to_string( size ) ).data.first );
        //         ImGui::Text( "Лежал - %s", ICON_LUCIDE_KEY_ROUND );
        //         ImGui::PopFont( );
        //     }
        //
        //     ImGui::End( );
        // }

        ImGui::Render( );
        int display_w, display_h;
        glfwGetFramebufferSize( window, &display_w, &display_h );
        glViewport( 0, 0, display_w, display_h );
        glClearColor( clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w );
        glClear( GL_COLOR_BUFFER_BIT );
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData( ) );

        glfwSwapBuffers( window );
    }

    ImGui_ImplOpenGL3_Shutdown( );
    ImGui_ImplGlfw_Shutdown( );
    ImGui::DestroyContext( );
    glfwDestroyWindow( window );
    glfwTerminate( );

    return 0;
}
