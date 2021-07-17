#include <iostream>
#include "s3d/core.h"
#include "s3d/ui/button.h"
#include "s3d/ui/label.h"
#include "s3d/ui/checkbox.h"
#include "s3d/ui/image.h"
#include "s3d/ui/radiobutton.h"
#include "s3d/ui/panel.h"
#include "s3d/ui/textfield.h"


using namespace std;


class Triangle : public Object3D {
private:
    Vertex position;
public:
    float angle;
    Triangle(Vertex position);
    void render(Graphics * graphics, const Event_Render *evt);
    void update(std::vector<Object *> * objects, const Event_Update *evt);
};

Triangle::Triangle(Vertex position) {
    Triangle::position = position;
    Triangle::angle = 0.0f;
}

void Triangle::render(Graphics * graphics, const Event_Render *evt) {

    glTranslatef(Triangle::position.x, Triangle::position.y,
                 Triangle::position.z);
    glRotatef(Triangle::angle, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
    // Front
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glColor3f(1.0f,0.0f,0.0f);       // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f,0.0f,1.0f);       // Blue
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glColor3f(0.0f,1.0f,0.0f);       // Green
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid
}


void Triangle::update(std::vector<Object *> * objects,
                      const Event_Update * evt) {
    Triangle::angle += 1.0f;
}


int main(int argc, char *argv[])
{
    CoreContext context = CORE_DEFAULT_CONFIG;
    S3DCore * core = new S3DCore(argc, argv, &context);

    Scene * s = core->createScene();
    s->mouseCamControl = true;
    s->visibleCursor = false;
    s->getCamera()->setPosition(-4.0, 2.0, 0.0);

    Triangle * t = new Triangle((Vertex){0.0, 1.0, 0.0});
    s->addObject(t);

    t = new Triangle((Vertex){1.0, 1.0, 5.0});
    s->addObject(t);


    Label * l = new Label(20, 40, "S3D Engine test");
    s->addObject(l);

    core->setActiveScene(s);
    core->run();
    delete core;

    return 0;
}
