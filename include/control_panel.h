#include "main.h"

#define LED_BOARD_RED 12
#define LED_BOARD_GREEN 13
#define MAGNET 3
#define RED_BIG_BUTTON 4
#define SWITCH_ON 2
#define SWITCH_OFF 11

class ControlPanel
{
    public:
    ControlPanel();

    void check_switch();
    void check_red_btn();
    void set_panel_led(led_color light);
    void update_panel_led();

    private:
};
