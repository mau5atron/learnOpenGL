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

  while( !glfwWindowShouldClose( window ) ){
    glfwPollEvents();
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glfwSwapBuffers( window );
  }

  glfwTerminate();

  return 0;
}

int main(void) {
    OpenGL_initialization();

    return 0;
}
