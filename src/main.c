#include "gmeme-gui.h"


int main(int argc, char **argv)
{
    gmeme_app_data_init();

    gmeme_gui_run(argc, argv);

    gmeme_app_data_dispose();

    return 0;
}