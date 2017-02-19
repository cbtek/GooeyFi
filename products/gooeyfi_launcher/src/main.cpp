
#include "gooeyfi_core/inc/GooeyFiApp.h"

using namespace cbtek::products::gooeyfi::core;
int main(int argc, char ** argv)
{
    GooeyFiApp app("C:/Dev/CBTek/cpp/GooeyFi/products/gooeyfi_core/res/template.xml");
    app.read();
    GooeyFiApp app2("C:/Dev/CBTek/cpp/GooeyFi/products/gooeyfi_core/res/template2.xml");
    app2.setPages(app.getPages());
    app2.write();
	return 0;
}

