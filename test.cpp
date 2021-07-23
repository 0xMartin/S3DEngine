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



/**
 * @brief The Triangle class
 */
class Triangle : public Object3D {
private:
    Vertex3 position;
public:
    float angle;
    Triangle(Vertex3 position);
    void render(Graphics * graphics, const Event_Render *evt);
    void update(std::vector<Object *> & objects, const Event_Update *evt);
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

void Triangle::update(std::vector<Object*> & objects,
                      const Event_Update * evt) {
    Triangle::angle += 1.0f;
}


/**
 * @brief The Gripen class
 */
class Gripen : public Object3D {
private:
    Model model;
    Vertex3 position;
public:
    Gripen(Texture * t, Vertex3 position);
    void render(Graphics * graphics, const Event_Render *evt);
};

Gripen::Gripen(Texture * t, Vertex3 position) : model("data/gripen2.obj") {
    Gripen::position = position;
    model.setTexture(t);
    //Obj1::model.rotation.x = -90.0f;
}

void Gripen::render(Graphics * graphics, const Event_Render *evt) {
    glTranslatef(Gripen::position.x, Gripen::position.y,
                 Gripen::position.z);
    Graphics3D * g3 = ((Graphics3D*)graphics);
    g3->setColorRGB(1.0, 0.0, 0.0, 0.4);
    model.render(graphics);
}


/**
 * @brief The Cube class
 */
class Cube : public Object3D {
private:
    Model model;
    Vertex3 position;
public:
    Cube(Texture * t, Vertex3 position);
    void render(Graphics * graphics, const Event_Render *evt);
};

Cube::Cube(Texture * t, Vertex3 position) : model("data/cube.obj") {
    Cube::position = position;
    model.setTexture(t);
}

void Cube::render(Graphics * graphics, const Event_Render *evt) {
    glTranslatef(Cube::position.x, Cube::position.y,
                 Cube::position.z);
    model.render(graphics);
}


/**
 * @brief The Img3D class
 */
class Img3D : public Object3D {
private:
    Vertex3 position;
    Vertex3 rotation;
    Texture * tex;
public:
    Img3D(Vertex3 position, Texture * tex);
    void render(Graphics * graphics, const Event_Render *evt);
};

Img3D::Img3D(Vertex3 position, Texture * tex) {
    Img3D::position = position;
    Img3D::tex = tex;
    rotation = (Vertex3){0.0, -90.0, 0.0};
    //Img3D::model.rotation.x = -90.0f;
}

void Img3D::render(Graphics * graphics, const Event_Render *evt) {
    Graphics3D * g3 = ((Graphics3D*)graphics);
    g3->drawImage(&(Img3D::position), &(Img3D::rotation), tex, 9.0f, 9.0f);
}



/**
 * @brief The DynamicLight class
 */
class DynamicLight : public Object3D {
private:
    Light * light;
    Vertex3 defPos;
    float time = 0;
public:
    DynamicLight(Light * light);
    void render(Graphics * graphics, const Event_Render *evt);
    void update(std::vector<Object *> & objects, const Event_Update *evt);
};

DynamicLight::DynamicLight(Light * light) {
    DynamicLight::defPos = light->position;
    DynamicLight::light = light;
}

void DynamicLight::render(Graphics * graphics, const Event_Render *evt) {
    Vertex3 p = light->position;
    float size = 0.5;
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for(unsigned int i = 0; i < 3; ++i) {
        glVertex3f(p.x - size * (i == 0),
                   p.y - size * (i == 1),
                   p.z - size * (i == 2));
        glVertex3f(p.x + size * (i == 0),
                   p.y + size * (i == 1),
                   p.z + size * (i == 2));
    }
    glEnd();
}

void DynamicLight::update(std::vector<Object *> & objects, const Event_Update *evt) {
    DynamicLight::time += 0.03f;
    Vertex3 p = DynamicLight::defPos;
    GLfloat radius = 10.0;
    Vertex3 v = (Vertex3){
            cos(DynamicLight::time) * radius + p.x,
            (GLfloat)(0.0 + p.y),
            sin(DynamicLight::time) * radius + p.z};
    light->position = v;
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


    //objects with 3D model
    Texture * tex = core->loadTexture("data/gripen_texture.bmp", false);
    for(int i = 0; i < 1; ++i) {
        Gripen * o = new Gripen(tex, (Vertex3){10.0, 4.0, 2.0});
        s->addObject(o);
    }

    tex = core->loadTexture("data/stone.bmp", false);
    Cube * o = new Cube(tex, (Vertex3){0.0, -4.0, 2.0});
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
    tex = core->loadTexture("data/img.bmp", false);
    Img3D * i = new Img3D((Vertex3){20.0, 2.0, 0.0}, tex);
    s->addObject(i);


    //lights
    Light * light = s->addLight((Vertex3){0.0, 12.0, 0.0}, (Color){1.0, 1.0, 1.0, 1.0});
    DynamicLight * dl = new DynamicLight(light);
    s->addObject(dl);


    core->setActiveScene(s);
    core->run();
    delete core;

    return 0;
}
