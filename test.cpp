#include <iostream>
#include "s3d/core.h"
#include "s3d/ui/button.h"
#include "s3d/ui/label.h"
#include "s3d/ui/checkbox.h"
#include "s3d/ui/image.h"
#include "s3d/ui/radiobutton.h"
#include "s3d/ui/panel.h"
#include "s3d/ui/textfield.h"
#include "s3d/model.h"


using namespace std;




class Triangle : public Object3D {
private:
    Vertex3 position;
public:
    float angle;
    Triangle(Vertex3 position);
    void render(Graphics * graphics, const Event_Render *evt);
    void update(std::vector<Object *> * objects, const Event_Update *evt);
};

Triangle::Triangle(Vertex3 position) {
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

void Triangle::update(std::vector<Object*> * objects,
                      const Event_Update * evt) {
    Triangle::angle += 1.0f;
}




class Obj1 : public Object3D {
private:
    Model model;
    Vertex3 position;
public:
    Obj1(Vertex3 position);
    void render(Graphics * graphics, const Event_Render *evt);
};

Obj1::Obj1(Vertex3 position) : model("data/gripen.obj") {
    Obj1::position = position;
    //Obj1::model.rotation.x = -90.0f;
}

void Obj1::render(Graphics * graphics, const Event_Render *evt) {
    glTranslatef(Obj1::position.x, Obj1::position.y,
                 Obj1::position.z);
    model.render(graphics);
}





class Img3D : public Object3D {
private:
    Vertex3 position;
    Texture * tex;
public:
    Img3D(Vertex3 position, Texture * tex);
    void render(Graphics * graphics, const Event_Render *evt);
};

Img3D::Img3D(Vertex3 position, Texture * tex) {
    Img3D::position = position;
    Img3D::tex = tex;
    //Img3D::model.rotation.x = -90.0f;
}

void Img3D::render(Graphics * graphics, const Event_Render *evt) {
    ((Graphics3D*)graphics)->drawImage(&(Img3D::position), tex, true);
}





int main(int argc, char *argv[])
{
    CoreContext context = CORE_DEFAULT_CONFIG;
    S3DCore * core = new S3DCore(argc, argv, &context);

    Scene * s = core->createScene();
    s->mouseCamControl = true;
    s->mouseCenter = true;
    s->visibleCursor = false;
    s->getCamera()->setPosition(-4.0, 2.0, 0.0);

    //triangle animation
    Triangle * t = new Triangle((Vertex3){0.0, 1.0, 0.0});
    s->addObject(t);
    t = new Triangle((Vertex3){1.0, 1.0, 5.0});
    s->addObject(t);

    //object with 3D model
    Obj1 * o = new Obj1((Vertex3){10.0, 3.0, 2.0});
    s->addObject(o);

    //2D objects (label + radiobuttons)
    Label * l = new Label(20, 70, "S3D Engine test");
    s->addObject(l);
    char buf[255];
    RadioButton * btn ;
    for(int i  = 0; i < 4; ++i) {
        snprintf(buf, 255, "Option %d", i + 1);
        btn = new RadioButton(20, 100 + i * 30, 20, false, buf);
        s->addObject(btn);
    }

    //3D image
    //Texture * tex = core->loadTexture("data/img.bmp", false);
    //Img3D * i = new Img3D((Vertex3){10.0, 3.0, 5.0}, tex);
    //s->addObject(i);

    core->setActiveScene(s);
    core->run();
    delete core;

    return 0;
}
