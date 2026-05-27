#include "../../include/render/render.h"

Render::Render(MainWindow* mainWindow) {
	window = mainWindow;
	SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

Render::~Render() {

}

void Render::SetClearColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

void Render::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
