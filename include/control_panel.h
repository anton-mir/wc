#include "main.h"

#define LED_BOARD_RED 12
#define LED_BOARD_GREEN 13
#define MAGNET 3
#define RED_BIG_BUTTON 4
#define SWITCH_ON 2
#define SWITCH_OFF 11
#define PANEL_BLINK_TIMES 10

class ControlPanel
{
    public:
    ControlPanel();

    void set_panel_led(led_color light);
    void update_panel_led();
    void run();

    private:
    void check_switch();
    void check_red_btn();
    bool panel_leds_state = false;
    uint8_t panel_blink_timer_counter = 0;
};
