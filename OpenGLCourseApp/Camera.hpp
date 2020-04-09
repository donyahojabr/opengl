//
//  Camera.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-04-08.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#endif /* Camera_hpp */

class Camera {
    
public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
    
    void keyControl(bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    
    glm::mat4 calculateViewMatrix();
    
    ~Camera();
    
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    GLfloat yaw; //looking left and right
    GLfloat pitch; //up and down
    
    GLfloat movementSpeed;
    GLfloat turnSpeed;
    
    void update();
};
