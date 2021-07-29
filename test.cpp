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
#include "s3d/objects/skybox.h"


using namespace std;


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
    Gripen::model.setOffset(position);
}

void Gripen::render(Graphics * graphics, const Event_Render *evt) {
    Graphics3D * g3 = ((Graphics3D*)graphics);
    g3->setColorRGB(1.0, 0.0, 0.0, 0.4);
    model.render(graphics);
}


/**
 * @brief The Cube class
 */
class Test : public Object3D {
private:
    Vertex3 position;
public:
    Test(Vertex3 position);
    void render(Graphics * graphics, const Event_Render *evt);
};

Test::Test(Vertex3 position){
    Test::position = position;
}

void Test::render(Graphics * graphics, const Event_Render *evt) {
    glTranslatef(Test::position.x, Test::position.y,
                 Test::position.z);

    Vertex3 p = (Vertex3){0.0, 10.0, 0.0};
    Vertex3 r = (Vertex3){0.0, 40.0, 0.0};
    ((Graphics3D*)graphics)->fillCube(p, r, 2.0);
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
    g3->drawImage(Img3D::position, Img3D::rotation, tex, 9.0f, 9.0f);
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

    //objects with 3D model
    Texture * tex = core->loadTexture("data/gripen_texture.bmp", false);
    Gripen * o = new Gripen(tex, (Vertex3){10.0, 4.0, 2.0});
    s->addObject(o);

    //Test * c = new Test((Vertex3){0.0, -4.0, 2.0});
    //s->addObject(c);


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
    tex = core->loadTexture("data/img.png", true);
    Img3D * i = new Img3D((Vertex3){20.0, 2.0, 0.0}, tex);
    s->addObject(i);


    //lights
    Light * light = s->addLight((Vertex3){10.0, 7.0, 2.0}, (Color){1.0, 1.0, 1.0, 1.0});
    DynamicLight * dl = new DynamicLight(light);
    s->addObject(dl);

    //skybox
    SkyBox * sky = new SkyBox(s, "data/skybox", "jpg", false);
    s->addObject(sky);

    core->setActiveScene(s);
    core->run();
    delete core;

    return 0;
}
