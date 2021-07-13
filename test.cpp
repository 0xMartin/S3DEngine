#include <iostream>
#include "s3d/core.h"
#include "s3d/ui/button.h"
#include "s3d/ui/label.h"
#include "s3d/ui/checkbox.h"
#include "s3d/ui/image.h"
#include "s3d/ui/radiobutton.h"
#include "s3d/ui/panel.h"


using namespace std;


class Triangle : public EngineObject {
private:
    Point2D pts[3];
    double time;
public:
    Triangle();
    void render(const Event_Render *evt, Graphics * graphics);
    void update(std::vector<EngineObject *> * objects, const Event_Update *evt);
};

Triangle::Triangle() {
    time = 0.0;

    pts[0].x = 50;
    pts[0].y = 50;
    pts[0].color = (Color){0.0, 0.0, 0.0, 1.0};

    pts[1].x = 250;
    pts[1].y = 350;
    pts[1].color = (Color){0.0, 0.0, 0.0, 1.0};

    pts[2].x = 450;
    pts[2].y = 50;
    pts[2].color = (Color){1.0, 0.0, 0.0, 1.0};
}

void Triangle::render(const Event_Render *evt, Graphics * graphics) {
    Graphics2D * g2 = (Graphics2D*)graphics;
    g2->enableVertexColor();
    g2->fillPolygon(pts, 3);
}

#include <math.h>

void Triangle::update(std::vector<EngineObject *> * objects, const Event_Update * evt) {
    time += evt->ns_diff/3e8;
    pts[0].color.red = sin(time/3);
    pts[0].color.green = cos(time);

    pts[1].color.blue = cos(time/2);
    pts[1].color.red = sin(time/3);

    pts[2].color.green = sin(time);
    pts[2].color.blue = cos(time/2);
}


int main(int argc, char *argv[])
{
    CoreContext context = CORE_DEFAULT_CONFIG;
    S3DCore * core = new S3DCore(argc, argv, &context);

    Scene * s = core->createScene();

    UI_obj * obj;

    Texture * tex = core->loadTexture("data/img.bmp", false);
    if(tex != NULL) {
        obj = new Image(300, 220, 300, 300, tex);
        s->addObject(obj);
    }

    Triangle * t = new Triangle();
    s->addObject(t);

    obj = new Button(250-70, 130, 140, 50, "Button 1");
    s->addObject(obj);

    obj = new Label(250, 100, "Triangle");
    ((Label*)obj)->setCentered(true);
    s->addObject(obj);

    obj = new CheckBox(500, 40, 25, true, "CheckBox 1");
    s->addObject(obj);

    RadioButtonGroup * grp = new RadioButtonGroup();
    s->addObject(grp);

    char buffer[255];
    for(int i = 0; i < 5; ++i) {
        snprintf(buffer, 255, "RadioButton %d", i);
        obj = new RadioButton(500, 100 + i * 30, 20, false, buffer);
        grp->addRadioButton(obj);
        s->addObject(obj);
    }


    core->setActiveScene(s);
    core->run();
    delete core;

    return 0;
}
