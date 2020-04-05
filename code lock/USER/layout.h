#define PASSLEN 13
#define MENULEN 9

void Layout_init(void);
int Layout_unlock(void);
void Layout_reset(void);
int Layout_main(void);
int Layout_menu(void);

void Layout_set(void);
void Layout_measure(void);
void Layout_display(void);
void Layout_Test(int id);
void Layout_solve(void);
void Layout_beep(void);
void Layout_led(void);