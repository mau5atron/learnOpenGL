//
//  main.cpp
//  GLFW OpenGL
//
//  Created by Gabriel Betancourt on 9/12/19.
//  Copyright © 2019 Gabriel Betancourt. All rights reserved.
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

using namespace std;

// close window with escape key 
void processEscapeInput( GLFWwindow *window ){
  if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ){
    glfwSetWindowShouldClose( window, true );
  }
}

void framebuffer_size_callback( GLFWwindow* window, int width, int height ){
  glViewport( 0, 0, width, height );
}

int OpenGL_initialization(void)
{
  glfwInit(); // need to initialize before functions can be used
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
  glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

  GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr );
  int screenWidth, screenHeight;
  glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

  if( nullptr == window ){
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent( window );
  glewExperimental = GL_TRUE;

  if( GLEW_OK != glewInit() ){
    cout << "Failed to initialize GLEW" << endl;
    return -1;
  }

  glViewport( 0, 0, screenWidth, screenHeight );

  // we tell glfw we want to call this function on every window resize by
  // registering it
  glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

  while( !glfwWindowShouldClose( window ) ){

    // input
    processEscapeInput( window ); // listen for escape key on render loop

    // render loop indicating that the window should stay open and continue
    // drawing images until explicitly told to quit

    // check and call events and swap the buffers
    glfwPollEvents();

    // only care about the color values so we are clearing the color buffer bit
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ); // state-setting function 1.4.1
    glClear( GL_COLOR_BUFFER_BIT ); // clear screens color buffer 1.3, 1.4.2

   
    glfwSwapBuffers( window ); // 1.1
  }

  glfwTerminate(); // perform cleanup 1.2

  return 0;
}

int main(void) {
    OpenGL_initialization();

    return 0;
}

// NOTES

/*
  1.1: 
  - When an application draws a single buffer the resulting image might display
    flickering issues. This is because the resulting output image is not drawn
    in an instant, but drawn pixel by pixel and usually from left to right and
    top to bottom. Because this image is not displayed at an instant to the user
    while still being rendered to, the result may contain artifacts. To
    circumvent these issues, windowing applications apply double buffer for
    rendering. The front buffer contains the final output image that is shown at
    the screen, while all the rendering commands draw to the back buffer. As
    soon as all the rendering commands are finished we swap the back buffer to
    the front buffer so the image is instantly displayed to the user, removing
    all the aforementioned artifacts.

  1.2: 
  - As soon as we exit the render loop we would like to properly clean/delete
    all of GLFW's resources that were allocated. We can do this via the
    glfwTerminate function that we call at the end of the main function.

  1.3: 
  - We can clear the screen's color buffer using the glClear function where pass
    in buffer bits to specify which buffer we would like to clear. The possible
    bits we can set are 
    1. GL_COLOR_BUFFER_BIT
    2. GL_DEPTH_BUFFER_BIT
    3. GL_STENCIL_BUFFER_BIT

    1.4.1: 
    - glClearColor is a state-setting function
    1.4.2: 
    - glClear is a state-using function  in that it uses the current state to
      retrieve the clearing color from.
*/ 


